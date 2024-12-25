#include<iostream>
using namespace std;
int main()
{
	int units;
	float cost, cost20Percent, discountedCost;
	cout<<"Enter Number of Units Purchased: ";
	cin>>units;
	cost=units*199;
	if(units<=50)
	{
		cout<<"Cost for "<<units<<" Units is "<<cost<<"$.";
	}
	else
	{
		cost20Percent=(cost/100)*20;
		discountedCost=cost-cost20Percent;
		cout<<"Cost for "<<units<<" Units with 20 percent discount is "<<discountedCost<<"$.";
	}
	return 0;
}