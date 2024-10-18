#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int digit;
    struct node* next;
}sll;

typedef struct {
    sll* next;
}header;


sll* make_node(int x){
    sll* temp =(sll*)malloc(sizeof(sll));
    temp->digit=x;
    temp->next=NULL;
    return temp;
}

header* make_head(){
    header* head= (header*)malloc(sizeof(header));
    if(head!=NULL) head->next=NULL;
    return head;
}

void add_node(header* head,sll* node){
    int x;
    if(head->next==NULL){
        head->next=node;
    }
    else{
        sll* p = head->next;
        while(p->next!=NULL){
            p=p->next;
        }
        p->next=node;
    }
}

void reverse_sll(header* head){
    if(head->next!=NULL){
        sll* current=head->next;
        sll* prev=NULL;
        sll* next=NULL;
        while(current!=NULL){
            next=current->next;
            current->next=prev;
            prev=current;
            current=next;
        }
        head->next=prev;
    }
}

void add(header* head1, header* head2, header* head3){
    int x=0,carry=0;
    sll* p=NULL;
    sll* q=NULL;
    if(head1->next!=NULL){
        p= head1->next;
    }
    if(head2->next!=NULL){
        q= head2->next;
    }
    while(p!=NULL&&q!=NULL){
        if((p->digit+q->digit)>9){
            x=(p->digit+q->digit)%10;
        }
        else{
            x=(p->digit+q->digit);
        }
        //printf("%d+%d\n",x,carry);
        add_node(head3,make_node(x+carry));
        carry=(p->digit+q->digit)/10;
        //printf("%d",carry);
        p=p->next;
        q=q->next;
    }
    while(p!=NULL){
        x=p->digit;
        //printf("%d+%d\n",x,carry);
        add_node(head3,make_node(x+carry));
        carry=0;
        p=p->next;
    }
    while (q!=NULL){
        x=q->digit;
        //printf("%d+%d\n",x,carry);
        add_node(head3,make_node(x+carry));
        carry=0;
        q=q->next;
    }
    if(carry!=0){
        add_node(head3,make_node(carry));
    }
}

void print_node(header* head){
    if(head->next!=NULL){
        sll* p=head->next;
        printf("%d",p->digit);
        p=p->next;
        while(p!=NULL){
            printf("%d",p->digit);
            p=p->next;
        }
    }
    printf("\n");
}



int main(){
    int x,count;
    printf("Enter the number of digits in 1st interger: ");
    scanf("%d",&count);
    printf("Enter 1st integer(digit by digit)\n");
    header* head1 =make_head();
    while(count--){
        printf("Enter digit: ");
        scanf("%d",&x);
        add_node(head1,make_node(x));
    }
    printf("Enter the number of digits in 2nd interger: ");
    scanf("%d",&count);
    printf("Enter 2nd integer(digit by digit)\n");
    header* head2 =make_head();
    while(count--){
        printf("Enter digit: ");
        scanf("%d",&x);
        add_node(head2,make_node(x));
    }
    
    
    header* head3 =make_head();
    

    //print_node(head1);
    reverse_sll(head1);
    //print_node(head1);
    //print_node(head2);
    reverse_sll(head2);
    //print_node(head2);
    add(head1,head2,head3);
    printf("Sum of 2 integers is : ");
    //print_node(head3);
    reverse_sll(head3);
    print_node(head3);





}