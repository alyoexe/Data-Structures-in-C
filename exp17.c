#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define HEAP_SIZE 20
#define ARR_SIZE 50

typedef struct {
    int priority;
    int token_number;
    char type[ARR_SIZE];
}customer;

typedef struct{
    int size;
    int capacity;
    customer* Customers;
}heap;

int set_priority(char* t){
    if(strcmp(t,"defence")==0){
        return 2;
    }
    else if(strcmp(t,"differently-abled")==0){
        return 4;
    }
    else if(strcmp(t,"senior-citizen")==0){
        return 3;
    }
    else {
        return 1;
    }
}


customer* make_customer(char* t,int token){
    customer* c =(customer*)malloc(sizeof(customer));
    c->token_number=token;
    strcpy(c->type,t);
    c->priority=set_priority(t);
    return c;
}

heap* make_heap(int x){
    heap* h = (heap*)malloc(sizeof(heap));
    h->size=0;
    h->capacity=x;
    h->Customers=(customer*)malloc(x*sizeof(customer));
    return h;
}
void swap(customer* a, customer* b)
{
    customer temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(heap* h, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < h->size){
        if(h->Customers[left].priority > h->Customers[largest].priority){
            largest = left;
        }
        else if(h->Customers[left].priority == h->Customers[largest].priority
                &&h->Customers[left].token_number < h->Customers[largest].token_number){
            largest = left;
        }
    } 
    if (right < h->size){
        if(h->Customers[right].priority > h->Customers[largest].priority){
            largest = right;
        }
        else if(h->Customers[right].priority == h->Customers[largest].priority
                &&h->Customers[right].token_number < h->Customers[largest].token_number){
            largest = right;
        }
    }
    if (largest != i) {
        swap(&h->Customers[i], &h->Customers[largest]);
        heapify(h, largest);
    }
}

void insert_heap(heap* h,customer* c){
    if (h->size == h->capacity) {
        printf("Heap overflow\n");
        return;
    }

    h->size++;
    int i = h->size - 1;
    h->Customers[i] = *c;

    while (i != 0 ){
        int parent = (i - 1) / 2;
        if(h->Customers[parent].priority < h->Customers[i].priority){
            swap(&h->Customers[i], &h->Customers[parent]);
            i=parent;
        }
        else if(h->Customers[parent].priority == h->Customers[i].priority&&h->Customers[parent].token_number > h->Customers[i].token_number){
            swap(&h->Customers[i], &h->Customers[parent]);
            i=parent;
        }  
        else{
            break;
        }
    }
}

customer empty_customer() {
    customer c;
    c.priority = -1; 
    c.token_number = -1;
    strcpy(c.type, "No customers left!");
    return c;
}

customer extractMax(heap* h)
{
    if (h->size <= 0)
        return empty_customer();
    if (h->size == 1) {
        h->size--;
        return h->Customers[0];
    }

    customer root = h->Customers[0];
    h->Customers[0] = h->Customers[h->size - 1];
    h->size--;
    heapify(h, 0);
    return root;
}


int main(){
    int i,flag,token=1;
    char a[ARR_SIZE];
    char ch;
    printf("Enter number of Customers(heap-capacity):");
    scanf("%d",&i);
    heap* h=make_heap(i);
    printf("POST OFFICE COUNTER\n");
    printf("1.add new cusomer\n2.serve customer\n3.print queue\n4.Exit\n");
    while(1){
        printf("Enter the choice: ");
        fflush(stdin);
        scanf("%d",&i);
        switch(i){
            case 1:
                do{
                    printf("Enter category (defence/differently-abled/senior-citizen/general): ");
                    fflush(stdin);
                    scanf(" %[^\n]",a);
                    customer* c=make_customer(a,token++);
                    insert_heap(h,c);
                    printf("continue adding?(y/n) ");
                    fflush(stdin);
                    scanf(" %c",&ch);
                }while(ch!='n');
                break;
            case 2:
                do{
                    customer c = extractMax(h);
                    printf("Serving customer with token number = %d\n",c.token_number);
                    printf("Category = %s\n",c.type);
                    printf("continue serving?(y/n) ");
                    fflush(stdin);
                    scanf(" %c",&ch);
                }while(ch!='n');
                break;
            case 3:
                printf("funtion in progress!!!");
                break;
            case 4:
                flag=1;
                break;
            default:
                printf("Invalid choice, please try again.\n");
                break;
        }
        if(flag==1){
            printf("Exiting the program!!\n");
            break;
        }
    }
}