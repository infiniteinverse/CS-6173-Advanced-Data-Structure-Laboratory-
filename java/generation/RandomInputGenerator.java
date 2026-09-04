package generation;
import java.util.Arrays;
import java.util.Random;

public class RandomInputGenerator{
    public enum InputType{
        RANDOM, 
        SORTED,
        REVERSE_SORTED,
        NEARLY_SORTED,
        HIGHLY_INVERSIONAL
    }

    public enum SortOrder{
        ASCENDING,
        DESCENDING
    }

    private Random Generator;

    public RandomInputGenerator(){
        this.Generator = new Random();
    }

    private int[] generateRandomArray(int size, int minValue, int maxValue){
        int[] array = new int[size];
        for(int i = 0; i < size; i++){
            array[i] = Generator.nextInt(minValue, maxValue + 1);
        }
        return array;
    }

    private void sortData(int[] array, SortOrder order){
       Arrays.sort(array);
       if(order == SortOrder.DESCENDING){
        reverseArray(array);
    }
    }

    private void reverseArray(int[] array){
        int start = 0;
        int end = array.length - 1;
        while(start < end){
            int temp = array[start];
            array[start] = array[end];
            array[end] = temp;
            start++;
            end--;
        }
    }

    public int[] generateInput(int size, int minValue, int maxValue, InputType type, SortOrder order, double inversionPercentage ){
        int[] array = generateRandomArray(size, minValue, maxValue);
        int numberOfInversions = 0;
        switch(type){ 
            case RANDOM:
                break;
            case SORTED:
                sortData(array, order);
                break;
            case REVERSE_SORTED:
                sortData(array, order == SortOrder.ASCENDING ? SortOrder.DESCENDING : SortOrder.ASCENDING);
                break;
            case NEARLY_SORTED:
                sortData(array, order);
                // Introduce a small number of inversions
                numberOfInversions = (int)(size * inversionPercentage);
                for(int i = 0; i < numberOfInversions; i++){
                    int index1 = Generator.nextInt(size);
                    int index2 = Generator.nextInt(size);
                    int temp = array[index1];
                    array[index1] = array[index2];
                    array[index2] = temp;
                }
                break;
            case HIGHLY_INVERSIONAL:
                numberOfInversions = (int)(size * inversionPercentage);
                sortData(array, order == SortOrder.ASCENDING ? SortOrder.DESCENDING : SortOrder.ASCENDING);
                // Introduce a large number of inversions
                numberOfInversions = (int)(size * inversionPercentage);
                for(int i = 0; i < numberOfInversions; i++){
                    int index1 = Generator.nextInt(size);
                    int index2 = Generator.nextInt(size);
                    int temp = array[index1];
                    array[index1] = array[index2];
                    array[index2] = temp;
                }
                break;
        }
        return array;
    }


}
