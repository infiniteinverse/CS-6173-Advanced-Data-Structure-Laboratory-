package tests;

// Import your generator class and its enums
import generation.RandomInputGenerator;
import generation.RandomInputGenerator.InputType;
import generation.RandomInputGenerator.SortOrder;

import java.util.Arrays;

public class MainTest {
    public static void main(String[] args) {
        // Create an instance of your generator
        RandomInputGenerator gen = new RandomInputGenerator();

        int size = 10;
        int min = 1;
        int max = 100;

        // Generate different types of arrays
        int[] randomArr = gen.generateInput(size, min, max, InputType.RANDOM, SortOrder.ASCENDING, 0.1);
        int[] sortedArr = gen.generateInput(size, min, max, InputType.SORTED, SortOrder.ASCENDING, 0.0);
        int[] reversedArr = gen.generateInput(size, min, max, InputType.REVERSE_SORTED, SortOrder.DESCENDING, 0.0);
        int[] nearlySortedArr = gen.generateInput(size, min, max, InputType.NEARLY_SORTED, SortOrder.ASCENDING, 0.1);

        // Print them out (Arrays.toString cleanly formats the array)
        System.out.println("Truly Random:   " + Arrays.toString(randomArr));
        System.out.println("Sorted:         " + Arrays.toString(sortedArr));
        System.out.println("Reversed:       " + Arrays.toString(reversedArr));
        System.out.println("Nearly Sorted:  " + Arrays.toString(nearlySortedArr));
    }
}