#define CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>



typedef struct Node{
    int number;
    int chislo;

    struct Node* next;
}node;



node* create_list(int arr[], int size){
        node* head= NULL;
        node* current = NULL;
        
        for (int i = 0; i < size; i++)
        {
            node* new_node= calloc(1, sizeof(node));
            new_node->chislo = arr[i];
            new_node->number = i+1;
            new_node->next = NULL;
            if(i == 0)
            {
                head = new_node;
                current = new_node;
            }
            else{
            current->next = new_node;
            current = new_node;
            }
            
        }
        return head;
}


void delete_list(node** list){
    node*current = *list;
    node* next = NULL;
    while(current != NULL)
    {
        next = current->next;
        free(current);
        current = NULL;
        current = next;
    }
    *list = NULL;
        
}


void print_node(node* list){
    if(list == NULL){
        printf("list is empty");
    }
    node* current = list;
    while(current != NULL)
    {
        printf("number [%d] = %d\n", current->number,current->chislo);
        current = current->next;
    }
    
}

int main()
{
    int arr[] = {5,6,2,4,1};
    node* l = create_list(arr,5);
    print_node(l);
    delete_list(&l);
   print_node(l);
}