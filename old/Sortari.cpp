#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;
using namespace std::chrono;

ifstream fin("Sortari_teste.txt");
ofstream fout("Test_iesire.txt");

int arr_length, maximum;

void GenereazaTest(int v[], int lungime, int nr_max)
{
    srand(time(NULL));
    for (int i = 0; i < lungime; i ++)
    {
        if (nr_max <= RAND_MAX){
            v[i] = rand() % nr_max + 1;
            if (v[i] > maximum)
                maximum = v[i];
        }
        else {
            int max_factor = nr_max / RAND_MAX;
            int a = rand() % RAND_MAX + 1;
            int aux = rand() % max_factor + 1;
            a *= aux;
            v[i] = a;
            if (v[i] > maximum)
                maximum = v[i];
        }
    }
}

void CopiereVector (int v[], int c[], int n)
{
    for (int i = 0; i < n; i ++)
    {
        c[i] = v[i];
    }
}

bool Test_Sort (int v[], int n)
{
    for (int i = 0; i < n-1; i ++)
        if (v[i] > v[i+1])
            return false;
    return true;
}

void AfisareVector (int v[], int n)
{
    for (int i = 0; i < n; i ++)
        cout << v[i] << " ";
    cout << '\n';
}

void CitireFisier (int v[])
{
    int i = 0;
    while (!fin.eof())
    {
        fin >> v[i];
        i ++;
    }
    arr_length = i;
}

void ScriereFisier (int v[], int n)
{
    int rows = n / 10, last_row = n % 10, i = 0;
    for (int j = 1; j <= rows; j++)
    {
        for (int k = 1; k <= 10; k ++)
        {
            fout << v[i];
            i++;
            if (j != rows || k != 10) fout << " ";
        }
        if (j != rows)
            fout << '\n';
    }
    if (last_row != 0)
    {
        for (int j = 1; j <= last_row; j++)
        {
            fout << v[i];
            i++;
            if (j != last_row) fout << " ";
        }
    }
}

void BubbleSort (int v[], int n)
{
    for (int i = 0; i < n-1; i++)
        for (int j = 0; j < n-i-1; j++)
            if (v[j] > v[j+1]) swap(v[j], v[j+1]);
}

void CountSort (int v[], int n, int maxim)
{
    int frecventa[maxim+1] = {0};
    for (int i = 0; i < n; i++)
        frecventa[v[i]] ++;
    
    int ind = 0;
    for (int i = 0; i < maxim + 1; i ++)
    {
        for (int j = 0; j < frecventa[i]; j ++)
        {
            v[ind] = i;
            ind ++;
        }
    }
}

void CountRadixSort (int v[], int n, int exp)
{
    int iesire[n+1], frecventa[10] = {0};

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

void RadixSort (int v[], int n)
{
    int maxi = 0;
    for (int i = 0; i < n; i ++)
        if (v[i] > maxi)
            maxi = v[i];

    for (int p = 1; maxi / p > 0; p *= 10) 
        CountRadixSort(v, n, p);
}

void Merge (int v[], int s, int m, int d)
{
    int copie[d-s+1];
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

void MergeSort (int v[], int s, int d)
{
    if (s >= d) return;

    int m = s + (d - s) / 2;
    MergeSort(v, s, m);
    MergeSort(v, m+1, d);
    Merge(v, s, m, d);
}

int QsortPartition (int v[], int s, int d)
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

void QuickSort(int v[], int s, int d)
{
    if (s < d) 
    {
        int piv = QsortPartition (v, s, d); 
 
        QuickSort(v, s, piv - 1); 
        QuickSort(v, piv + 1, d); 
    } 
}

int main()
{
    int nr_teste;
    fin >> nr_teste;

    for (int i = 0; i < nr_teste; i ++)
    {
        int lungime, nr_max;
        fin >> lungime >> nr_max;
        int v[lungime + 10];
        GenereazaTest(v, lungime, nr_max);

        int cop[lungime + 10];
        CopiereVector(v, cop, lungime);

        fout << "Testul " << i << ": "
            << lungime << " de elemente mai mici de "
            << nr_max << '\n';

        auto start = high_resolution_clock::now();
        sort (cop, cop + lungime);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        fout << "Algoritm nativ: " << duration.count() << " microsecunde\n";
        CopiereVector(v, cop, lungime);

        start = high_resolution_clock::now();
        BubbleSort(cop, lungime);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        fout << "BubbleSort: " << duration.count() << " microsecunde\n";
        CopiereVector(v, cop, lungime);

        start = high_resolution_clock::now();
        CountSort(cop, lungime, maximum);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        fout << "CountSort: " << duration.count() << " microsecunde\n";
        CopiereVector(v, cop, lungime);

        start = high_resolution_clock::now();
        RadixSort(cop, lungime);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        fout << "RadixSort: " << duration.count() << " microsecunde\n";
        CopiereVector(v, cop, lungime);

        start = high_resolution_clock::now();
        MergeSort(cop, 0, lungime - 1);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        fout << "MergeSort: " << duration.count() << " microsecunde\n";
        CopiereVector(v, cop, lungime); 

        start = high_resolution_clock::now();
        QuickSort (cop, 0, lungime-1);
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start);

        fout << "QuickSort: "<< duration.count() << " microsecunde\n\n";

        // fout << "Sirul sortat:\n";
        // ScriereFisier(v, lungime);
        // fout << "\n\n";
    }
    return 0;
}
