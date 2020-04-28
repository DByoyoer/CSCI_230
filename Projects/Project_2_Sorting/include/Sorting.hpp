#pragma once
#include <Entry.hpp>
#include <fstream>
#include <vector>
#include <chrono>

//TODO: Implement insertion sort
//TODO: Implement merge sort
//TODO: Track data moves for quick sort
//TODO: Utility output function

template <typename E, typename C>
class Sorting
{
public:
    void insertionSort(std::vector<E> &S, std::ofstream &outfile);
    void quickSortEnd(std::vector<E> &S, std::ofstream &outfile);
    void quickSortMedOf3(std::vector<E> &S, std::ofstream &outfile);
    void mergeSort(std::vector<E> &S, std::ofstream &outfile);

    //Extra Credit

    void shellSort(std::vector<E> &S, std::ofstream &outfile);
    void radixSort(std::vector<E> &S, std::ofstream &outfile);

protected:
    void
    quickSortStep(std::vector<E> &S, int a, int b, int pivotType,
                  int &compares, int &dataMoves);

    //puts the median of 3 at the end point, b, so we can use the same quicksort algorithm
    void medianOfThree(std::vector<E> &S, int a, int b, int &compares, int &dataMoves);

    //Helper function to output necessary info to separate txt doc
    void outputData(std::ofstream &outfile, const char *sortingType,
                    const std::vector<E> &S, int compares,
                    int dataMoves, float runtime);

    void mergeSortHelper(std::vector<E> &S, int &compares, int &dataMoves);

    void merge(std::vector<E> &S1, std::vector<E> &S2, std::vector<E> &S,
               int &compares, int &dataMoves);
    int getDigits(int n);
    int getMaxDigits(std::vector<E> &S);

private:
    C less;
};

