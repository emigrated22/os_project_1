#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
	char a[20]={"allocation.txt"};
	char b[20]={"max.txt"};
	char c[20]={"available.txt"};

int* arraysize(int typenum){
	FILE *fp;
	if(typenum==1){
	fp = fopen(a, "r");}
	else if(typenum==2){
	fp = fopen(c, "r");}
	static int result[2];
	int rcnt,pcnt;
	char tmp;
    int cnt = 1;
    int all =1;
	 while (fscanf(fp, "%c", &tmp) != EOF) {
      all++;
      if (tmp == '\n')
         cnt++;
   }
    fclose(fp); 
	pcnt = cnt;
	rcnt = all/cnt/2;
	result[0]=pcnt;
	result[1]=rcnt;
	return result;
}
int main(){
	int *size1;
	int *size2;
	size1=arraysize(1);	//alloc matrix size
	int Rowsize1=size1[0];
	int Columsize1=size1[1];	
	size2=arraysize(2);	//available matrix size
	int Rowsize2=size2[0];
	int Columsize2=size2[1];
	int allocation[Rowsize1][Columsize1];
	int max[Rowsize1][Columsize1];
	int need[Rowsize1][Columsize1];
	int available[Rowsize2][Columsize2];
	int work[Rowsize2][Columsize2];		
	printf("confirm array size: alloc(%d, %d),    avail(%d, %d)",Rowsize1,Columsize1,Rowsize2,Columsize2);
	printf("\nallocation mat \n");
	FILE *fp;
	fp=fopen("allocation.txt","r");
	for(int i=0;i<Rowsize1;i++){
		for(int j=0;j<Columsize1;j++){
			fscanf(fp,"%d",&allocation[i][j]);
		}
	}
	fp=fopen("MAX.txt","r");
	for(int i=0;i<Rowsize1;i++){
		for(int j=0;j<Columsize1;j++){
			fscanf(fp,"%d",&max[i][j]);
		}
	}
	fp=fopen("available.txt","r");
	for(int i=0;i<Rowsize2;i++){
		for(int j=0;j<Columsize2;j++){
			fscanf(fp,"%d",&available[i][j]);
			//fscanf(fp,"%d",&work[i][j]);
		}
	}
	fp=fopen("available.txt","r");
	for(int i=0;i<Rowsize2;i++){
		for(int j=0;j<Columsize2;j++){
			fscanf(fp,"%d",&work[i][j]);
		}
	}
	
	for(int i=0;i<Rowsize1;i++){
		for(int j=0;j<Columsize1;j++){
			need[i][j]=max[i][j]-allocation[i][j];
			}
	}

	for(int i=0;i<Rowsize1;i++){
		for(int j=0;j<Columsize1;j++){
			printf("%d ",allocation[i][j]);
		}
		printf("\n");
	}
			printf("max\n");
	for(int i=0;i<Rowsize1;i++){
		for(int j=0;j<Columsize1;j++){
			printf("%d ",max[i][j]);
		}
		printf("\n");
	}
			printf("available\n");
	for(int i=0;i<Rowsize2;i++){
		for(int j=0;j<Columsize2;j++){
			printf("%d ",available[i][j]);
		}
		printf("\n");
	}

		printf("need\n");
	for(int i=0;i<Rowsize1;i++){
		for(int j=0;j<Columsize1;j++){
			printf("%d ",need[i][j]);
		}
		printf("\n");
	}	
		printf("\n");
//------------------------------------------read file and make array part
//now start banker's algorithm
bool finish[Rowsize1]={false};
printf("work(");
for(int j=0;j<Columsize1;j++){
	printf("%d ",work[0][j]);
}
printf(")->");
step2:
	for(int i=0;i<Rowsize1;i++){
		if(finish[i]==false){
			int check_value=1;
			for(int j=0;j<Columsize1;j++){
				check_value=check_value*(need[i][j]<=work[0][j]);	//check all need<work if true check_value=1
			}
			if(check_value==1){//step 3
			printf("p%d ",i);
				for(int j=0;j<Columsize1;j++){
					work[0][j]=work[0][j]+allocation[i][j];
					printf("%d ",work[0][j]);
					
				}
				printf("->");
				finish[i]=true;
				goto step2;
			}
		}
	}
	int check_value2=1;
for(int i=0;i<Rowsize1;i++){
		check_value2=check_value2*finish[i];
	}
	
if(check_value2==1){
	printf("Safe state");
	request:
	printf("\nIs there any additional request?(y/n)");
	char addtional_request;
	scanf("%c",&addtional_request);
	if(addtional_request=='y'){
		printf("press the %d length of additional resource and process number\n",Columsize1);
		printf("addtional array:");
		int addi[Columsize1];	
		for(int i=0;i<Columsize1;i++){
			scanf("%d",&addi[i]);			
		}
		for(int i=0;i<Columsize1;i++){
			printf("%d",addi[i]);
		}	
		printf("process number:");
		int processnum;
		scanf("%d",&processnum);
		printf("%d",processnum);
		int checkval=1;	
		for(int i=0;i<Columsize1;i++){
			checkval=checkval*(addi[i]<=need[processnum][i]);
		}
		if(checkval==1){
			int checkval1=1;	
			for(int i=0;i<Columsize1;i++){
				checkval1=checkval1*(addi[i]<=available[processnum][i]);
			}
			if(checkval==1){
				for(int i=0;i<Columsize1;i++){
				available[processnum][i]=available[processnum][i]-addi[i];
				allocation[processnum][i]=allocation[processnum][i]+addi[i];
				need[processnum][i]=need[processnum][i]-addi[i];
				goto step2;
				}
			}
			else{
				printf("not all resources are not available");
				exit;
			}
		}
		else{
			printf("process has exceeded its maximum claim");
			exit;
		}
	}
	else if(addtional_request=='n'){
		exit;
	}
	else
	goto request;
}
else
printf("Unsafe state");
	return 0;
}

