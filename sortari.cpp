#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>

using namespace std;
using namespace std::chrono;

ifstream fin("input.txt");
ofstream fout("output.txt");

int arr_length, maximum;
vector<int> v(100000000), cp(100000000);

void vector_copy(int n) {
    for (int i = 0; i < n; i++) {
        v[i] = cp[i];
    }
}

void GenerateTest(int length, int max_no)
{
    srand(time(NULL));
    for (int i = 0; i < length; i ++)
    {
        if (max_no <= RAND_MAX){
            int a = rand() % max_no + 1;
            // v.push_back(a);
            v[i] = a;
            if (a > maximum)
                maximum = a;
        }
        else {
            int max_factor = max_no / RAND_MAX;
            int a = rand() % RAND_MAX + 1;
            int aux = rand() % max_factor + 1;
            a *= aux;
            // v.push_back(a);
            v[i] = a;
            if (a > maximum)
                maximum = a;
        }
    }
}

void CountRadixSort (int n, int exp)
{
    vector<int> iesire(n+1);
    int frecventa[10] = {0};

    for (int i = 0; i < n; i ++)
        frecventa[(v[i] / exp) % 10]++;

    for (int i = 1; i < 10; i ++)
        frecventa[i] += frecventa[i - 1];

    for (int i = n - 1; i >= 0; i--){
        iesire[frecventa[(v[i] / exp) % 10] - 1] = v[i]; 
        frecventa[(v[i] / exp) % 10]--;
    }

    for (int i = 0; i < n; i++) 
        v[i] = iesire[i];
}

void RadixSort (int n)
{
    int maxi = 0;
    for (int i = 0; i < n; i ++)
        if (v[i] > maxi)
            maxi = v[i];

    for (int p = 1; maxi / p > 0; p *= 10) 
        CountRadixSort(n, p);
}

void Merge (int s, int m, int d)
{
    vector<int> copie(d-s+1);
    int i = s, j = m + 1, k = 0;

    while (i <= m && j <= d){
        if (v[i] > v[j]){
            copie[k] = v[j];
            k ++;
            j ++;
        }
        else{
            copie[k] = v[i];
            k ++;
            i ++;
        }
    }
    while (i <= m){
        copie[k] = v[i];
        k ++;
        i ++;
    }
    while (j <= d){
        copie[k] = v[j];
        k ++;
        j ++;
    }

    k = 0;
    for (int x = s; x <= d; x ++)
    {
        v[x] = copie[k];
        k ++;
    }
}

void MergeSort (int s, int d)
{
    if (s >= d) return;

    int m = s + (d - s) / 2;
    MergeSort(s, m);
    MergeSort(m+1, d);
    Merge(s, m, d);
}

void ShellSort (int n) {
    for (int gap = n/2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int aux = v[i];
            int j;
            for (j = i; j >= gap && v[j - gap] > aux; j -= gap) {
                v[j] = v[j - gap];
            }
            v[j] = aux;
        }
    }
}

int QsortPartition (int s, int d)
{
    int m = s + (d - s) / 2;
    if (v[m] < v[s])
        swap (v[s], v[m]);
    if (v[d] < v[s])
        swap (v[s], v[d]);
    if (v[m] < v[d])
        swap (v[m], v[d]);

    int pivot = v[d];  
    int i = (s - 1); 
 
    for (int j = s; j <= d - 1; j++) 
    { 
        if (v[j] < pivot) 
        { 
            i++;
            swap(v[i], v[j]); 
        } 
    } 
    swap(v[i + 1], v[d]); 
    return (i + 1);
}

void QuickSort(int s, int d)
{
    if (s < d) 
    {
        int piv = QsortPartition (s, d); 
 
        QuickSort(s, piv - 1); 
        QuickSort(piv + 1, d); 
    } 
}

void SelectionSort(int n) 
{ 
    int ind; 
 
    for (int i = 0; i < n-1; i++) 
    {
        ind = i; 
        for (int j = i+1; j < n; j++) 
            if (v[j] < v[ind]) 
                ind = j;  
        swap(v[ind], v[i]); 
    } 
} 

int main() {

    int tests;
    fin >> tests;

    for (int i = 0; i < tests; i++) {
        int length, max_no;
        fin >> length >> max_no;

        GenerateTest(length, max_no);
        for (int i = 0; i < length; i++) {
            cp[i] = v[i];
        }

        fout << "Testul " << i << ": "
            << length << " de elemente mai mici de "
            << max_no << "\n\n";

        auto start = high_resolution_clock::now();
        sort(cp.begin(), cp.begin()+length);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        fout << "Nativ: " << duration.count() << " microsecunde\n";

        vector_copy(length);
        start = high_resolution_clock::now();
        RadixSort(length);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        fout << "Radix: " << duration.count() << " microsecunde\n";

        vector_copy(length);
        start = high_resolution_clock::now();
        MergeSort(0, length - 1);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        fout << "Merge: " << duration.count() << " microsecunde\n";

        vector_copy(length);
        start = high_resolution_clock::now();
        ShellSort(length);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        fout << "Shell: " << duration.count() << " microsecunde\n";

        vector_copy(length);
        start = high_resolution_clock::now();
        QuickSort(0, length - 1);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        fout << "Quick: " << duration.count() << " microsecunde\n";

        if (length <= 250000) {
        vector_copy(length);
        start = high_resolution_clock::now();
        SelectionSort(length);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        fout << "Selection: " << duration.count() << " microsecunde\n\n";
        } else fout << "Selection: X\n\n";

    }

    
    // int length, max_no;
    // fin >> length >> max_no;
    // GenerateTest(length, max_no);

    // auto start = high_resolution_clock::now();
    

    // // sort(v.begin(), v.begin() + length);
    // // RadixSort(length);
    // // MergeSort(0, length - 1);
    // // ShellSort(length);
    // // QuickSort(0, length - 1);
    // SelectionSort(length);

    // auto stop = high_resolution_clock::now();
    // auto duration = duration_cast<microseconds>(stop - start);

    // fout << "Time: " << duration.count() << " microseconds\n\n";

    // for (int i = 0; i < length; i++) {
        
    //     if (i % 10 == 0 && i > 0) 
    //         fout << '\n';
    //     fout << v[i] << " ";
    // }

    return 0;
}