template <typename E, typename C>
void Sorting<E, C>::insertionSort(std::vector<E> &S, std::ofstream &outfile)
{
    auto start = std::chrono::high_resolution_clock::now();
    E key;
    int j;
    int comparisons = 0;
    int dataMoves = 0;
    for (int i = 1; i < S.size(); i++)
    {
        key = S[i];
        dataMoves++;
        j = i - 1;
        while (j >= 0)
        {
            if (less(key, S[j]))
            {
                dataMoves++;
                comparisons++;
                S[j + 1] = S[j]; //swaps
                j--;
            }
            else
            {
                comparisons++;
                break;
            }
        }
        S[j + 1] = key;
        dataMoves++;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    outputData(outfile, "Insertion Sort", S, comparisons, dataMoves, duration.count());
}

template <typename E, typename C>
void Sorting<E, C>::quickSortStep(std::vector<E> &S, int a, int b, int pivotType, int &compares, int &dataMoves)
{
    if (a >= b)
        return; // 0 or 1 left? done
    //If pivot type is 1 don't do anything if 2 move median to end
    if (pivotType == 2)
    {
        medianOfThree(S, a, b, compares, dataMoves);
    }

    E pivot = S[b];

    int l = a;     // left edge
    int r = b - 1; // right edge
    while (l <= r)
    {
        while (l <= r && !less(pivot, S[l]))
        {
            l++; // scan right till larger
            compares++;
        }
        while (r >= l && !less(S[r], pivot))
        {
            r--; // scan left till smaller
            compares++;
        }
        if (l < r) // both elements found
        {
            std::swap(S[l], S[r]);
            dataMoves += 3;
        }
    }
    std::swap(S[l], S[b]); // store pivot at l
    dataMoves += 3;
    quickSortStep(S, a, l - 1, pivotType, compares, dataMoves); // recur on both sides
    quickSortStep(S, l + 1, b, pivotType, compares, dataMoves);
}

template <typename E, typename C>
void Sorting<E, C>::medianOfThree(std::vector<E> &S, int a, int b, int &compares, int &dataMoves)
{
    int mid = (b + a) / 2;
    //Find and put median value at the end index
    if (less(S[mid], S[a]))
    {
        std::swap(S[a], S[mid]);
        dataMoves += 3;
    }
    if (less(S[b], S[a]))
    {
        std::swap(S[a], S[b]);
        dataMoves += 3;
    }
    if (less(S[mid], S[b]))
    {
        std::swap(S[mid], S[b]);
        dataMoves += 3;
    }
    compares += 3;
}

template <typename E, typename C>
void Sorting<E, C>::quickSortEnd(std::vector<E> &S, std::ofstream &outfile)
{
    int compares = 0;
    int dataMoves = 0;
    int pivotType = 1; //1 means use end as pivot
    if (S.size() <= 1)
    {
        return;
    }

    auto start = std::chrono::high_resolution_clock::now();
    quickSortStep(S, 0, S.size() - 1, pivotType, compares, dataMoves);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    outputData(outfile, "Quick Sort(End Pivot)", S, compares, dataMoves, duration.count());
}

template <typename E, typename C>
void Sorting<E, C>::quickSortMedOf3(std::vector<E> &S, std::ofstream &outfile)
{
    int compares = 0;
    int dataMoves = 0;
    int pivotType = 2; //2 means use median of 3 as pivot
    if (S.size() <= 1)
    {
        return;
    }
    auto start = std::chrono::high_resolution_clock::now();
    quickSortStep(S, 0, S.size() - 1, pivotType, compares, dataMoves);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    outputData(outfile, "Quick Sort(Median of 3)", S, compares, dataMoves, duration.count());
}

template <typename E, typename C>
void Sorting<E, C>::outputData(std::ofstream &outfile, const char *sortingType,
                               const std::vector<E> &S, int compares,
                               int dataMoves, float runtime)
{
    outfile << "============== " << sortingType << " ==============\n\n";
    outfile << "Size:" << S.size()
            << "\nNumber of compares: " << compares
            << "\nNumber of data moves:" << dataMoves
            << "\nRuntime: " << runtime << " microseconds"
            << "\nFirst 5 elements: \n";
    for (int i = 0; i < 5; i++)
    {
        outfile << S[i] << ' ';
    }
    outfile << "\n\nLast 5 elements: \n";
    for (int i = S.size() - 6; i < S.size(); i++)
    {
        outfile << S[i] << ' ';
    }
    outfile << "\n\n\n";
}

template <typename E, typename C>
void Sorting<E, C>::mergeSort(std::vector<E> &S, std::ofstream &outfile)
{

    int compares = 0;
    int dataMoves = 0;
    auto start = std::chrono::high_resolution_clock::now();
    mergeSortHelper(S, compares, dataMoves);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    outputData(outfile, "Merge Sort", S, compares, dataMoves, duration.count());
}

template <typename E, typename C>
void Sorting<E, C>::mergeSortHelper(std::vector<E> &S, int &compares, int &dataMoves)
{
    typedef typename std::vector<E>::iterator Iterator;
    int n = S.size();
    if (n <= 1)
    {
        return;
    }
    std::vector<E> S1, S2;
    Iterator p = S.begin();
    for (int i = 0; i < n / 2; i++)
    {
        S1.push_back(*p++);
        dataMoves++;
    }
    for (int i = n / 2; i < n; i++)
    {
        S2.push_back(*p++);
        dataMoves++;
    }
    S.clear();
    mergeSortHelper(S1, compares, dataMoves);
    mergeSortHelper(S2, compares, dataMoves);
    merge(S1, S2, S, compares, dataMoves);
}

template <typename E, typename C>
void Sorting<E, C>::merge(std::vector<E> &S1, std::vector<E> &S2, std::vector<E> &S, int &compares, int &dataMoves)
{
    typedef typename std::vector<E>::iterator Iterator;
    Iterator p1 = S1.begin();
    Iterator p2 = S2.begin();

    while (p1 != S1.end() && p2 != S2.end())
    {
        if (less(*p1, *p2))
        {
            S.push_back(*p1++);
            dataMoves++;
        }
        else
        {
            S.push_back(*p2++);
            dataMoves++;
        }
        compares++;
    }

    while (p1 != S1.end())
    {
        S.push_back(*p1++);
        dataMoves++;
    }
    while (p2 != S2.end())
    {
        S.push_back(*p2++);
        dataMoves++;
    }
}

template <typename E, typename C>
void Sorting<E, C>::shellSort(std::vector<E> &S, std::ofstream &outfile)
{
    int interval = 0;
    int compares = 0;
    int dataMoves = 0;
    E key;
    int j;
    auto start = std::chrono::high_resolution_clock::now();
    while (interval < S.size() / 3)
    {
        interval = interval * 3 + 1;
    }
    (interval - 1) / 3;
    while (interval > 0)
    {
        for (int i = interval; i < S.size(); i++)
        {
            key = S[i];
            dataMoves++;
            j = i;
            while (j >= interval && less(key, S[j - interval]))
            {
                S[j] = S[j - interval];
                dataMoves++;
                compares++;
                j -= interval;
            }
            S[j] = key;
            dataMoves++;
        }
        interval = (interval - 1) / 3;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    outputData(outfile, "Shell Sort", S, compares, dataMoves, duration.count());
}

template <typename E, typename C>
void Sorting<E, C>::radixSort(std::vector<E> &S, std::ofstream &outfile)
{
    std::vector<std::vector<E>> buckets(10);
    int bucketIndex, arrayIndex;
    int maxDigits = getMaxDigits(S);
    int pow10 = 1;
    auto start = std::chrono::high_resolution_clock::now();
    for (int digitIndex = 0; digitIndex < maxDigits; digitIndex++)
    {
        for (int i = 0; i < S.size(); i++)
        {
            bucketIndex = (S[i].key() / pow10) % 10;
            buckets[bucketIndex].push_back(S[i]);
        }
        arrayIndex = 0;
        for (int i = 0; i < 10; i++)
        {
            for (int j = 0; j < buckets[i].size(); j++)
            {
                S[arrayIndex++] = buckets[i][j];
            }
            buckets[i].clear();
        }
        pow10 *= 10;
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    outputData(outfile, "Radix Sort", S, -1, -1, duration.count());
}
template <typename E, typename C>
int Sorting<E, C>::getMaxDigits(std::vector<E> &S)
{
    int maxDigits = 0;
    int digitCount;
    for (int i = 0; i < S.size(); i++)
    {
        digitCount = getDigits(S[i].key());
        maxDigits = std::max(digitCount, maxDigits);
    }
    return maxDigits;
}

template <typename E, typename C>
int Sorting<E, C>::getDigits(int n)
{
    if (n == 0)
    {
        return 1;
    }
    int digits = 0;
    while (n != 0)
    {
        digits++;
        n /= 10;
    }
    return digits;
}