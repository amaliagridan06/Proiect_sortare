#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void bubbleSort(int *arr, int n) {
    if (n > 50000) return; 
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void insertionSort(int *arr, int n) {
    if (n > 50000) return;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void merge(int *arr, int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *L = malloc(n1 * sizeof(int)), *R = malloc(n2 * sizeof(int));
    if (!L || !R) return;
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    free(L); free(R);
}

void mergeSort(int *arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void mergeSortWrapper(int *arr, int n) { mergeSort(arr, 0, n - 1); }

void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int pivot = arr[low + (high - low) / 2];
        int i = low, j = high;
        while (i <= j) {
            while (arr[i] < pivot) i++;
            while (arr[j] > pivot) j--;
            if (i <= j) {
                int t = arr[i]; arr[i] = arr[j]; arr[j] = t;
                i++; j--;
            }
        }
        if (low < j) quickSort(arr, low, j);
        if (i < high) quickSort(arr, i, high);
    }
}

void quickSortWrapper(int *arr, int n) { quickSort(arr, 0, n - 1); }

int getMax(int *arr, int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) if (arr[i] > max) max = arr[i];
    return max;
}

void countingForRadix(int *arr, int n, int exp) {
    int *output = malloc(n * sizeof(int));
    if (!output) return;
    int i, count[10] = {0};
    for (i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++) count[i] += count[i - 1];
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }
    for (i = 0; i < n; i++) arr[i] = output[i];
    free(output);
}

void radixSort(int *arr, int n) {
    if (n <= 0) return;
    int m = getMax(arr, n);
    for (int exp = 1; m / exp > 0; exp *= 10) countingForRadix(arr, n, exp);
}

void genRandom(int *arr, int n) { for (int i = 0; i < n; i++) arr[i] = rand() % 1000000; }
void genSorted(int *arr, int n) { for (int i = 0; i < n; i++) arr[i] = i; }
void genReverse(int *arr, int n) { for (int i = 0; i < n; i++) arr[i] = n - i; }
void genAlmost(int *arr, int n) {
    genSorted(arr, n);
    int swaps = n / 100 + 1;
    for (int i = 0; i < swaps; i++) {
        int idx1 = rand() % n, idx2 = rand() % n;
        int t = arr[idx1]; arr[idx1] = arr[idx2]; arr[idx2] = t;
    }
}
void genPlate(int *arr, int n) { for (int i = 0; i < n; i++) arr[i] = rand() % 100; }

void runExperiment(void (*sortFunc)(int*, int), char* algoName, int n, int type, FILE *f) {
    if ((n > 50000) && (strcmp(algoName, "BubbleSort") == 0 || strcmp(algoName, "InsertionSort") == 0)) {
        fprintf(f, "%-15s | N=%-10d | [SARIT - TIMP EXCESIV]\n", algoName, n);
        return;
    }

    int *orig = malloc(n * sizeof(int));
    int *work = malloc(n * sizeof(int));
    if (!orig || !work) return;

    if (type == 0) genRandom(orig, n);
    else if (type == 1) genSorted(orig, n);
    else if (type == 2) genReverse(orig, n);
    else if (type == 3) genAlmost(orig, n);
    else genPlate(orig, n);

    memcpy(work, orig, n * sizeof(int));

    clock_t start = clock();
    sortFunc(work, n);
    clock_t end = clock();

    double time = ((double)(end - start)) / CLOCKS_PER_SEC;
    fprintf(f, "%-15s | N=%-10d | %.6f s\n", algoName, n, time);
    printf("%-15s | N=%-10d | %.6f s\n", algoName, n, time);

    free(orig); free(work);
}

int main() {
    srand(time(NULL));
    FILE *f = fopen("rezultate.txt", "w");
    if (f == NULL) return 1;

    long sizes[] = {100, 1000, 10000, 100000, 1000000, 10000000}; 
    char* types[] = {"Random", "Sorted", "Reverse", "Almost Sorted", "Plate"};

    fprintf(f, "RAPORT SORTARE\n\n");

    for (int s = 0; s < 6; s++) {
        printf("\n>>> N = %ld\n", sizes[s]);
        fprintf(f, "\n Dimensiune: %ld \n", sizes[s]);
        for (int t = 0; t < 5; t++) {
            fprintf(f, "\nTip date: %s\n", types[t]);
            runExperiment(bubbleSort, "BubbleSort", sizes[s], t, f);
            runExperiment(insertionSort, "InsertionSort", sizes[s], t, f);
            runExperiment(mergeSortWrapper, "MergeSort", sizes[s], t, f);
            runExperiment(quickSortWrapper, "QuickSort", sizes[s], t, f);
            runExperiment(radixSort, "RadixSort", sizes[s], t, f);
        }
    }

    fclose(f);
    return 0;
}
