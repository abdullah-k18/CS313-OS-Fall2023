#include<iostream>
using namespace std;
int main()
{
	float length, width, area, perimeter;
	cout<<"Enter the length of rectangle: ";
	cin>>length;
	cout<<"Enter the width of rectangle: ";
	cin>>width;
	area=length*width;
	cout<<"Area of Rectangle= "<<area<<endl;
	perimeter=2*(length+width);
	cout<<"Perimeter of Rectangle= "<<perimeter;
	return 0;
}