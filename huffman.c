#include<stdio.h>
#include<stdlib.h>
#include<math.h>
void display(float desp[][20],int count1,int col,int r)
{
	int i,j,k=0;
	for(i=0;i<count1;i++)
	{
		if(i==(r+(r-1)*k))
		{
			col--;
			k++;
		}
		for(j=0;j<col;j++)
			printf("%0.2f\t",desp[i][j]);
		printf("\n");
	}
}
void sort(float p[],float desp[][20],int count,int col)
{
	int i,j;
	float temp;
	for(i=0;i<count-1;i++)
	{
		for(j=i+1;j<count;j++)
		{
			if(p[i]<p[j])
			{
				temp=p[i];
				p[i]=p[j];
				p[j]=temp;
			}
		}
		desp[i][col]=p[i];
	}
	desp[i][col]=p[i];
}
int lendist(float desp[][20],float len[20][2],char code[][10],int count1,int col,int r)
{
	int i,j,k=0,ele=0,l,m;
	float add;
	char c[10],temp[10];
	for(j=col-1;j>=0;j--,k++)
	{
		if(k==0)
		{
			for(i=0;i<(r+(r-1)*k);i++)
			{
				len[ele][0]=desp[i][j];
				len[ele][1]=1;
				sprintf(c,"%d",i);
				strcpy(code[ele],c);
				ele++;
			}
		}
		else
		{
			add=0;
			for(i=(r+(r-1)*k)-1,l=0;l<r;i--,l++)
			{
				add+=desp[i][j];
			}
			for(m=0;m<ele;m++)
			{
				if(len[m][0]==add)
				{
					for(i=(r+(r-1)*k)-r,l=0;l<r;i++,l++)
					{
						len[ele][0]=desp[i][j];
						len[ele][1]=len[m][1]+1;
						sprintf(c,"%d",l);
						sprintf(temp,"%s",code[m]);
						strcpy(code[ele],strcat(temp,c));
						ele++;
					}
					break;
				}
			}
		}	
	}
	printf("\n\nTable of Probability with corresponding length:\n");	
	for(l=0;l<ele;l++)
		printf("%f\t%.0f\t%s\n",len[l][0],len[l][1],code[l]);
	return ele;
}
void main()
{
	int i,j,k,mes,count,count1,flag,addblankm=0,r,col=0,ele;
	float p[20]={},desp[20][20]={},temp,entropy=0,len[20][2],avlen=0,eff,red;
	char code[20][10];
	printf("Enter the number of messages:\t");
	scanf("%d",&count);
	printf("\nEnter %d number of probabilities:\t",count);
	for(i=0;i<count;i++)
		scanf("%f",&p[i]);
	printf("\nEnter the base from 2 to 9:\t");
	scanf("%d",&r);
	for(k=0;k<20;k++)
	{
		if(count==(r+(r-1)*k))
		{
			flag++;
			break;
		}
		else
		{
			if((r+(r-1)*k)>count)
			{
				addblankm=(r+(r-1)*k)-count;
				break;
			}
		}
	}
	for(i=0;i<addblankm;i++)
		p[count++]=0.0;
	for(i=0;i<count;i++)
	{
		if(p[i]!=0)
			entropy+=(p[i]*log(p[i]));
	}
	entropy=-1*entropy/log(r);
	printf("\nThe entropy is %f.\n",entropy);
	sort(p,desp,count,col);
	col++;
	count1=count;
	while(count!=r)
	{
		temp=0;
		for(i=0;i<r;i++)
		{
			temp+=p[count-1];
			count--;
		}
		p[count++]=temp;
		sort(p,desp,count,col);
		col++;
	}
	printf("\nThe probability reduction is as follows:\n");
	display(desp,count1,col,r);
	ele=lendist(desp,len,code,count1,col,r);
	for(i=0;i<count1;i++)
	{
		for(j=0;j<ele;j++)
		{
			if(desp[i][0]==len[j][0])
			{
				avlen+=desp[i][0]*len[j][1];
				break;
			}
		}
	}
	printf("\nThe average length is: %f",avlen);
	eff=(entropy/avlen)*100;
	printf("\n\nThe efficiency is %f%%\n",eff);
	red=1-(entropy/avlen);
	printf("\nThe redundancy is %f\n",red);	
}
