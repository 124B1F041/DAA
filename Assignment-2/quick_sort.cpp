#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Movie
{
    string release_date;
    string popularity;
};

Movie movies[10000];

// Partition Function
int partition(Movie a[], int low, int high)
{
    string pivot = a[high].release_date;
    Movie temp;
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (a[j].release_date <= pivot)
        {
            i++;
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }

    temp = a[i + 1];
    a[i + 1] = a[high];
    a[high] = temp;

    return i + 1;
}

// Quick Sort
void quickSort(Movie a[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(a, low, high);

        quickSort(a, low, pi - 1);
        quickSort(a, pi + 1, high);
    }
}

int main()
{
    ifstream fin("/home/nisl21/quick sort/top10K-TMDB-movies.csv");

    if (!fin)
    {
        cout << "File not found!" << endl;
        return 0;
    }

    string line;

    // Skip header
    getline(fin, line);

    int count = 0;

    while (getline(fin, line))
    {
        int last = line.rfind(',');
        int secondLast = line.rfind(',', last - 1);
        int thirdLast = line.rfind(',', secondLast - 1);
        int fourthLast = line.rfind(',', thirdLast - 1);

        // Popularity
        movies[count].popularity =
            line.substr(fourthLast + 1, thirdLast - fourthLast - 1);

        // Release Date
        movies[count].release_date =
            line.substr(thirdLast + 1, secondLast - thirdLast - 1);

        count++;
    }

    fin.close();

    quickSort(movies, 0, count - 1);

    cout << "Release Date\tPopularity" << endl;
    cout << "----------------------------------" << endl;

    for (int i = 0; i < 20 && i < count; i++)
    {
        cout << movies[i].release_date << "\t"
             << movies[i].popularity << endl;
    }

    return 0;
}
