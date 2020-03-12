#include <chrono>
#include <iostream>
#include <list>

template <typename E>
class LessThan
{
public:
    bool operator()(const E& first, const E& second) const
    {
        return first < second;
    }
};

template <typename E, typename C>
void mergeSort(std::list<E>& S, const C& less);

template <typename E, typename C>
void merge(std::list<E>& S1, std::list<E>& S2, std::list<E>& S, const C& less);

std::list<int> randomizeList(int size);

void measureRuntime(int size);

template <typename E>
void printSeq(const E& seq);

int main()
{
    std::list<int> randList = randomizeList(10);
    LessThan<int> less;

    std::cout << "Unsorted List:\n";
    printSeq(randList);

    mergeSort(randList, less);
    std::cout << "\nSorted with Merge Sort:\n";
    printSeq(randList);

    //Extra credit

    std::cout << "\n\nCollecting Merge Sort Runtimes:\n\n";

    std::list<int> testList1 = randomizeList(1000);
    std::list<int> testList2 = randomizeList(10000);
    std::list<int> testList3 = randomizeList(100000);

    measureRuntime(1000);
    measureRuntime(10000);
    measureRuntime(100000);
}

template <typename E, typename C>
void mergeSort(std::list<E>& S, const C& less)
{
    typedef typename std::list<E>::iterator Iterator;
    int n = S.size();
    if (n <= 1)
    {
        return;
    }
    std::list<E> S1, S2;
    Iterator p = S.begin();
    for (int i = 0; i < n / 2; i++)
    {
        S1.push_back(*p++);
    }
    for (int i = n / 2; i < n; i++)
    {
        S2.push_back(*p++);
    }
    S.clear();
    mergeSort(S1, less);
    mergeSort(S2, less);
    merge(S1, S2, S, less);
}

template <typename E, typename C>
void merge(std::list<E>& S1, std::list<E>& S2, std::list<E>& S, const C& less)
{
    typedef typename std::list<E>::iterator Iterator;
    Iterator p1 = S1.begin();
    Iterator p2 = S2.begin();

    while (p1 != S1.end() && p2 != S2.end())
    {
        if (less(*p1, *p2))
        {
            S.push_back(*p1++);
        }
        else
        {
            S.push_back(*p2++);
        }
    }

    while (p1 != S1.end())
    {
        S.push_back(*p1++);
    }
    while (p2 != S2.end())
    {
        S.push_back(*p2++);
    }
}

template <typename E>
void printSeq(const E& seq)
{
    for (auto i : seq)
    {
        std::cout << i << '\n';
    }
}

std::list<int> randomizeList(int size)
{
    std::srand(time(NULL));
    std::list<int> randList;
    for (int i = 0; i < size; i++)
    {
        randList.push_back(std::rand() % 1000);
    }

    return randList;
}

void measureRuntime(int size)
{
    std::list<int> testList = randomizeList(size);
    LessThan<int> less;
    auto start = std::chrono::high_resolution_clock::now();
    mergeSort(testList, less);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout << "List of size " << size << " sorted in " << duration.count() << " microseconds or "
              << duration.count() / (float)1000000 << " seconds\n";
}