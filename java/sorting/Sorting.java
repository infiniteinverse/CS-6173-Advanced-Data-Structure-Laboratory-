package sorting;

public class Sorting {
    
    // Static counter to track comparisons across all method calls
    private static long comparisonCount = 0;

    // Enum for QuickSort partitioning schemes
    public enum PartitionScheme {
        LOMUTO,
        HOARE,
        MEDIAN_OF_THREE
    }

    // --- Getter and Setter for the Counter ---
    public static long getComparisonCount() {
        return comparisonCount;
    }

    public static void setComparisonCount(long count) {
        comparisonCount = count;
    }

    // --- Bubble Sort ---
    public static void bubbleSort(int[] arr) {
        int n = arr.length;
        boolean flag;
        for (int i = 0; i < n - 1; i++) {
            flag = false;
            for (int j = 0; j < n - i - 1; j++) {
                comparisonCount++; // Counting comparison
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                    flag = true;
                }
            }
            if (!flag) break;
        }
    }

    // --- Selection Sort ---
    public static void selectionSort(int[] arr) {
        int n = arr.length;
        for (int i = 0; i < n - 1; i++) {
            int minIndex = i;
            for (int j = i + 1; j < n; j++) {
                comparisonCount++; // Counting comparison
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            int temp = arr[minIndex];
            arr[minIndex] = arr[i];
            arr[i] = temp;
        }
    }

    // --- Insertion Sort ---
    public static void insertionSort(int[] arr) {
        int n = arr.length;
        for (int i = 1; i < n; ++i) {
            int key = arr[i];
            int j = i - 1;

            while (j >= 0) {
                comparisonCount++; // Counting comparison
                if (arr[j] > key) {
                    arr[j + 1] = arr[j];
                    j = j - 1;
                } else {
                    break;
                }
            }
            arr[j + 1] = key;
        }
    }

    public static void insertionSort(int[] arr, int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            int key = arr[i];
            int j = i - 1;

            while (j >= left) {
                comparisonCount++; // Counting comparison
                if (arr[j] > key) {
                    arr[j + 1] = arr[j];
                    j--;
                } else {
                    break;
                }
            }
            arr[j + 1] = key;
        }
    }

    // --- Merge Sort ---
    public static void mergeSort(int[] arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);

            int n1 = mid - left + 1;
            int n2 = right - mid;
            int[] L = new int[n1];
            int[] R = new int[n2];
            
            for (int i = 0; i < n1; i++) L[i] = arr[left + i];
            for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
            
            int i = 0, j = 0, k = left;
            while (i < n1 && j < n2) {
                comparisonCount++; // Counting comparison
                if (L[i] <= R[j]) {
                    arr[k] = L[i];
                    i++;
                } else {
                    arr[k] = R[j];
                    j++;
                }
                k++;
            }
            while (i < n1) arr[k++] = L[i++];
            while (j < n2) arr[k++] = R[j++];
        }
    }

    // --- Quick Sort Master Methods ---
    
    // Default to Lomuto if no scheme is provided (overloading)
    public static void quickSort(int[] arr, int low, int high) {
        quickSort(arr, low, high, PartitionScheme.LOMUTO);
    }

    public static void quickSort(int[] arr, int low, int high, PartitionScheme scheme) {
        if (low < high) {
            int pi;
            if (scheme == PartitionScheme.HOARE) {
                pi = hoarePartition(arr, low, high);
                quickSort(arr, low, pi, scheme); // Hoare includes pivot in left half
            } else {
                if (scheme == PartitionScheme.MEDIAN_OF_THREE) {
                    medianOfThree(arr, low, high); // Adjusts pivot
                }
                pi = lomutoPartition(arr, low, high);
                quickSort(arr, low, pi - 1, scheme);
                quickSort(arr, pi + 1, high, scheme);
            }
        }
    }

    // --- Quick Sort Partitions ---

    private static int lomutoPartition(int[] arr, int low, int high) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            comparisonCount++; // Counting comparison
            if (arr[j] < pivot) {
                i++;
                swap(arr, i, j);
            }
        }
        swap(arr, i + 1, high);
        return i + 1;
    }

    private static int hoarePartition(int[] arr, int low, int high) {
        int pivot = arr[low];
        int i = low - 1;
        int j = high + 1;

        while (true) {
            do {
                i++;
                comparisonCount++;
            } while (arr[i] < pivot);

            do {
                j--;
                comparisonCount++;
            } while (arr[j] > pivot);

            if (i >= j) return j;
            swap(arr, i, j);
        }
    }

    private static void medianOfThree(int[] arr, int low, int high) {
        int mid = low + (high - low) / 2;
        
        comparisonCount++;
        if (arr[low] > arr[mid]) swap(arr, low, mid);
        
        comparisonCount++;
        if (arr[low] > arr[high]) swap(arr, low, high);
        
        comparisonCount++;
        if (arr[mid] > arr[high]) swap(arr, mid, high);

        // Move the median (now at mid) to the end to act as the Lomuto pivot
        swap(arr, mid, high);
    }

    // --- Helper Utility ---
    private static void swap(int[] arr, int i, int j) {
        if (i == j) return;
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}