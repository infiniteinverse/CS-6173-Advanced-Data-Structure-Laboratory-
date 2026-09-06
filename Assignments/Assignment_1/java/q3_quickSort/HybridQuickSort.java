package Assignments.Assignment_1.java.q3_quickSort;

import java.util.Arrays;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

import sorting.Sorting;
import generation.RandomInputGenerator;

public class HybridQuickSort {

    private static final int TRIALS = 25;
    private static final int BREAKING_POINT = 12;

    private static long comparisonCount = 0;

    public static void hybridQuickSort(
            int[] arr,
            int low,
            int high,
            Sorting.PartitionScheme scheme) {

        if (low >= high) {
            return;
        }

        // Use insertion sort for small subarrays
        if (high - low + 1 <= BREAKING_POINT) {

            Sorting.setComparisonCount(0);

            Sorting.insertionSort(arr, low, high);

            comparisonCount += Sorting.getComparisonCount();

            Sorting.setComparisonCount(0);

            return;
        }

        int pivotIndex = partition(arr, low, high, scheme);

        hybridQuickSort(arr, low, pivotIndex - 1, scheme);
        hybridQuickSort(arr, pivotIndex + 1, high, scheme);
    }



    private static int partition(
            int[] arr,
            int low,
            int high,
            Sorting.PartitionScheme scheme) {

        switch (scheme) {

            case LOMUTO:
                return lomutoPartition(arr, low, high);

            case MEDIAN_OF_THREE:
                return medianOfThreePartition(arr, low, high);

            default:
                throw new IllegalArgumentException(
                        "Unsupported partition scheme: " + scheme);
        }
    }


    private static int lomutoPartition(
            int[] arr,
            int low,
            int high) {

        int pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {

            comparisonCount++;

            if (arr[j] < pivot) {
                i++;
                swap(arr, i, j);
            }
        }

        swap(arr, i + 1, high);

        return i + 1;
    }



    private static int medianOfThreePartition(
            int[] arr,
            int low,
            int high) {

        int mid = low + (high - low) / 2;

        if (arr[low] > arr[mid])
            swap(arr, low, mid);

        if (arr[low] > arr[high])
            swap(arr, low, high);

        if (arr[mid] > arr[high])
            swap(arr, mid, high);

        swap(arr, mid, high - 1);

        int pivot = arr[high - 1];
        int i = low;

        for (int j = low; j < high - 1; j++) {

            comparisonCount++;

            if (arr[j] < pivot) {
                swap(arr, i, j);
                i++;
            }
        }

        swap(arr, i, high - 1);

        return i;
    }


    private static void swap(int[] arr, int i, int j) {

        if (i == j)
            return;

        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }


    public static long getComparisonCount() {
        return comparisonCount;
    }

    public static void setComparisonCount(long count) {
        comparisonCount = count;
    }


    private static void comparisonIsortQsort() {

        try (PrintWriter file = new PrintWriter(
                new FileWriter("comparisonIsortQsort.csv"))) {

            file.println(
                    "InputSize,Comp(InsertionSort),Comp(QuickSort)");

            RandomInputGenerator inputGenerator = new RandomInputGenerator();

            for (int dataSize = 5; dataSize <= 100; dataSize++) {

                long totalInsertionComparisons = 0;
                long totalQuickComparisons = 0;

                for (int trial = 0; trial < TRIALS; trial++) {

                    // Generate input
                    int[] arr = inputGenerator.generateInput(
                            dataSize,
                            1,
                            100,
                            RandomInputGenerator.InputType.RANDOM,
                            RandomInputGenerator.SortOrder.ASCENDING,
                            0.0);

                    // Same input for both algorithms
                    int[] arrCopy = Arrays.copyOf(arr, arr.length);



                    Sorting.setComparisonCount(0);

                    Sorting.insertionSort(arrCopy);

                    totalInsertionComparisons += Sorting.getComparisonCount();

                    // -------------------------
                    // Quick Sort
                    // -------------------------

                    Sorting.setComparisonCount(0);

                    Sorting.quickSort(
                            arr,
                            0,
                            arr.length - 1,
                            Sorting.PartitionScheme.LOMUTO);

                    totalQuickComparisons += Sorting.getComparisonCount();
                }

                double avgInsertion = (double) totalInsertionComparisons / TRIALS;

                double avgQuick = (double) totalQuickComparisons / TRIALS;

                file.println(
                        dataSize + "," +
                                avgInsertion + "," +
                                avgQuick);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void comparisonQsortHybrid() {

        try (PrintWriter file = new PrintWriter(
                new FileWriter("comparisonQsortHybrid.csv"))) {

            file.println(
                    "InputSize,Comp(QuickSort),Comp(HybridQuickSort)");

            RandomInputGenerator inputGenerator = new RandomInputGenerator();

            for (int dataSize = 10; dataSize <= 100; dataSize++) {

                long totalQuickComparisons = 0;
                long totalHybridComparisons = 0;

                for (int trial = 0; trial < TRIALS; trial++) {

                    // Generate input
                    int[] arr = inputGenerator.generateInput(
                            dataSize,
                            1,
                            100,
                            RandomInputGenerator.InputType.RANDOM,
                            RandomInputGenerator.SortOrder.ASCENDING,
                            0.0);

                    // Same input for both algorithms
                    int[] arrCopy = Arrays.copyOf(arr, arr.length);

                    // -------------------------
                    // Normal Quick Sort
                    // -------------------------

                    Sorting.setComparisonCount(0);

                    Sorting.quickSort(
                            arr,
                            0,
                            arr.length - 1,
                            Sorting.PartitionScheme.LOMUTO);

                    totalQuickComparisons += Sorting.getComparisonCount();

                    // -------------------------
                    // Hybrid Quick Sort
                    // -------------------------

                    setComparisonCount(0);
                    Sorting.setComparisonCount(0);

                    hybridQuickSort(
                            arrCopy,
                            0,
                            arrCopy.length - 1,
                            Sorting.PartitionScheme.LOMUTO);

                    totalHybridComparisons += getComparisonCount();
                }

                double avgQuick = (double) totalQuickComparisons / TRIALS;

                double avgHybrid = (double) totalHybridComparisons / TRIALS;

                file.println(
                        dataSize + "," +
                                avgQuick + "," +
                                avgHybrid);
            }

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {

        // Experiment 1:
        // Insertion Sort vs Quick Sort
        comparisonIsortQsort();

        // Experiment 2:
        // Quick Sort vs Hybrid Quick Sort
        comparisonQsortHybrid();
    }
}