#define _POSIX_C_SOURCE 200809L
#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

enum { CLOCK, STOPWATCH, TIMER, MODE_COUNT };

static pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
static int mode = CLOCK;
static int paused[MODE_COUNT], finished;
static long long time_ms[MODE_COUNT], last_tick;
static long long last_shown = -1;

static long long now_ms(void)
{
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec * 1000LL + now.tv_nsec / 1000000;
}

// Прибавляем только время, прошедшее с предыдущего обновления.
static void update_time(void)
{
    long long now = now_ms();
    long long elapsed = now - last_tick;
    last_tick = now;

    if (!paused[CLOCK]) {
        time_ms[CLOCK] = (time_ms[CLOCK] + elapsed) % 86400000;
    }
    if (mode == STOPWATCH && !paused[STOPWATCH]) {
        time_ms[STOPWATCH] += elapsed;
    }
    if (mode == TIMER && !paused[TIMER]) {
        time_ms[TIMER] -= elapsed;
        if (time_ms[TIMER] < 0) {
            time_ms[TIMER] = 0;
        }
    }
}

static void *clock_thread(void *arg)
{
    const char *names[] = {"Clock", "Stopwatch", "Timer"};
    const struct timespec delay = {0, 100000000};
    (void)arg;

    for (;;) {
        pthread_mutex_lock(&lock);
        if (finished) {
            pthread_mutex_unlock(&lock);
            return NULL;
        }

        update_time();
        long long seconds = time_ms[mode] / 1000;
        if (mode == TIMER) {
            seconds = (time_ms[TIMER] + 999) / 1000;
        }

        if (seconds != last_shown) {
            const char *status = paused[mode] ? " (paused)" : "";
            if (mode == TIMER && seconds == 0) {
                status = " (time is up)";
            }
            printf("%s %02lld:%02lld:%02lld%s\n", names[mode],
                   seconds / 3600, seconds / 60 % 60, seconds % 60, status);
            last_shown = seconds;
        }
        pthread_mutex_unlock(&lock);
        nanosleep(&delay, NULL);
    }
}

static void apply_command(char command, const char *line)
{
    int h, m, s;
    char extra;

    // Учитываем прошедшее время перед сменой режима или паузой.
    update_time();

    if (command == 'c') {
        mode = CLOCK;
    } else if (command == 'p') {
        if (mode == TIMER && time_ms[TIMER] == 0) {
            return;
        }
        paused[mode] = !paused[mode];
    } else if (command == 'w') {
        mode = STOPWATCH;
        time_ms[STOPWATCH] = 0;
        paused[STOPWATCH] = 0;
    } else if (command == 't' &&
               sscanf(line, " t %9d %c", &s, &extra) == 1 && s > 0) {
        mode = TIMER;
        time_ms[TIMER] = s * 1000LL;
        paused[TIMER] = 0;
    } else if (command == 's' &&
               sscanf(line, " s %2d:%2d:%2d %c", &h, &m, &s, &extra) == 3 &&
               h >= 0 && h < 24 && m >= 0 && m < 60 && s >= 0 && s < 60) {
        mode = CLOCK;
        time_ms[CLOCK] = (h * 3600 + m * 60 + s) * 1000LL;
        paused[CLOCK] = 0;
    } else {
        puts("Invalid command. Use s HH:MM:SS or t SECONDS to set time.");
        return;
    }
    last_shown = -1;
}

int main(void)
{
    time_t current = time(NULL);
    const struct tm *local = localtime(&current);
    if (local != NULL) {
        time_ms[CLOCK] = (local->tm_hour * 3600 + local->tm_min * 60 + local->tm_sec) * 1000LL;
    }
    last_tick = now_ms();

    setvbuf(stdout, NULL, _IONBF, 0);
    puts("c - clock | p - pause/resume | s HH:MM:SS - set time");
    puts("w - start stopwatch | t SECONDS - start timer | q - quit");
    pthread_t thread;
    if (pthread_create(&thread, NULL, clock_thread, NULL) != 0) {
        puts("Could not start clock thread.");
        return 1;
    }

    char line[80], command, extra;
    while (fgets(line, sizeof line, stdin) != NULL) {
        if (strchr(line, '\n') == NULL && !feof(stdin)) {
            int ch;
            do {
                ch = getchar();
            } while (ch != '\n' && ch != EOF);
            puts("Command is too long.");
            continue;
        }

        int fields = sscanf(line, " %c %c", &command, &extra);
        if (fields < 1) {
            continue;
        }
        if (fields == 2 && strchr("cpwq", command) != NULL) {
            puts("This command takes no arguments.");
            continue;
        }
        if (command == 'q') {
            break;
        }

        pthread_mutex_lock(&lock);
        apply_command(command, line);
        pthread_mutex_unlock(&lock);
    }

    pthread_mutex_lock(&lock);
    finished = 1;
    pthread_mutex_unlock(&lock);
    pthread_join(thread, NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}
