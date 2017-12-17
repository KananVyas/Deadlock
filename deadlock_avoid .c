//Algorithm for deadlock avoidance
#include<stdio.h>
//Initialization of matrix
int max[10][10];
int alloc[10][10];
int need[10][10];
int avail[10];
int n,r;

//Initialization of function
void input();
void display();
void calculation();
//Main function
int main()
{
 int i,j;
 printf("Bankers Algorithm:\n");
 input(); // input function called
 display(); //display function called
 calculation(); //Calculation function called

 return 0;
}
//Function for taking inputs
void input()
{
 int i,j;
 printf("Enter the no of Processes\t");
 scanf("%d",&n);
 printf("Enter the no of resources instances\t");
 scanf("%d",&r);
 printf("Enter the Max Matrix\n");
 for(i=0;i<n;i++)
 {
  for(j=0;j<r;j++)
  {
   scanf("%d",&max[i][j]);
  }
 }
 printf("Enter the Allocation Matrix\n");
 for(i=0;i<n;i++)
 {
  for(j=0;j<r;j++)
  {
   scanf("%d",&alloc[i][j]);
  }
 }
 printf("Enter the available Resources\n");
 for(j=0;j<r;j++)
 {
  scanf("%d",&avail[j]);
 }
}
//Function for displaying matrix
void display()
{
 int i,j;
 printf("Process\t Allocation\t Max\t Available\t");
 for(i=0;i<n;i++)
 {
  printf("\nP%d\t   ",i+1);
  for(j=0;j<r;j++)
  {
   printf("%d ",alloc[i][j]);
  }
  printf("\t");
  for(j=0;j<r;j++)
  {
   printf("%d ",max[i][j]); 
  }
  printf("\t");
  if(i==0)
  {
   for(j=0;j<r;j++)
   printf("%d ",avail[j]);
  }
 }
}
//Function for calculating bankers algorithm
void calculation()
{
 int finish[100],temp,need[100][100],flag=1,k,c1=0;
 int safe[100];
 int i,j;
 for(i=0;i<n;i++)
 {
  finish[i]=0;
 }
 //find need matrix
 for(i=0;i<n;i++)
 {
  for(j=0;j<r;j++)
  {
   need[i][j]=max[i][j]-alloc[i][j];
  }
 }
 printf("\n");
 while(flag)
 {
  flag=0;
   for(i=0;i<n;i++)
  {
   int c=0;
   for(j=0;j<r;j++)
   {
    if((finish[i]==0)&&(need[i][j]<=avail[j]))
    {
       c++;
     if(c==r)
     {
      for(k=0;k<r;k++)
      {
       avail[k]+=alloc[i][j];
       finish[i]=1;
       flag=1;
           }
      printf("P%d->",i);
      if(finish[i]==1)
      {
       i=n;
      }
           }
    }
   }
    }
  }
  for(i=0;i<n;i++)
  {
  if(finish[i]==1)
  {
   c1++;
  }
  else
  {
   printf("P%d->",i+1);
  }
 }
 if(c1==n)
 {
  printf("\n The system is in safe state");
 }
 else
 {
  printf("\n Process are in dead lock");
  printf("\n System is in unsafe state");
 } 
}
