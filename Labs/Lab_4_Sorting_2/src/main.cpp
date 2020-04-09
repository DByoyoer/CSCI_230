#include <iostream>
#include <vector>
#include <list>
#include "Comparators.hpp"

template <typename E, typename C>
void quickSort(std::vector<E> &S, const C &less);

template <typename E, typename C>
void quickSortStep(std::vector<E> &S, int a, int b, const C &less);

void printVector(const std::vector<int> &S);

void bucketSort(std::vector<int> &S)
{
    std::vector<std::list<int>> bucketArray(1000);
    int k;
    while (!S.empty())
    {
        k = S.back();
        S.pop_back();
        bucketArray[k].insert(bucketArray[k].end(), k);
    }
    for (int i = 0; i < 1000; i++)
    {
        while (!bucketArray[i].empty())
        {
            S.push_back(bucketArray[i].front());
            bucketArray[i].pop_front();
        }
    }
}

std::vector<int> randomizeVector(int size)
{
    std::srand(time(NULL));
    std::vector<int> randVec;
    for (int i = 0; i < size; i++)
    {
        randVec.push_back(std::rand() % 1000);
    }

    return randVec;
}

int main()
{
    std::vector<int> quickSortTest = randomizeVector(20);
    std::vector<int> bucketSortTest = randomizeVector(100);
    std::cout << "Unsorted:\n";
    LowToHigh<int> less;
    printVector(quickSortTest);
    quickSort(quickSortTest, less);
    std::cout << "Sorted: \n";
    printVector(quickSortTest);
    std::cout << "\n\n\nBucketSort:\n";
    std::cout << "Unsorted:\n";
    printVector(bucketSortTest);
    bucketSort(bucketSortTest);
    std::cout << "Sorted:\n";
    printVector(bucketSortTest);
}

template <typename E, typename C>
void quickSort(std::vector<E> &S, const C &less)
{
    if (S.size() <= 1)
    {
        return;
    }
    quickSortStep(S, 0, S.size() - 1, less);
}
template <typename E, typename C>
void quickSortStep(std::vector<E> &S, int a, int b, const C &less)
{
    if (a >= b)
        return;     // 0 or 1 left? done
    E pivot = S[b]; // select last as pivot
    int l = a;      // left edge
    int r = b - 1;  // right edge
    while (l <= r)
    {
        while (l <= r && !less(pivot, S[l]))
            l++; // scan right till larger
        while (r >= l && !less(S[r], pivot))
            r--;   // scan left till smaller
        if (l < r) // both elements found
            std::swap(S[l], S[r]);
    }                                 // until indices cross
    std::swap(S[l], S[b]);            // store pivot at l
    quickSortStep(S, a, l - 1, less); // recur on both sides
    quickSortStep(S, l + 1, b, less);
}

void printVector(const std::vector<int> &S)
{
    for (int i : S)
    {
        std::cout << i << '\n';
    }
}
