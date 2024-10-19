#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_SIZE 25
typedef struct{
    char word[MAX_SIZE];
    char meaning[MAX_SIZE];
}pair;





typedef struct node{
    pair p;
    struct node* left;
    struct node* right;
}node;

node* make_node(char* a,char* b){
    node* temp =(node*)malloc(sizeof(node));
    if(temp==NULL){
        printf("Memory Allocation failed!!");
        return NULL;
    }
    strcpy(temp->p.word,a);
    strcpy(temp->p.meaning,b);
    temp->left=temp->right=NULL;
    return temp;
}

node* search(node* root,char* a){
    if(root==NULL||strcmp(root->p.word,a)==0){
        return root;
    }
    if(strcmp(root->p.word,a)>0){
        return search(root->left,a);
    }
    else if(strcmp(root->p.word,a)<0){
        return search(root->right,a);
    }
}

node* insert(node* root,char* a,char* b){
    if(root==NULL){
        return make_node(a,b);
    }
    if(strcmp(root->p.word,a)>0){
        root->left=insert(root->left,a,b);
    }
    else if(strcmp(root->p.word,a)<0){
        root->right=insert(root->right,a,b);
    }
    return root;
}

node* findmin(node* root){
    if(root==NULL){
        return NULL;
    }
    else if(root->left!=NULL){
        return findmin(root->left);
    }
    return root;
}

node* delete(node*root, char* a){
    if (root == NULL) {
        return NULL;
    }
    if(strcmp(root->p.word,a)<0){
        root->right= delete(root->right,a);
    }
    else if(strcmp(root->p.word,a)>0){
        root->left= delete(root->left,a);
    }
    else{
        if(root->left==NULL&&root->right==NULL){
            free(root);
            return NULL;
        }
        else if(root->left==NULL||root->right==NULL){
            node* temp;
            if(root->left==NULL){
                temp=root->right;
            }
            else{
                temp=root->left;
            }
            free(root);
            return temp;
        }
        else{
            node* temp =findmin(root->right);
            strcpy(root->p.word, temp->p.word);
            strcpy(root->p.meaning, temp->p.meaning);
            root->right= delete(root->right,temp->p.word);
        }
    }
    return root;
}
void inOrder(node* root)
{
    if (root != NULL) {
        inOrder(root->left);
        printf(" word:%s,meaning:%s \n", root->p.word,root->p.meaning);
        inOrder(root->right);
    }
}

int main(){
    int i,temp,flag=0;
    char ch;
    char a[MAX_SIZE],b[MAX_SIZE];
    node* bst=NULL;
    printf("DICTIONARY\n");
    printf("1.Search a word\n2.Insert a {word,meaning} pair\n3.Delete a {word,meaning} pair\n4.Print the dictionary\n5.Exit\n");
    while(1){
        printf("Enter the choice: ");
        fflush(stdin);
        scanf("%d",&i);
        switch(i){
            case 1:
                printf("Enter word to search: ");
                fflush(stdin);
                scanf(" %[^\n]",a);
                node* tempp=search(bst,a);
                if(tempp!=NULL){
                    printf("Meaning of %s is: %s\n",a,tempp->p.meaning);
                }
                else{
                    printf("word not found!\n");
                }
                break;
            case 2:
                do{
                    printf("Enter the word to insert: ");
                    fflush(stdin);
                    scanf(" %[^\n]",a);
                    printf("Enter the meaning: ");
                    fflush(stdin);
                    scanf(" %[^\n]",b);
                    bst = insert(bst,a,b);
                    printf("continue adding?(y/n) ");
                    fflush(stdin);
                    scanf(" %c",&ch);
                }while(ch!='n');
                inOrder(bst);
                break;
            case 3:
                printf("Enter word to delete: ");
                fflush(stdin);
                scanf(" %[^\n]",a);
                bst=delete(bst,a);
                break;
            case 4:
                inOrder(bst);
                break;
            case 5:
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
