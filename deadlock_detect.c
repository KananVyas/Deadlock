/*
    Deadlock Detection Algorithm
   


*/


#include<stdio.h>
#include<stdlib.h>

//Initialzing resource matrix
int max[10][10];
int alloc[10][10];
int need[10][10];
int avail[10];
int n,r;
// Function initialized
void input();
void display();
void calculation();

int main()
{
               int i,j;
               printf("Algorithm for deadlock detection:\n");
               input(); 	//Calling function input
               display(); 	//Calling function display
               calculation();   //Calling function calculation
               
               return 0;
}

//Function for taking inputs for given matrixs
void input()
{
               int i,j;
               printf("Enter the no of Processes:\t");
               scanf("%d",&n);
               printf("Enter the no of resource instances:\t");
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
//Function for displaying matrixs
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
//Function for checking if deadlock can occur or not
void calculation()
{
  int finish[100],temp,need[100][100],flag=1,k,c1=0;
  int dead[100];
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
                                                                                          
                                    if(finish[i]==1)
                                    {
                                     i=n;
                                    }
                                    }
                                    }
                              }
                             }
                }
    j=0;
    flag=0;
    for(i=0;i<n;i++)
                {
                    if(finish[i]==0)
                     {
                         dead[j]=i; //storing the process which is not finished
                         j++;
                         flag=1;
                      }
               }
               if(flag==1)
               {
                  printf("\n\nThere is a deadlock and deadlock causing processes are:\n");
                   for(i=0;i<j+1;i++)
                    {
                        printf("P%d\t",(dead[i]+1));
                    }
               }
               else
               {
                              printf("\nNo Deadlock Occured");
               }  
}
