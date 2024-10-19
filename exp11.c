#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int deg;
    int coeff;
    struct node* next;
}sll;

typedef struct {
    sll* next;
}header;


sll* make_node(int x,int y){
    sll* temp =(sll*)malloc(sizeof(sll));
    temp->deg=x;
    temp->coeff=y;
    temp->next=NULL;
    return temp;
}

header* make_head(){
    header* head= (header*)malloc(sizeof(header));
    if(head!=NULL) head->next=NULL;
    return head;
}

void add_node(header* head,sll* node){
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

void add_poly(header* head1,header* head2,header* head3){
    sll* p=NULL;
    sll* q=NULL;
    int x,y;
    if(head1->next!=NULL){
        p= head1->next;
    }
    if(head2->next!=NULL){
        q= head2->next;
    }

    while(p!=NULL&&q!=NULL){
        if(p->deg>q->deg){
            x=p->deg;
            y=p->coeff;
            p=p->next;
        }
        else if(q->deg>p->deg){
            x=q->deg;
            y=q->coeff;
            q=q->next;
        }
        else{
            x=p->deg;
            y=p->coeff+q->coeff;
            p=p->next;
            q=q->next;
        }
        add_node(head3,make_node(x,y));
    }
    while(p!=NULL){
        add_node(head3, make_node(p->deg, p->coeff));
        p=p->next;
    }
    while(q!=NULL){
       add_node(head3, make_node(q->deg, q->coeff));
        q=q->next;
    }
}

int check_exist(header* head, int degree,int ceofficient ){
    int flag=0;
    if(head->next!=NULL){
        sll* p=head->next;
        while(p!=NULL){
          if(p->deg==degree){
            p->coeff=p->coeff+ceofficient;
            flag =1;
            break;
          }
          p=p->next;
        }
    }
    if(flag==1){
        return 1;
    }
    return 0;
}


void mul_poly(header* head1,header* head2,header* head3){
    sll* p=NULL;
    sll* q=NULL;
    int x,y;
    if(head1->next!=NULL){
        p= head1->next;
    }
    if(head2->next!=NULL){
        q= head2->next;
    }
    while(p!=NULL){
        while(q!=NULL){
            x=p->deg+q->deg;
            y=p->coeff*q->coeff;
            if(check_exist(head3,x,y)==0){
                add_node(head3,make_node(x,y));
            }
            q=q->next;
        }
        q= head2->next;
        p=p->next;
    }

}


void print_node(header* head){
    if(head->next!=NULL){
        sll* p=head->next;
        if(p->coeff!=0)printf("%dx^%d ",p->coeff,p->deg);
        p=p->next;
        while(p->next!=NULL){
            if(p->coeff==0){
                p=p->next;
                continue;
            }
            printf("+ %dx^%d ",p->coeff,p->deg);
            p=p->next;
        }
        if(p->coeff!=0)printf(" + %dx^%d ",p->coeff,p->deg);
    }
    printf("\n");
}

int main(){
    int x,y;
    printf("Enter 1st polynomial(till degree is 0): \n");
    header* head =make_head();
    do{
        printf("Enter degree: ");
        scanf("%d",&x);
        printf("Enter coefficient: ");
        scanf("%d",&y);
        add_node(head,make_node(x,y));
    }while(x!=0);
    printf("Enter 2nd polynomial(till degree is 0): \n");
    header* head1 =make_head();
    do{
        printf("Enter degree: ");
        scanf("%d",&x);
        printf("Enter coefficient: ");
        scanf("%d",&y);
        add_node(head1,make_node(x,y));
    }while(x!=0);
    header* head2 =make_head();
    add_poly(head,head1,head2);
    //printf("Multiplication : ");
    header* head3 =make_head();
    mul_poly(head,head1,head3);
    print_node(head);
    print_node(head1);
    print_node(head2);
    print_node(head3);
    
}