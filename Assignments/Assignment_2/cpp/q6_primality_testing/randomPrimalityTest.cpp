#include <iostream>
#include <fstream>
#include <random>

class FermatTest{
private:
    std::mt19937 generator;

public:
    FermatTest(): generator((std::random_device{}())){
        // constructor created
    }

     bool fermatTest(unsigned long long n, int k = 100) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0) return false;

        std::uniform_int_distribution<unsigned long long> dist(2, n - 2);

        for (int i = 0; i < k; ++i) {
            unsigned long long a = dist(generator);

            if (gcd(a, n) > 1) {
                return false; // Composite
            }

            // Check Fermat's condition: a^(n-1) == 1 (mod n)
            if (mod_pow(a, n - 1, n) != 1) {
                return false; // Composite
            }
        }
        return true; // Probably prime
    }

    unsigned long long mod_mul(unsigned long long a, unsigned long long b, unsigned long long mod) {
    unsigned long long res = 0;
        a %= mod;
        while (b > 0) {
            if (b & 1) res = (res + a) % mod;
            a = (a * 2) % mod;
            b >>= 1;
        }
        return res;
        }

    // Fast modular exponentiation: (base^exp) % mod
    unsigned long long mod_pow(unsigned long long base, unsigned long long exp, unsigned long long mod) {
        unsigned long long res = 1;
        base %= mod;
        while (exp > 0) {
            if (exp & 1) res = mod_mul(res, base, mod);
            base = mod_mul(base, base, mod);
            exp >>= 1;
        }
        return res;
    }

    // Greatest Common Divisor
    unsigned long long gcd(unsigned long long a, unsigned long long b) {
        while (b != 0) {
            unsigned long long t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    // Deterministic ground truth check for verification
    bool isActuallyPrime(unsigned long long n) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 2 == 0 || n % 3 == 0) return false;
        for (unsigned long long i = 5; i * i <= n; i += 6) {
            if (n % i == 0 || n % (i + 2) == 0) return false;
        }
        return true;
    }


};

int main(){
    fstream
    return 0;
}