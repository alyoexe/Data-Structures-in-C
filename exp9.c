#include<stdio.h>
#include<string.h>
#define MAXSIZE 10
typedef struct{	
	char arr[20][MAXSIZE];
	int front;
	int rear;
}Queue;
void makeq(Queue *q){
	q->front=q->rear=-1;
}
void printq(Queue *q,int p){
	int y=q->rear;
	int x=q->front;
	if(p==1){
		while(x!=y){
			printf("%s ",q->arr[x]);
			x=(x+1)%MAXSIZE;
		}
		printf("%s ",q->arr[x]);
		printf("\n");
	}
	else{
		while(x!=y){
			printf("%s ",q->arr[y]);
			y=(y+MAXSIZE-1)%MAXSIZE;
		}
		printf("%s ",q->arr[y]);
		printf("\n");

	}
}
void pushrear(Queue *q,char item[]){
	if(q->front==-1){
		strcpy(q->arr[++q->rear],item);
		q->front++;
		printq(q,2);
	}
	else{
		if((q->rear+1)%MAXSIZE==q->front){
			printf("Queue overflow\n");
		}
		else{
			q->rear=(q->rear+1)%MAXSIZE;
			strcpy(q->arr[q->rear],item);
			printq(q,2);
		}
	}
}
void pushfront(Queue *q,char item[]){
	if(q->front==-1){
		strcpy(q->arr[++q->rear],item);
		q->front++;
		printq(q,1);
	}
	else{
		if((q->rear+1)%MAXSIZE==q->front){
			printf("Queue overflow\n");
		}
		else{
			q->front=(q->front+MAXSIZE-1)%MAXSIZE;
			strcpy(q->arr[q->front],item);
			printq(q,1);
		}
	}
}
void popfront(Queue *q){
	if(q->front==-1){
		printf("Queue underflow\n");
	}
	else{
		printf("student selected is %s\n",q->arr[q->front]);
		if(q->front==q->rear){
			q->front=q->rear=-1;
		}
		else{
			q->front=(q->front+1)%MAXSIZE;
		}	
	}
}
void poprear(Queue *q){
	if(q->front==-1){
		printf("Queue underflow\n");
	}
	else{
		printf("student selected is %s\n",q->arr[q->rear]);
		if(q->front==q->rear){
			q->front=q->rear=-1;
		}
		else{
			q->rear=(q->rear+MAXSIZE-1)%MAXSIZE;
		}	
	}
}

int main(){
	Queue q;
	makeq(&q);
	int n,m;
	char l[20];
	while(1){
		printf("1.Choose a student\n");
		printf("2.Seat a latecomer\n");
		printf("enter choice: ");
		scanf("%d",&n);
		if(n==1){
			printf("pick a side (1.right)(2.left): ");
			scanf("%d",&m);
			if(m==1){
				popfront(&q);
			}
			else{
				poprear(&q);
			}
		}
		else if(n==2){
			printf("Enter name: ");
			scanf("%s[^\n]",l);
			printf("pick a side (1.right)(2.left): ");
			scanf("%d",&m);
			if(m==1){
				pushfront(&q,l);
			}
			else{
				pushrear(&q,l);
			}
		}
		else{
			printf("Invalid choice\n");
		}
		printf("\n");
	}
	return 0;
}