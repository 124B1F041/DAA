#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;
void sort(vector<int>&arr)
{
	int n=arr.size();
	for(int i=0;i<n-1;i++)
	{
		for (int j=0;j<n-1-i;j++)
		{
			if(arr[j]>arr[j+1])
			{
				int temp=arr[j];
				arr[j]=arr[j+1];
				arr[j+1]=temp;
			}}}}
int main()
{
	ifstream file("sample_dataset.csv");
	if (!file.is_open())
	{
		cout<<"error"<<endl;
		return 1;
	}
	vector<int> numbers;
	string line;
	while(getline(file,line)){
		if(!line.empty()){
			numbers.push_back(stoi(line));
		}}
	file.close();
	for(int num:numbers){
		cout<<num<<" ";
	}
	sort(numbers);
	for(int num:numbers)
	{
		cout<<num<<" ";
	}
	return 0;
}
