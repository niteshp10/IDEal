#include<stdio.h>
#include<stdlib.h>
#include<omp.h>

float matres[2000][2000];
int size,i,j;
void multiply(int size,float matrix1[][size],float matrix2[][size]);
void print(int size,float approx[size][0]);
float diff(int size,float mat1[size][0],float mat2[size][0]);

void main()
{
    FILE *fin,*fout;
    fin=fopen("input1.txt","r");
    fout=fopen("output1.txt","w");

    fscanf(fin,"%d",&size);
    int a[size][size+1];
    printf("%d \n",size);
    int m=size;

    int c[size][size];
    float diaginv[size][size],zerdiag[size][size],temp[size][size],b[size][size];
    float approx[size][size],matres[size][size];
    int row,col,f=0,s=0,i,k,j,ictr;

    for(i=0; i<size; i++)
    {
        for(j=0; j<=size; j++)
        {
            fscanf(fin,"%d",&a[i][j]);
            printf("%d ",a[i][j]);
        }
        printf("\n");
    }

    for(i=0; i<size; i++)
    {
        for(j=0; j<=size; j++)
        {
            fprintf(fout,"%d ",a[i][j]);

        }
        fprintf(fout,"\n");
    }








    for(i=0; i<size; i++)
    {

        {
            c[i][0]=a[i][size];
            printf("%d ",c[i][0]);
        }
    }



    for(i=0; i<size; i++)
    {

        {
            fprintf(fout,"%d\n",c[i][0]);

        }

    }

    for(row=0; row<size; row++)
    {
        for(col=0; col<size; col++)
        {


            if(row==col)
            {
                diaginv[row][col]=1/(float)a[row][col];
                zerdiag[row][col]=0;
            }


            else if(row!=col)
            {
                diaginv[row][col]=0;
                zerdiag[row][col]=a[row][col];
            }

            printf("%f ",diaginv[row][col]);

        }
        printf("\n");
    }


    for(i=0; i<size; i++)
    {
        for(j=0; j<size; j++)
        {
            printf("%f ",zerdiag[i][j]);
        }
        printf("\n");
    }

    int ctrr=0,ctr=0,move,result;
    #pragma omp parallel while
    while(ctrr<=10)
    {

        for(ctr=0; ctr<size; ctr++)
        {
            matres[ctr][0]=0;
            for(move=0; move<size; move++)
            {
                matres[ctr][0]=matres[ctr][0]+zerdiag[ctr][move]*approx[move][0];
            }
        }

        for(row=0; row<size; row++)
            temp[row][0]=c[row][0]-matres[row][0];
        printf("The Value after iteration %d is\n",ctrr);
        for(ctr=0; ctr<size; ctr++)
        {
            approx[ctr][0]=0;
            for(move=0; move<size; move++)
            {
                approx[ctr][0]=approx[ctr][0]+diaginv[ctr][move]*temp[move][0];
            }
            //printf("%f\n",approx[ctr][0]);
        }
        print(size,approx);

        result=diff(size,b,approx);
        for(ctr=0;ctr<size;ctr++)
        {
            b[ctr][0]=approx[ctr][0];
        }
        ctrr++;
    }


}

void print(int size,float approx[size][0])
{
    int row;
    FILE *fout;
    fout=fopen("output1.txt","a");
    for(row=0; row<size; row++)
        {
            fprintf(fout,"%.3f\n",approx[row][0]);
        }
}

float diff(int size,float mat1[size][0],float mat2[size][0])
{
    float diffresult[size][0];
    int i,flag=0;
    for(i=0;i<size;i++)
    {
        diffresult[i][0]=mat2[i][0]-mat1[i][0];
        printf("%f ",diffresult[i][0]);

    }




}

