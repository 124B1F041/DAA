#include<iostream>
#include<fstream>
#include<vector>
#include<string>
using namespace std;

void merge(vector<int>&arr,int left,int mid,int right)
{
int n1=mid-left+1;
int n2=right-mid;
vector<int>l(n1),r(n2);
for(int i=0;i<n1;i++)
   l[i]=arr[left+i];
for(int j=0;j<n2;j++)
   r[j]=arr[mid+1+j];
 int i=0;
int j=0;
int k=left;
while(i<n1 &&  j<n2){
   if(l[i]<=r[j])
     arr[k++]=l[i++];
   else
     arr[k++]=r[j++];
}
while(i<n1)
arr[k++]=l[i++];
while(j<n2)
arr[k++]=r[j++];
}
void mergesort(vector<int>&arr,int left,int right)
{
if(left<right)
{
int mid=(left+right)/2;
mergesort(arr,left,mid);
mergesort(arr,mid+1,right);
merge(arr,left,mid,right);
}
}
int main(){
ifstream file("sample_dataset.csv");
if(!file.is_open()){
	cout<<"not found"<<endl;
	return 1;
}
vector<int>numbers;
string line;
while(getline(file,line)){
	if(!line.empty())
		numbers.push_back(stoi(line));
}
file.close();
for(int num:numbers)
	cout<<num<<" ";
	cout<<endl;
	mergesort(numbers,0,numbers.size()-1);
	for(int num:numbers)
	cout<<num<<" ";

return 0;
}

