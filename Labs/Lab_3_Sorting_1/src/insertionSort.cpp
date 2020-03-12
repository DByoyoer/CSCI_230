#include <chrono>
#include <iostream>

//Returns pair corresponding to Comparisons and Swaps
std::pair<int, int> insertionSort(int arr[], int size);

void randomizeArr(int arr[], int size);

//Extra Credit, Create and measures runtime for insertion sort
//on an array of given size
void measureRuntime(int size);

int main()
{
    int sortedArr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int descendingArr[10] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int randArr[10];
    std::pair<int, int> data;
    randomizeArr(randArr, 10);

    std::cout << "Sorted Array: \n";
    data = insertionSort(sortedArr, 10);
    std::cout << "Array sorted with " << data.first << " comparisons and "
              << data.second << " swaps\n\n";

    std::cout << "Reverse Sorted Array: \n";
    data = insertionSort(descendingArr, 10);
    std::cout << "Array sorted with " << data.first << " comparisons and "
              << data.second << " swaps\n\n";

    std::cout << "Random Array: \n";
    data = insertionSort(randArr, 10);
    std::cout << "Array sorted with " << data.first << " comparisons and "
              << data.second << " swaps\n\n";

    //Extra Credit

    std::cout << "Collecting Insertion Sort runtimes:\n\n";

    measureRuntime(1000);
    measureRuntime(10000);
    measureRuntime(100000);
}

std::pair<int, int> insertionSort(int arr[], int size)
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
    std::pair<int, int> data(comparisons, swaps);
    return data;
}

void randomizeArr(int arr[], int size)
{
    std::srand(time(NULL));
    for (int i = 0; i < size; i++)
    {
        arr[i] = rand() % 100 + 1;
    }
}

void measureRuntime(int size)
{
    int* arr = new int[size];
    randomizeArr(arr, size);
    auto start = std::chrono::high_resolution_clock::now();
    insertionSort(arr, size);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    std::cout << "Array of size " << size << " sorted in " << duration.count()
              << " microseconds or " << duration.count() / (float)1000000 << " seconds\n";

    delete[] arr;
}