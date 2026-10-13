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


node* insert_value(node* list, int value, int index){
    node* new_node = calloc(1,sizeof(node));
    new_node->chislo = value;
    new_node->number = index;
    new_node->next = NULL;
    node* current = list;
    node* prev =NULL;
    if(index == 0)
    {
        return list;
    }
    if(index == 1)
    {
        current = list;
        new_node->next = current; 
        list = new_node;
        current = new_node->next;
        while(current != NULL)
        {
            current->number++;
            current = current->next;
        }

    }
   else
   {
    while (current != NULL && current->number != index)
    {
    prev = current;
    current = current->next;
    }
    
    new_node->next = current;
    prev->next = new_node;
    current = new_node->next;
    while(current != NULL)
    {
        
        current->number++;
        current = current->next;
    }
}
    return list;
}



node* swap_elems(node* list, int first_index, int second_index)
{
   
    if (list == NULL || first_index < 1 || second_index < 1)
        return list;

    if (first_index == second_index)
        return list;

   
    if (first_index > second_index)
    {
        int temp = first_index;
        first_index = second_index;
        second_index = temp;
    }

   
    node* current1 = list;
    node* prev1 = NULL;

    while (current1 != NULL && current1->number != first_index)
    {
        prev1 = current1;
        current1 = current1->next;
    }

    node* current2 = list;
    node* prev2 = NULL;

    while (current2 != NULL && current2->number != second_index)
    {
        prev2 = current2;
        current2 = current2->next;
    }

   
    if (current1 == NULL || current2 == NULL)
        return list;

    if (current1->next == current2)
    {
        if (prev1 != NULL)
            prev1->next = current2;
        else
            list = current2;

        current1->next = current2->next;
        current2->next = current1;
    }
 
    else
    {
        if (prev1 != NULL)
            prev1->next = current2;
        else
            list = current2;

        if (prev2 != NULL)
            prev2->next = current1;
        else
            list = current1;

        node* temp = current1->next;

        current1->next = current2->next;
        current2->next = temp;
    }

    
    int temp_number = current1->number;
    current1->number = current2->number;
    current2->number = temp_number;

    return list;
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
    l = insert_value(l,124,0);
    printf("dsads\n");
    print_node(l);
    printf("dsads\n");
    l = swap_elems(l,2,4);
    print_node(l);
}