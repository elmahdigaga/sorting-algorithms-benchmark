#include <chrono>
#include <fstream>
#include <map>

#include "sortingAlgorithms.hpp"

std::map<__int64, double> bubble;
std::map<__int64, double> selection;
std::map<__int64, double> insertion;
std::map<__int64, double> merge;
std::map<__int64, double> quick;

void fillArray(int arr[], __int64 size);
void printArray(int arr[], __int64 size);
void fillFiles(__int64 minSize, __int64 maxSize);
void plot();

int main() {
    using std::chrono::duration;
    using std::chrono::duration_cast;
    using std::chrono::high_resolution_clock;
    using std::chrono::milliseconds;

    Sort sort;
    __int64 size = 0, minSize = 0, maxSize = 0;
    std::cout << "Enter the min size of the array:\n> ";
    scanf("%lld", &minSize);
    std::cout << "Enter the max size of the array:\n> ";
    scanf("%lld", &maxSize);

    for (size = minSize; size <= maxSize; ++size) {
        int arr[size];
        int tmp[size];
        duration<double, std::milli> time;
        fillArray(arr, size);
        sort.copy(arr, tmp, size);

        auto t1 = high_resolution_clock::now();
        sort.bubble(arr, size);
        auto t2 = high_resolution_clock::now();
        time = t2 - t1;
        bubble[size] = time.count();
        sort.copy(tmp, arr, size);

        t1 = high_resolution_clock::now();
        sort.selection(arr, size);
        t2 = high_resolution_clock::now();
        time = t2 - t1;
        selection[size] = time.count();
        sort.copy(tmp, arr, size);

        t1 = high_resolution_clock::now();
        sort.insertion(arr, size);
        t2 = high_resolution_clock::now();
        time = t2 - t1;
        insertion[size] = time.count();
        sort.copy(tmp, arr, size);

        t1 = high_resolution_clock::now();
        sort.merge(arr, 0, size - 1);
        t2 = high_resolution_clock::now();
        time = t2 - t1;
        merge[size] = time.count();
        sort.copy(tmp, arr, size);

        t1 = high_resolution_clock::now();
        sort.quick(arr, 0, size - 1);
        t2 = high_resolution_clock::now();
        time = t2 - t1;
        quick[size] = time.count();
    }
    fillFiles(minSize, maxSize);
    plot();

    return 0;
}

void fillArray(int arr[], __int64 size) {
    srand((unsigned)time(NULL));
    for (__int64 i = 0; i < size; i++) {
        arr[i] = rand();
    }
}

void printArray(int arr[], __int64 size) {
    printf("\n");
    for (__int64 i = 0; i < size; i++) {
        printf("%lld\n", arr[i]);
    }
}

void fillFiles(__int64 minSize, __int64 maxSize) {
    std::fstream bubbleFile, selectionFile, insertionFile, mergeFile, quickFile;

    bubbleFile.open("bubbleFile.csv", std::ios::out);
    selectionFile.open("selectionFile.csv", std::ios::out);
    insertionFile.open("insertionFile.csv", std::ios::out);
    mergeFile.open("mergeFile.csv", std::ios::out);
    quickFile.open("quickFile.csv", std::ios::out);

    for (__int64 i = minSize; i <= maxSize; ++i) {
        bubbleFile << i << ',' << bubble[i] << std::endl;
        selectionFile << i << ',' << selection[i] << std::endl;
        insertionFile << i << ',' << insertion[i] << std::endl;
        mergeFile << i << ',' << merge[i] << std::endl;
        quickFile << i << ',' << quick[i] << std::endl;
    }

    bubbleFile.close();
    selectionFile.close();
    insertionFile.close();
    mergeFile.close();
    quickFile.close();
}

void plot() {
    std::fstream Graph;
    Graph.open("Graph.gp", std::ios::out);
    Graph << "set datafile separator \",\"\nset grid\nplot \"bubbleFile.csv\" u 1:2 with lines title \"Bubble\", \\\n\"selectionFile.csv\" u 1:2 with lines title \"Selection\", \\\n\"insertionFile.csv\" u 1:2 with lines title \"Insertion\", \\\n\"mergeFile.csv\" u 1:2 with lines title \"Merge\", \\\n\"quickFile.csv\" u 1:2 with lines title \"Quick\"\npause -1";
    Graph.close();
    system("gnuplot Graph.gp");
}
