#include<iostream>
using namespace std;
int main()
{
	int available[3]={5, 5, 5};
	int allocation[3][3]={{1, 2, 1}, {2, 0, 1}, {2, 2, 1}};
	int need[3][3];
	int lastProcess;
	int safeSequence[3];
	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			need[i][j]=allocation[i][j]-available[j];
		}
	}
	bool finish[3]={false, false, false};
	int count=0;
	while(count<3)
	{
		bool found=false;
		for(int i=0; i<3; i++)
		{
			if(!finish[i])
			{
				int j;
				for(j=0; j<3; j++)
				{
					if(need[i][j]>available[j])
					{
						break;
					}
				}
				if(j==3)
				{
					for(int k=0; k<3; k++)
					{
						available[k]+=allocation[i][k];
					}
					safeSequence[count++]=i;
					finish[i]=true;
					found=true;
					lastProcess=safeSequence[i];
				}
			}
		}
		if(!found)
		{
			cout<<"The system is not in a safe state."<<endl;
		}
	}
	cout<<"The system is in a safe state."<<endl;
	cout<<"The process that will finish last is P"<<lastProcess<<endl;
	return 0;
}