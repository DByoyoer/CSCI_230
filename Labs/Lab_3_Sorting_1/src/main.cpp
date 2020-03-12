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

void insertionSort(int arr[], int size);

template <typename E>
void printSeq(const E& seq)
{
    for (auto i : seq)
    {
        std::cout << i << '\n';
    }
}

void randomizeArr(int arr[], int size);

template <typename E, typename C>
void mergeSort(std::list<E>& S, const C& less);

template <typename E, typename C>
void merge(std::list<E>& S1, std::list<E>& S2, std::list<E>& S, const C& less);

int main()
{
    int sortedArr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int descendingArr[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int randArr[10];
    randomizeArr(randArr, 10);

    std::cout << "Sorted Array: \n";
    insertionSort(sortedArr, 10);
    std::cout << "\nReverse Sorted Array: \n";
    insertionSort(descendingArr, 10);
    std::cout << "\nRandom Array: \n";
    insertionSort(randArr, 10);
    std::cout << '\n';

    //Merge Sort Stuff

    std::list<int> randList = randomizeList(10);
    LessThan<int> less;

    printSeq(randList);
    mergeSort(randList, less);
    std::cout << '\n';
    printSeq(randList);
}

void insertionSort(int arr[], int size)
{
    int key;
    int j;
    int comparisons = 0;
    int swaps = 0;
    for (int i = 1; i < size; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0)
        {
            if (arr[j] > key)
            {
                swaps++;
                comparisons++;
                arr[j + 1] = arr[j]; //swaps
                j--;
            }
            else
            {
                comparisons++;
                break;
            }
        }
        arr[j + 1] = key;
    }
    std::cout << "Array sorted with " << comparisons << " comparisons and " << swaps << " swaps.\n";
}

void randomizeArr(int arr[], int size)
{
    std::srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100 + 1;
    }
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