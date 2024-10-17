#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#define MAX_SIZE 10

typedef struct node{
    char data;
    struct node *left;
    struct node *right;
}node;

node* make_node(char data){
    node* newnode=(node*)malloc(sizeof(node));
    newnode->data=data;
    newnode->left=NULL;
    newnode->right=NULL;
    return newnode;
}

int precedence(char op) {
	switch (op) {
    	case '+':
    	case '-':
        	return 1;
    	case '*':
    	case '/':
        	return 2;
    	default:
        	return 0;
	}
}

typedef struct{ 
    node* arr[MAX_SIZE];
    int top;
}stack;

void make_stack(stack* s){
    s->top=-1;
}

void push_stack(stack* s,node* ele){
    if(s->top==MAX_SIZE-1){
        return;
    }
    s->arr[++s->top]=ele;
}

node* pop_stack(stack* s) {  
    if (s->top == -1) {  
        return NULL;
    }  
    return s->arr[s->top--];  
}

node* top_stack(stack *s){
    if (s->top == -1) {  
        return NULL;
    }
    return s->arr[s->top];
}

int isempty(stack *s){
    if(s->top==-1)
        return 1;
    return 0;
}

void make_tree(stack* opstack,stack* nodestack){
    node*n,*r,*l;
    n=pop_stack(opstack);
    r=pop_stack(nodestack);
    l=pop_stack(nodestack);
    if(n==NULL||r==NULL||l==NULL){
        return;
    }
    n->right=r;
    n->left=l;
    push_stack(nodestack,n);
}

int isoperator(char ch){
    char operators[] = "+-*/";
    if (strchr(operators, ch) != NULL) {
        return 1;
    } 
    return 0;
}

void printInorder(node* node){
    if (node == NULL){
        return;
    }
    else{
        printInorder(node->left);
        printf("%c ", node->data);
        printInorder(node->right);
    }
}


void printPrefix(node* root) {
    if (root == NULL) {
        return;
    }
    printf("%c ", root->data);
    printPrefix(root->left);
    printPrefix(root->right);
}

void printPostfix(node* root) {
    if (root == NULL) {
        return;
    }
    printPostfix(root->left);
    printPostfix(root->right);
    printf("%c ", root->data);
}

int main(){
    printf("Construct expression treee: ");
    printf("\nDisplay infix and postfix notation: ");
    char exp[100];
    scanf("%[^\n]",exp);
    //printf("%s",exp);
    int size = strlen(exp);
    stack opstack , nodestack ;
    make_stack(&opstack);
    make_stack(&nodestack);
    for(int i=0;i<size;i++){
        if(isalnum(exp[i])){
            node* a=make_node(exp[i]);
            push_stack(&nodestack,a);  
        }
        else if(exp[i]=='('){
            node* a=make_node(exp[i]);
            push_stack(&opstack,a);
        }
        else if(exp[i]==')'){
            char op = top_stack(&opstack)->data;
            while(op!='('){
                make_tree(&opstack,&nodestack);
                op = top_stack(&opstack)->data;
            }
            pop_stack(&opstack);
        }
        else if(isoperator(exp[i])){
            node* a = make_node(exp[i]);
            while(!isempty(&opstack) && precedence(top_stack(&opstack)->data) >= precedence(exp[i])){
                make_tree(&opstack, &nodestack);
            }
            push_stack(&opstack, a);
        }
        else{
            printf("invlaid characters");
        }
    }
    while(!isempty(&opstack)){
        make_tree(&opstack,&nodestack);
    }
    node* answer=top_stack(&nodestack);

    printf("The given equation is : ");
    printInorder(answer);

    printf("\nPrefix notation :");
    printPrefix(answer);

    printf("\npostfix notation :");
    printPostfix(answer);


}