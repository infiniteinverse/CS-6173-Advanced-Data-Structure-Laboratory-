#include <iostream>
#include <fstream>
#include <random>
#include <iomanip>
#include <string>

using namespace std;

using ull = unsigned long long;
using u128 = __uint128_t;


// ---------------------------------------------------------
// (a * b) % mod
// Uses 128-bit intermediate value to avoid overflow.
// ---------------------------------------------------------
ull modMultiply(ull a, ull b, ull mod)
{
    return (u128)a * b % mod;
}


// ---------------------------------------------------------
// (a^b) % mod using binary exponentiation
// ---------------------------------------------------------
ull modPower(ull a, ull b, ull mod)
{
    ull result = 1;

    while (b > 0)
    {
        if (b & 1)
            result = modMultiply(result, a, mod);

        a = modMultiply(a, a, mod);

        b >>= 1;
    }

    return result;
}


// ---------------------------------------------------------
// Miller-Rabin primality test
// ---------------------------------------------------------
bool millerRabin(ull n, int k, ofstream& file)
{
    // Handle small numbers
    if (n < 2)
    {
        file << n << ",0,0,0,0,0,0,Not Prime\n";
        return false;
    }

    if (n == 2 || n == 3)
    {
        file << n << ",0,0,0,0,0,0,Prime\n";
        return true;
    }

    if (n % 2 == 0)
    {
        file << n << ",0,0,0,0,0,0,Not Prime\n";
        return false;
    }


    // -----------------------------------------------------
    // Write n - 1 = 2^s * d
    // -----------------------------------------------------
    ull d = n - 1;
    int s = 0;

    while ((d & 1) == 0)
    {
        d >>= 1;
        s++;
    }


    // Random number generator
    random_device rd;
    mt19937_64 generator(rd());

    uniform_int_distribution<ull> distribution(2, n - 2);


    // -----------------------------------------------------
    // Perform k Miller-Rabin rounds
    // -----------------------------------------------------
    for (int iteration = 1; iteration <= k; iteration++)
    {
        ull a = distribution(generator);

        // x = a^d mod n
        ull x = modPower(a, d, n);

        // Initial state
        bool passed = false;

        if (x == 1 || x == n - 1)
        {
            passed = true;

            file << n << ","
                 << iteration << ","
                 << a << ","
                 << 0 << ","
                 << x << ","
                 << x << ","
                 << "Round Passed\n";
        }
        else
        {
            // Repeat squaring
            for (int r = 1; r < s; r++)
            {
                x = modMultiply(x, x, n);

                file << n << ","
                     << iteration << ","
                     << a << ","
                     << r << ","
                     << x << ","
                     << x << ","
                     << "Intermediate\n";

                if (x == n - 1)
                {
                    passed = true;
                    break;
                }
            }
        }


        // If this round fails, n is definitely composite
        if (!passed)
        {
            file << n << ","
                 << iteration << ","
                 << a << ","
                 << "-," 
                 << x << ","
                 << x << ","
                 << "COMPOSITE\n";

            return false;
        }
    }


    // All k rounds passed
    file << n << ","
         << k << ","
         << "- ," 
         << "- ," 
         << "- ," 
         << "- ," 
         << "- ," 
         << "PROBABLY PRIME\n";

    return true;
}


int main()
{
    ull n;
    int k;

    cout << "Enter number to test: ";
    cin >> n;

    cout << "Enter number of Miller-Rabin iterations: ";
    cin >> k;


    ofstream file("miller_rabin_results.csv");

    if (!file.is_open())
    {
        cerr << "Error: Could not open CSV file.\n";
        return 1;
    }


    // CSV header
    file << "Number,Iteration,Base,SquareStep,X,Value,Result\n";


    bool result = millerRabin(n, k, file);


    cout << "\n--------------------------------\n";
    cout << "Miller-Rabin Result\n";
    cout << "--------------------------------\n";

    cout << "Number: " << n << "\n";
    cout << "Iterations: " << k << "\n";

    if (result)
        cout << "Result: Probably Prime\n";
    else
        cout << "Result: Composite\n";

    cout << "\nResults stored in:\n";
    cout << "miller_rabin_results.csv\n";


    file.close();

    return 0;
}