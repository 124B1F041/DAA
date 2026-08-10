#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

struct Retail
{
    string invoice;
    string date;
};

void merge(vector<Retail> &a, int left, int mid, int right)
{
    vector<Retail> temp;

    int i = left;
    int j = mid + 1;

    while(i <= mid && j <= right)
    {
        if(a[i].date <= a[j].date)
            temp.push_back(a[i++]);
        else
            temp.push_back(a[j++]);
    }

    while(i <= mid)
        temp.push_back(a[i++]);

    while(j <= right)
        temp.push_back(a[j++]);

    for(int k = 0; k < temp.size(); k++)
        a[left + k] = temp[k];
}

void mergeSort(vector<Retail> &a, int left, int right)
{
    if(left < right)
    {
        int mid = (left + right) / 2;

        mergeSort(a, left, mid);
        mergeSort(a, mid + 1, right);

        merge(a, left, mid, right);
    }
}

int main()
{
    ifstream fin("/home/nisl21/Mergesort/online_retail_II.csv");

    if(!fin)
    {
        cout<<"File not found"<<endl;
        return 0;
    }

    vector<Retail> records;
    string line;

    getline(fin,line);

    while(getline(fin,line))
    {
        Retail r;

        // Invoice = before first comma
        int first = line.find(',');
        r.invoice = line.substr(0, first);

        // Find commas from the end
        int c1 = line.rfind(',');
        int c2 = line.rfind(',', c1 - 1);
        int c3 = line.rfind(',', c2 - 1);
        int c4 = line.rfind(',', c3 - 1);

        // InvoiceDate is between c4 and c3
        r.date = line.substr(c4 + 1, c3 - c4 - 1);

        records.push_back(r);
    }

    fin.close();

    cout << "Total Records Read : " << records.size() << endl;

    mergeSort(records,0,records.size()-1);

    cout << "\nInvoice\t\tInvoice Date\n";
    cout << "---------------------------------------------\n";

    for(int i=0;i<20 && i<records.size();i++)
    {
        cout << records[i].invoice << "\t"
             << records[i].date << endl;
    }

    return 0;
}
