package Assignments.Assignment_1.java.q1_coinToss;

import java.util.Random;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.IOException;

public class CoinSimulator {
    private Random random;

    public CoinSimulator() {
        this.random = new Random();
    }

    public boolean flipCoin() {
        return random.nextBoolean(); // Returns true (Heads) or false (Tails)
    }

    // --- 1. Single Coin Toss Simulation ---
    public void oneCoinToss() {
        int N = 5000;
        int heads = 0, tails = 0;

        // "try-with-resources" automatically closes the file when done (replaces file.close())
        try (PrintWriter file = new PrintWriter(new FileWriter("Assignments/Assignment_1/java/q1_coinToss/oneCoinToss.csv"))) {
            file.println("Toss,Heads,Tails,HeadProbability,TailProbability");

            for (int i = 1; i <= N; i++) {
                if (flipCoin()) {
                    heads++;
                } else {
                    tails++;
                }

                double headProb = (double) heads / i;
                double tailProb = (double) tails / i;

                // Writing to CSV
                file.println(i + "," + heads + "," + tails + "," + headProb + "," + tailProb);
            }
            
            // Console output mirroring your C++ cout
            System.out.printf("%d %d %.4f %.4f%n", heads, tails, (double)heads/N, (double)tails/N);

        } catch (IOException e) {
            System.out.println("Failed to open the file: " + e.getMessage());
        }
    }

    // --- 2. Two Coin Toss Simulation ---
    public void twoCoinToss() {
        int N = 5000;
        int HH = 0, HT = 0, TH = 0, TT = 0;

        try (PrintWriter file = new PrintWriter(new FileWriter("Assignments/Assignment_1/java/q1_coinToss/twoCoinToss.csv"))) {
            file.println("Toss,HH,HT,TH,TT,P(HH),P(HT),P(TH),P(TT)");

            for (int i = 1; i <= N; i++) {
                boolean result1 = flipCoin();
                boolean result2 = flipCoin();

                if (result1) {
                    if (result2) HH++;
                    else HT++;
                } else {
                    if (result2) TH++;
                    else TT++;
                }

                double hhProb = (double) HH / i;
                double htProb = (double) HT / i;
                double thProb = (double) TH / i;
                double ttProb = (double) TT / i;

                // Writing to CSV
                file.println(i + "," + HH + "," + HT + "," + TH + "," + TT + "," 
                           + hhProb + "," + htProb + "," + thProb + "," + ttProb);
            }

            System.out.printf("%d %d %d %d %.4f %.4f %.4f %.4f%n", 
                              HH, HT, TH, TT, 
                              (double)HH/N, (double)HT/N, (double)TH/N, (double)TT/N);

        } catch (IOException e) {
            System.out.println("Failed to open the file: " + e.getMessage());
        }
    }

    // --- 3. The Main Method (Entry Point) ---
    public static void main(String[] args) {
        // Instantiate the class to access its non-static methods
        CoinSimulator simulator = new CoinSimulator();

        // Run the experiments
        simulator.oneCoinToss();
        simulator.twoCoinToss();
    }
}