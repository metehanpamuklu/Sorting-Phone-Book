// created by Metehan Pamuklu

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <chrono>
#include<cctype>
#include <algorithm>

using namespace std::chrono;
using namespace std;

struct Contact {
    string name; 
    string surname;
    string telephone;
    string city;
    string fullName; //comparsion element for sorting
    // Comparison operator to compare Contacts by their full name
    bool operator<(const Contact& other) const {
        return fullName < other.fullName;
    }
};
//vector elements


struct Timing {
    string sort_name;
    float time_of_sort;
};
//making struct for output


// Function to read PhoneBook data from file
vector<Contact> readPhoneBook(const string& filename) {
    vector<Contact> phoneBook;
    ifstream file(filename);
    if (file.is_open()) {
        Contact contact;
        while (file >> contact.name >> contact.surname >> contact.telephone >> contact.city) {
            contact.fullName = contact.name + " " + contact.surname;
            phoneBook.push_back(contact);
        }
        file.close();
    }
    else {
        cerr << "Error: Unable to open file " << filename << endl;
    }
    return phoneBook;
}


//sorting algortihms

// Insertion Sort
template <class Comparable>
void insertionSort(vector<Comparable>& a) {
    int j;
    for (int p = 1; p < a.size(); ++p) {
        Comparable tmp = a[p];
        for (j = p; j > 0 && tmp < a[j - 1]; --j)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
}
//end


// Function to perform percDown operation in heapify process
template <class Comparable>
void percDown(vector<Comparable>&a, int i, int n) {
    int child;
    Comparable tmp = move(a[i]);

    for (; 2 * i + 1 < n; i = child) {
        child = 2 * i + 1;
        if (child != n - 1 && a[child] < a[child + 1])
            ++child;
        if (tmp < a[child])
            a[i] = move(a[child]);
        else
            break;
    }
    a[i] = move(tmp);
}
// heap sort
template <class Comparable>
void heapSort(vector<Comparable>& a) {
    // Build heap
    for (int i = a.size() / 2 - 1; i >= 0; --i)
        percDown(a, i, a.size());

    // Sort
    for (int j = a.size() - 1; j > 0; --j) {
        swap(a[0], a[j]);      // Swap max to the last position
        percDown(a, 0, j);     // Re-form the heap
    }
}
//end


/**
 * Mergesort algorithm (driver).
 */
template <class Comparable>
void mergeSort(vector<Comparable>& a) {
    vector<Comparable> tmpArray(a.size());

    mergeSort(a, tmpArray, 0, a.size() - 1);
}

/**
 * Internal method that makes recursive calls.
 * a is a vector of Comparable items.
 * tmpArray is a vector to place the merged result.
 * left is the left-most index of the subarray.
 * right is the right-most index of the subarray.
 */
template <class Comparable>
void mergeSort(vector<Comparable>& a, vector<Comparable>& tmpArray, int left, int right) {
    if (left < right) {
        int center = (left + right) / 2;
        mergeSort(a, tmpArray, left, center);
        mergeSort(a, tmpArray, center + 1, right);
        merge(a, tmpArray, left, center + 1, right);
    }
}

/**
 * Internal method that merges two sorted halves of a subarray.
 * a is a vector of Comparable items.
 * tmpArray is a vector to place the merged result.
 * leftPos is the left-most index of the subarray.
 * rightPos is the index of the start of the second half.
 * rightEnd is the right-most index of the subarray.
 */
template <class Comparable>
void merge(vector<Comparable>& a, vector<Comparable>& tmpArray, int leftPos, int rightPos, int rightEnd) {
    int leftEnd = rightPos - 1;
    int tmpPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    // Main loop
    while (leftPos <= leftEnd && rightPos <= rightEnd) {
        if (a[leftPos].fullName <= a[rightPos].fullName)
            tmpArray[tmpPos++] = move(a[leftPos++]);
        else
            tmpArray[tmpPos++] = move(a[rightPos++]);
    }

    // Copy rest of first half
    while (leftPos <= leftEnd)
        tmpArray[tmpPos++] = move(a[leftPos++]);

    // Copy rest of right half
    while (rightPos <= rightEnd)
        tmpArray[tmpPos++] = move(a[rightPos++]);

    // Copy tmpArray back
    for (int i = 0; i < numElements; ++i, --rightEnd)
        a[rightEnd] = move(tmpArray[rightEnd]);
}
//end



//quicksort
template <class Comparable>
inline void myswap(Comparable& obj1,
    Comparable& obj2)
{
    Comparable tmp = obj1;
    obj1 = obj2;
    obj2 = tmp;
}

template <class Comparable>
const Comparable& median3(vector<Comparable>& a,
    int left, int right)
{
    int center = (left + right) / 2;
    if (a[center] < a[left])
        myswap(a[left], a[center]);
    if (a[right] < a[left])
        myswap(a[left], a[right]);
    if (a[right] < a[center])
        myswap(a[center], a[right]);

    // Place pivot at position right - 1
    myswap(a[center], a[right - 1]);
    return a[right - 1];
}
// insertion sort that is going to be used in quick sort when the array is small
template <class Comparable>
void insertionSortQuick(vector<Comparable>& a, int left, int right)
{
    for (int p = left + 1; p <= right; p++)
    {
        Comparable tmp = a[p];
        int j;

        // we move the current element to the right by one as long as the current element is smaller than the previous element
        for (j = p; j > left && tmp < a[j - 1]; j--)
            a[j] = a[j - 1];
        a[j] = tmp;
    }
};

template <class Comparable>
void quicksortMedian(vector<Comparable>& a,
    int left, int right)
{
    if (left + 10 <= right)
    {
        Comparable pivot = median3(a, left, right);
        int i = left, j = right - 1;
        for (; ; )
        {
            while (a[++i] < pivot) {}

            while (pivot < a[--j]) {}

            if (i < j)
                myswap(a[i], a[j]);
            else
                break;
        }
        myswap(a[i], a[right - 1]);   // Restore pivot

        quicksortMedian(a, left, i - 1);       // Sort small elements
        quicksortMedian(a, i + 1, right);    // Sort large elements
    }
    else  // Do an insertion sort on the subarray
        insertionSortQuick(a, left, right);
}

inline int leftChild(int i)
{
    return 2 * i + 1;
}


template <class Comparable>
void quicksortMedian(vector<Comparable>& a)
{
    quicksortMedian(a, 0, a.size() - 1);
}


//search algortihms


//binary search
template <class Comparable>
vector<Contact> binarySearch(const vector<Comparable>& a, const string& query) {
    vector<Contact> matches;
    int left = 0;
    int right = a.size() - 1;
    bool isFullName = query.find(' ') != string::npos;//if there is a space check full name given

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (isFullName) {
            if (a[mid].fullName == query) {
                // Exact full name match found
                matches.push_back(a[mid]);
                return matches;
            }
            else if (a[mid].fullName < query) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        else {
            if (a[mid].name.substr(0, query.length()) == query) {
                // Partial name match found
                matches.push_back(a[mid]);
            }
            // Check which direction to search next
            if (a[mid].fullName < query) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
    }
    return matches; // Return empty vector if no matches found
}



// Sequential search function
template <class Comparable>
vector<Comparable> sequentialSearch(const vector<Comparable>& a, const string& query) {
    vector<Comparable> searchResults;
    bool isFullName = query.find(' ') != string::npos;

    for (const auto& contact : a) {
        if (isFullName) {
            if (contact.fullName == query) {
                searchResults.push_back(contact);
                break; // Break out of the loop after finding the first match
            }
        }
        else {
            if (contact.name.substr(0, query.length()) == query) {
                searchResults.push_back(contact);
            }
        }
    }
    return searchResults;
}

//Search for printing
template <class Comparable>
vector<Comparable> Search_Outputs(const vector<Comparable>& a, const string& query) {
    vector<Comparable> searchResults;
    bool isFullName = query.find(' ') != string::npos;

    for (const auto& contact : a) {
        if (isFullName) {
            if (contact.fullName == query) {
                searchResults.push_back(contact);
            }
        }
        else {
            if (contact.name.substr(0, query.length()) == query) {
                searchResults.push_back(contact);
            }
        }
    }
    return searchResults;
}





int main() {
    string filename;
    cout << "Enter the filename of the PhoneBook: ";
    cin >> filename;

    string query;
    cout << "Enter the search query: ";
    cin.ignore(); 
    getline(cin, query);
    

    vector<Contact> phoneBook = readPhoneBook(filename);
    
    // Create copies of the phoneBook vector for each sorting algorithm
    
    vector<Contact> phoneBookQuickSort = phoneBook;
    vector<Contact> phoneBookInsertionSort = phoneBook;
    vector<Contact> phoneBookMergeSort = phoneBook;
    vector<Contact> phoneBookHeapSort = phoneBook;

    // Measure insertion sort time
        auto start = high_resolution_clock::now();
    insertionSort(phoneBookInsertionSort);
    auto insertionSortTime = duration_cast<nanoseconds>(high_resolution_clock::now() - start);

    // Measure heap sort time
    start = high_resolution_clock::now();
    heapSort(phoneBookHeapSort);
    auto heapSortTime = duration_cast<nanoseconds>(high_resolution_clock::now() - start);

    // Measure merge sort time
    start = high_resolution_clock::now();
    mergeSort(phoneBookMergeSort);
    auto mergeSortTime = duration_cast<nanoseconds>(high_resolution_clock::now() - start);

    // Measure quick sort (median) time
    start = high_resolution_clock::now();
    quicksortMedian(phoneBookQuickSort);
    auto quickSortTime = duration_cast<nanoseconds>(high_resolution_clock::now() - start);

    cout << endl;
    cout << "Sorting the vector copies" << endl;
    cout << "======================================" << endl;
    // Print the execution times with the desired format
    cout << "Quick Sort Time: " << quickSortTime.count() << " Nanoseconds" << endl;
    cout << "Insertion Sort Time: " << insertionSortTime.count() << " Nanoseconds" << endl;
    cout << "Merge Sort Time: " << mergeSortTime.count() << " Nanoseconds" << endl;
    cout << "Heap Sort Time: " << heapSortTime.count() << " Nanoseconds" << endl;
    cout << endl;
    cout<<"Searching for "<<query<<endl;
    cout << "======================================" << endl;

    Timing quickSortTiming{ "Quick Sort", quickSortTime.count() };
    Timing insertionSortTiming{ "Insertion Sort", insertionSortTime.count() };
    Timing mergeSortTiming{ "Merge Sort", mergeSortTime.count() };
    Timing heapSortTiming{ "Heap Sort", heapSortTime.count() };
    vector<Timing> sort_timings = { quickSortTiming, insertionSortTiming, mergeSortTiming, heapSortTiming };
    
    int N = 100; // Number of iterations
    string fullNameUpper_query = query;
    // Convert full name to uppercase
    for (char& c : fullNameUpper_query) {
        c = toupper(c);
    }

    // Binary search
    auto binaryStart = high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        binarySearch(phoneBook, query);
    }
    auto binaryEnd = high_resolution_clock::now();
    auto binaryTotalTime = duration_cast<nanoseconds>(binaryEnd - binaryStart).count() / static_cast<double>(N);
    vector<Contact> Results = Search_Outputs(phoneBookQuickSort, query);
    if (Results.empty()) {
        cout << fullNameUpper_query << " does NOT exist in the dataset" << endl;
    }
    for (const auto& contact : Results) {
        string fullNameUpper = contact.fullName;
        // Convert full name to uppercase
        for (char& c : fullNameUpper) {
            c = toupper(c);
        }
        cout << fullNameUpper << " " << contact.telephone << " " << contact.city << endl;
    }
    cout << "Binary Search Time: " << binaryTotalTime << " Nanoseconds" << endl;
    
    
    
    cout << endl;
    cout << "Search results for Sequential Search:" << endl;
    // Sequential search
    auto sequentialStart = high_resolution_clock::now();
    for (int i = 0; i < N; ++i) {
        sequentialSearch(phoneBook, query);
    }
    auto sequentialEnd = high_resolution_clock::now();
    auto sequentialTotalTime = duration_cast<nanoseconds>(sequentialEnd - sequentialStart).count() / static_cast<double>(N);
    if (Results.empty()) {
        cout << fullNameUpper_query << " does NOT exist in the dataset" << endl<<endl;
    }

    for (const auto& contact : Results) {
        string fullNameUpper = contact.fullName;
        // Convert full name to uppercase
        for (char& c : fullNameUpper) {
            c = toupper(c);
        }
        cout << fullNameUpper << " " << contact.telephone << " " << contact.city << endl;
    }
    cout << "Sequential Search Time: " << sequentialTotalTime << " Nanoseconds" << endl;
    cout << endl;
    
    
    
    cout << "SpeedUp between Search Algorithms" << endl;
    cout << "======================================" << endl;
    if (sequentialTotalTime < binaryTotalTime) {
        cout << "Binary Search/Sequantial Search Speedup = " << binaryTotalTime /sequentialTotalTime;
    }
    else {
        cout << "(Sequential Search/ Binary Search) SpeedUp = " << sequentialTotalTime / binaryTotalTime;
    }
    cout << endl;
    cout << endl;
    cout << "SpeedUps between Sorting Algorithms" << endl;
    cout << "======================================" << endl;
    // Find the minimum time
    //After that taking necesarry info from min time
    auto min_time_it = min_element(sort_timings.begin(), sort_timings.end(),
        [](const Timing& lhs, const Timing& rhs) {
            return lhs.time_of_sort < rhs.time_of_sort;
        });
    float min_time = min_time_it->time_of_sort;
    string fastest_sort = min_time_it->sort_name;
    for (const auto& timing : sort_timings) {
        if (timing.time_of_sort != min_time) {
            cout << "(" << timing.sort_name << "/"<<fastest_sort <<") SpeedUp = " << timing.time_of_sort / min_time << endl;
        }
    }
    return 0;
}


