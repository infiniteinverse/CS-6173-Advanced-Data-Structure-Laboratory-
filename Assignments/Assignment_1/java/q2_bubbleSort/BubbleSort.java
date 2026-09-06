package Assignments.Assignment_1.java.q2_bubbleSort;
import java.util.Arrays;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

import sorting.Sorting;
import generation.RandomInputGenerator;

public class BubbleSort {
    private 
    static int comparisonCount = 0;
    final int  TRIALS = 25;
    private RandomInputGenerator inputGenerator;

    public static void bubbleSort(int[] arr) {
        int n = arr.length;
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                comparisonCount++; // Counting comparison
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    public static int getComparisonCount() {
        return comparisonCount;
    }

    public static void setComparisonCount(int count) {
        comparisonCount = count;
    }

    public void highlyInversionalArrayComparison(){
        try (PrintWriter file = new PrintWriter(new FileWriter("Assignments/Assignment_1/java/q2_bubbleSort/highlyInversional.csv"))) {
            file.println("InputSize, Comp(NES), Comp(ES)");
            for(int dataSize = 1; dataSize <= 100; dataSize ++) {
                int comparisonWithoutEarlyStopping  = 0, comparisonWithEarlyStopping = 0;
                for(int trial = 0; trial < TRIALS; trial++) {
                    int [] arr = inputGenerator.generateInput(dataSize, 1, 100, RandomInputGenerator.InputType.HIGHLY_INVERSIONAL, RandomInputGenerator.SortOrder.ASCENDING, 0.95);
                    int [] arrCopy = Arrays.copyOf(arr, arr.length);
                    Sorting.bubbleSort(arrCopy);
                    bubbleSort(arr);
                    comparisonWithEarlyStopping += Sorting.getComparisonCount();
                    comparisonWithoutEarlyStopping += BubbleSort.getComparisonCount();
                    Sorting.setComparisonCount(0);
                    BubbleSort.setComparisonCount(0);
                }
                double avgCompWithEarlyStopping = (double) comparisonWithEarlyStopping / TRIALS;
                double avgCompWithoutEarlyStopping = (double) comparisonWithoutEarlyStopping / TRIALS;
                file.println(dataSize + "," + avgCompWithoutEarlyStopping + "," + avgCompWithEarlyStopping);
            }
        } catch (IOException e) {
            System.out.println("Failed to open the file: " + e.getMessage());
        }
    }



    public void nearlySortedArrayComparison(){
        try (PrintWriter file = new PrintWriter(new FileWriter("Assignments/Assignment_1/java/q2_bubbleSort/nearlySorted.csv"))) {
            file.println("InputSize, Comp(NES), Comp(ES)");
            for(int dataSize = 1; dataSize <= 100; dataSize ++) {
                int comparisonWithoutEarlyStopping  = 0, comparisonWithEarlyStopping = 0;
                for(int trial = 0; trial < TRIALS; trial++) {
                    int [] arr = inputGenerator.generateInput(dataSize, 1, 100, RandomInputGenerator.InputType.NEARLY_SORTED, RandomInputGenerator.SortOrder.ASCENDING, 0.12);
                    int [] arrCopy = Arrays.copyOf(arr, arr.length);
                    Sorting.bubbleSort(arrCopy);
                    bubbleSort(arr);
                    comparisonWithEarlyStopping += Sorting.getComparisonCount();
                    comparisonWithoutEarlyStopping += BubbleSort.getComparisonCount();
                    Sorting.setComparisonCount(0);
                    BubbleSort.setComparisonCount(0);
                }
                double avgCompWithEarlyStopping = (double) comparisonWithEarlyStopping / TRIALS;
                double avgCompWithoutEarlyStopping = (double) comparisonWithoutEarlyStopping / TRIALS;
                file.println(dataSize + "," + avgCompWithoutEarlyStopping + "," + avgCompWithEarlyStopping);
            }
        } catch (IOException e) {
            System.out.println("Failed to open the file: " + e.getMessage());
        }
    }



    public void sortedArrayComparison(){
        try (PrintWriter file = new PrintWriter(new FileWriter("Assignments/Assignment_1/java/q2_bubbleSort/sorted.csv"))) {
            file.println("InputSize, Comp(NES), Comp(ES)");
            for(int dataSize = 1; dataSize <= 100; dataSize ++) {
                int comparisonWithoutEarlyStopping  = 0, comparisonWithEarlyStopping = 0;
                for(int trial = 0; trial < TRIALS; trial++) {
                    int [] arr = inputGenerator.generateInput(dataSize, 1, 100, RandomInputGenerator.InputType.SORTED, RandomInputGenerator.SortOrder.ASCENDING, 0.0);
                    int [] arrCopy = Arrays.copyOf(arr, arr.length);
                    Sorting.bubbleSort(arrCopy);
                    bubbleSort(arr);
                    comparisonWithEarlyStopping += Sorting.getComparisonCount();
                    comparisonWithoutEarlyStopping += BubbleSort.getComparisonCount();
                    Sorting.setComparisonCount(0);
                    BubbleSort.setComparisonCount(0);
                }
                double avgCompWithEarlyStopping = (double) comparisonWithEarlyStopping / TRIALS;
                double avgCompWithoutEarlyStopping = (double) comparisonWithoutEarlyStopping / TRIALS;
                file.println(dataSize + "," + avgCompWithoutEarlyStopping + "," + avgCompWithEarlyStopping);
            }
        } catch (IOException e) {
            System.out.println("Failed to open the file: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        BubbleSort bubbleSort = new BubbleSort();
        bubbleSort.inputGenerator = new RandomInputGenerator();
        bubbleSort.highlyInversionalArrayComparison();
        bubbleSort.nearlySortedArrayComparison();
        bubbleSort.sortedArrayComparison();
    }
};



