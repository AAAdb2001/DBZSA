#include <iostream>
#include <omp.h>
using namespace std;
int main()
{
    int n;
    cout << "Enter the size of the array:- ";
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
    }
    omp_set_num_threads(4);
    int min_val = INT_MAX;
#pragma omp parallel
    for (int i = 0; i < n; i++)
    {
        if (arr[i] < min_val)
        {
            min_val = arr[i];
        }
    }

    int max_val = INT_MIN;
#pragma omp parallel
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
    }

    int sum = 0;
#pragma omp parallel
    for (int i = 0; i < n; i++)
    {
        sum = sum + arr[i];
    }

    double avg = sum;
    avg = avg / n;
    cout << "Min:- " << min_val << endl;
    cout << "Max:- " << max_val << endl;
    cout << "Sum:- " << sum << endl;
    cout << "Avg:- " << avg << endl;
    return 0;
}