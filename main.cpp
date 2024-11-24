#include <iostream>
#include <vector>
#include <chrono>
#include <random>

class SortingComparison
{
public:
    // Insertion Sort
    void insertionSort(std::vector<int> &arr)
    {
        for (size_t i = 1; i < arr.size(); ++i)
        {
            int key = arr[i];
            int j = i - 1;
            // will move elements greater than key to one position ahead
            while (j >= 0 && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                --j;
            }
            arr[j + 1] = key;
        }
    }

    // Quick Sort
    void quickSort(std::vector<int> &arr, int left, int right)
    {
        if (left < right)
        {
            int pi = partition(arr, left, right);
            quickSort(arr, left, pi - 1);
            quickSort(arr, pi + 1, right);
        }
    }

    // Merge Sort
    void mergeSort(std::vector<int> &arr, int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    // Generate random integers
    std::vector<int> generateRandomArray(int size)
    {
        std::vector<int> arr(size);
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dist(1, 100000);
        for (int &x : arr)
        {
            x = dist(gen);
        }
        return arr;
    }

    // Test if sorted
    bool isSorted(const std::vector<int> &arr)
    {
        for (size_t i = 1; i < arr.size(); ++i)
        {
            if (arr[i] < arr[i - 1])
            {
                return false;
            }
        }
        return true;
    }

    // Compare sorting algorithms
    void compareSortingAlgorithms()
    {
        std::vector<int> sizes = {1000, 10000, 100000}; // Dataset sizes
        for (int size : sizes)
        {
            std::vector<int> arr = generateRandomArray(size);

            std::cout << "Data size: " << size << "\n";

            // Test Insertion Sort
            std::vector<int> arr_copy = arr;
            auto start = std::chrono::high_resolution_clock::now();
            insertionSort(arr_copy);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> elapsed = end - start;
            std::cout << "Insertion Sort: " << elapsed.count() << " seconds\n";
            std::cout << "Sorted: " << (isSorted(arr_copy) ? "Yes" : "No") << "\n";

            // Test Quick Sort
            arr_copy = arr;
            start = std::chrono::high_resolution_clock::now();
            quickSort(arr_copy, 0, arr_copy.size() - 1);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            std::cout << "Quick Sort: " << elapsed.count() << " seconds\n";
            std::cout << "Sorted: " << (isSorted(arr_copy) ? "Yes" : "No") << "\n";

            // Test Merge Sort
            arr_copy = arr;
            start = std::chrono::high_resolution_clock::now();
            mergeSort(arr_copy, 0, arr_copy.size() - 1);
            end = std::chrono::high_resolution_clock::now();
            elapsed = end - start;
            std::cout << "Merge Sort: " << elapsed.count() << " seconds\n";
            std::cout << "Sorted: " << (isSorted(arr_copy) ? "Yes" : "No") << "\n\n";
        }
    }

private:
    // Helper for Quick Sort: Partition
    int partition(std::vector<int> &arr, int left, int right)
    {
        int pivot = arr[right]; // Choose the rightmost element as pivot
        int i = left - 1;
        for (int j = left; j < right; ++j)
        {
            if (arr[j] <= pivot)
            {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[right]);
        return i + 1;
    }

    // Helper for Merge Sort: Merge
    void merge(std::vector<int> &arr, int left, int mid, int right)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<int> L(n1), R(n2);

        for (int i = 0; i < n1; ++i)
            L[i] = arr[left + i];
        for (int i = 0; i < n2; ++i)
            R[i] = arr[mid + 1 + i];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
            {
                arr[k] = L[i];
                ++i;
            }
            else
            {
                arr[k] = R[j];
                ++j;
            }
            ++k;
        }

        while (i < n1)
            arr[k++] = L[i++];
        while (j < n2)
            arr[k++] = R[j++];
    }
};

int main()
{
    SortingComparison sorter;
    sorter.compareSortingAlgorithms();
    return 0;
}
