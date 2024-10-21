
#include <stdio.h>
typedef struct{
	int exp;
	int coef;
}poly;
poly polyy[100];
void print(){
	printf("hello");
	for(int i =0;i<30;i++){
		printf("%d",polyy[i].exp);
		printf("%d\n",polyy[i].coef);
	}
}
void printt(int a,int b){
	int i;
	for(i=a;i<b;i++){
		if (polyy[i].exp==0){
			printf("%d +",polyy[i].coef);
		}
		else{
			printf("%dX^%d +",polyy[i].coef,polyy[i].exp);
		}
	}
	if (polyy[i].exp==0){
		printf("%d ",polyy[i].coef);
	}
	else{
		printf("%dX^%d ",polyy[i].coef,polyy[i].exp);
	}

}

int polyadd(int astart,int afinish,int bstart,int bfinish,int avail){
	int i=astart,j=bstart,k=avail;
	while(i<=afinish&&j<=bfinish){
		if(polyy[i].exp>polyy[j].exp){
			polyy[k].exp=polyy[i].exp;
			polyy[k].coef=polyy[i].coef;
			k++;
			i++;
		}
		else if(polyy[i].exp<polyy[j].exp){
			polyy[k].exp=polyy[j].exp;
			polyy[k].coef=polyy[j].coef;
			k++;
			j++;
		}
		else{
			if(polyy[i].coef+polyy[j].exp==0){
				i++;
				j++;
			}
			else {
				polyy[k].exp=polyy[j].exp;
				polyy[k].coef=polyy[i].coef+polyy[j].coef;
				i++;
				j++;
				k++;
			}
		}
	}
	while(i<=afinish){
		polyy[k].exp=polyy[i].exp;
		polyy[k].coef=polyy[i].coef;
		k++;
		i++;
	}
	while(j<=bfinish){
		polyy[k].exp=polyy[j].exp;
		polyy[k].coef=polyy[j].coef;
		k++;
		j++;
	}
	return k;
}
int main(){
	int e,c,i=0;
	int astart,afinish,bstart,bfinish,avail;	
	astart=0;
	printf("Enter the first polynomial in decreasing power");
	do{ 
		scanf("%d",&e);
		polyy[i].exp=e;
		scanf("%d",&polyy[i].coef);
		i++;
	}while(e);
	afinish=i-1;
	bstart = afinish+1;
	printf("Enter the second polynomail in decreasing power");
	do{ 
		scanf("%d",&e);
		polyy[i].exp=e;
		scanf("%d",&polyy[i].coef);
		i++;
	}while(e);
	bfinish=i-1;
	avail =bfinish+1;
	//printf("%d %d %d %d %d \n",astart,afinish,bstart,bfinish,avail);
	//polyadd(astart,afinish,bstart,bfinish,avail);
	int last =polyadd(astart,afinish,bstart,bfinish,avail);
	//print();
	printt(astart,avail-1);
	printf(" = ");
	printt(avail,last-1);
}
