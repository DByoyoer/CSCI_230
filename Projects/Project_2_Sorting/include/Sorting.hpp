#pragma once
#include <Entry.hpp>
#include <fstream>
#include <vector>

//TODO: Implement insertion sort
//TODO: Implement merge sort
//TODO: Track data moves for quick sort
//TODO: Utility output function

template <typename E, typename C>
class Sorting
{
public:
    void insertionSort(std::vector<E> &S, std::ofstream &outfile);
    void quickEndSort(std::vector<E> &S, std::ofstream &outfile);
    void quickSortMedOf3(std::vector<E> &S, std::ofstream &outfile);
    void mergeSort();

protected:
    void quickSortStep(std::vector<int> &S, int a, int b, int pivotType, int &compares);
    E medianOfThree(const std::vector<E> &S, int a, int b, int &compares);

private:
    C less;
};

template <typename E, typename C>
void Sorting<E, C>::quickSortStep(std::vector<int> &S, int a, int b, int pivotType, int &compares)
{
    if (a >= b)
        return; // 0 or 1 left? done
    E pivot;
    if (pivotType == 1) //last element as pivot
    {
        pivot = S[b];
    }
    else if (pivotType == 2) //median of 3 pivot
    {
        pivot = medianOfThree(S, a, b, compares);
    }
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
        }
    }
    std::swap(S[l], S[b]);                           // store pivot at l
    quickSortStep(S, a, l - 1, pivotType, compares); // recur on both sides
    quickSortStep(S, l + 1, b, pivotType, compares);
}

template <typename E, typename C>
E Sorting<E, C>::medianOfThree(const std::vector<E> &S, int a, int b, int &compares)
{
    E left, right, mid;
    left = S[a];
    right = S[b];
    mid = S[(b + a) / 2];
    if (less(left, right))
    {
        if (less(right, mid))
        {
            compares += 2;
            return right;
        }
        else if (less(mid, left))
        {
            compares += 3;
            return left;
        }
        else
        {
            compares += 3;
            return mid;
        }
    }
    else
    {
        if (less(left, mid))
        {
            compares += 2;
            return left;
        }
        else if (less(mid, right))
        {
            compares += 3;
            return right;
        }
        else
        {
            compares += 3;
            return mid;
        }
    }
}

template <typename E, typename C>
void Sorting<E, C>::quickEndSort(std::vector<E> &S, std::ofstream &outfile)
{
    int compares = 0;
    int dataMoves = 0;
    int pivotType = 1; //1 means use end as pivot
    if (S.size() <= 1)
    {
        return;
    }

    quickSortStep(S, 0, S.size() - 1, pivotType, compares);
    //TODO:Move this to a utility function
    outfile << "Number of compares: " << compares
            << "\nNumber of data moves:" << dataMoves
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
    outfile << "\n";
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

    quickSortStep(S, 0, S.size() - 1, pivotType, compares);
    //TODO:Move this to a utility function
    outfile << "Number of compares: " << compares
            << "\nNumber of data moves:" << dataMoves
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
    outfile << "\n";
}