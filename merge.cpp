#include <iostream>
#include <omp.h>
using namespace std;
void Merge(int arr[], int l, int mid, int h)
{
    int i, j, k;
    i = l;
    j = mid + 1;
    k = l;
    int arr_temp[h + 1];
    while (i <= mid && j <= h)
    {
        if (arr[i] < arr[j])
        {
            arr_temp[k++] = arr[i++];
        }
        else
        {
            arr_temp[k++] = arr[j++];
        }
    }
    while (i <= mid)
    {
        arr_temp[k++] = arr[i++];
    }
    while (j <= h)
    {
        arr_temp[k++] = arr[j++];
    }

    for (int i = l; i <= h; i++)
    {
        arr[i] = arr_temp[i];
    }

    // for(int i=0;i<n;i++){
    //     cout<<arr[i]<<" ";
    // }
}

void Imerge_sort(int A[], int n)
{
    int p;
    double start = omp_get_wtime();
    for (p = 2; p <= n; p = p * 2)
    {
#pragma omp parallel num_threads(1000)
        {
            for (int i = 0; i + p - 1 < n; i = i + p)
            {
#pragma omp critical
                {
                    int l = i;
                    int h = i + p - 1;
                    int mid = (l + h) / 2;
                    Merge(A, l, mid, h);
                }
            }
        }
    }
    if (p / 2 < n)
    {
#pragma omp critical
        Merge(A, 0, p / 2 - 1, n - 1);
    }
    double end = omp_get_wtime();
    cout << "Sequntial exection time " << end - start << endl;
}

void Imerge_sort_p(int A[], int n)
{
    int p;
    double start = omp_get_wtime();
    for (p = 2; p <= n; p = p * 2)
    {
#pragma omp parallel num_threads(1000)
        {
#pragma omp parallel
            {
                for (int i = 0; i + p - 1 < n; i = i + p)
                {
                    int l = i;
                    int h = i + p - 1;
                    int mid = (l + h) / 2;
                    Merge(A, l, mid, h);
                }
            }
        }
    }
    if (p / 2 < n)
    {
#pragma omp critical
        Merge(A, 0, p / 2 - 1, n - 1);
    }
    double end = omp_get_wtime();
    cout << "Parallel exection time " << end - start << endl;
}
int main()
{
    int arr1[] = {2, 5, 8, 12, 3, 6, 7, 10};
    int n = sizeof(arr1) / sizeof(arr1[0]);
    Imerge_sort(arr1, n);
    Imerge_sort_p(arr1, n);
    for (int i = 0; i < n; i++)
    {
        cout << arr1[i] << " ";
    }
    return 0;
}