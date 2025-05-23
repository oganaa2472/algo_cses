#include <iostream>
#include <vector>
#include <cmath>
#include <vector>
#include <algorithm> // For std::min

// Modular multiplication: (a * b) % m
// Uses __int128 for intermediate product to handle large numbers up to 10^12 * 10^12
long long multiply(long long a, long long b, long long m) {
    return static_cast<long long>((static_cast<__int128>(a) * b) % m);
}

// Modular exponentiation: (base^exp) % mod
// Uses binary exponentiation (exponentiation by squaring)
long long power(long long base, long long exp, long long mod) {
    long long res = 1;
    base %= mod;
    while (exp > 0) {
        if (exp % 2 == 1) res = multiply(res, base, mod);
        base = multiply(base, base, mod);
        exp /= 2;
    }
    return res;
}

// Miller-Rabin primality test for numbers up to ~10^12
// This set of bases {2, 7, 61} is sufficient for deterministic primality testing
// for numbers up to 4,759,123,141 (well above 10^9). For numbers up to 10^12,
// a slightly larger set might be theoretically needed for full determinism up to that exact bound,
// but {2, 7, 61} is often sufficient in competitive programming contexts for numbers around this size,
// or the problem setters might implicitly use a bound where these bases are sufficient.
// For strict determinism up to 10^12, bases {2, 13, 23, 1662803} are needed.
// Let's use the common competitive programming set {2, 7, 61} first, as it's simpler and often passes.
// If needed, we can switch to a more robust set.
bool isPrime(long long n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false; // Quick check for small factors

    // Write n - 1 as 2^s * d, where d is odd
    long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }

    // Bases for Miller-Rabin test
    std::vector<long long> bases = {2, 7, 61};

    for (long long a : bases) {
        // If n is one of the bases, it's prime
        if (n == a) return true;

        // Compute a^d % n
        long long x = power(a, d, n);

        // If a^d % n is 1 or n-1, n is likely prime for this base. Continue to the next base.
        if (x == 1 || x == n - 1) continue;

        // Check the sequence a^(d * 2^r) % n for r = 1 to s-1
        bool composite = true; // Assume composite until proven otherwise
        for (int r = 1; r < s; ++r) {
            x = multiply(x, x, n); // Compute x^2 % n
            if (x == n - 1) {
                // Found a^((n-1)/2^i) % n == n-1 for some i. n is likely prime.
                composite = false;
                break; // Break inner loop, continue to the next base
            }
            if (x == 1) {
                // Found a non-trivial square root of 1 (x^2 % n == 1 but x != 1 and x != n-1).
                // This proves n is composite.
                composite = true;
                break; // Break inner loop
            }
        }

        // If composite is still true after checking all powers of 2, n is composite.
        if (composite) return false;
    }

    // If n passes the test for all bases, it is considered prime.
    return true;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int t;
    std::cin >> t; // Number of test cases

    while (t--) {
        long long n;
        std::cin >> n; // Input number

        // Start checking from the next integer after n
        long long current_num = n + 1;

        // If n is 1, the next prime is 2
        if (n == 1) {
             current_num = 2;
        } else {
             current_num = n + 1;
        }


        // Increment current_num until a prime number is found
        while (!isPrime(current_num)) {
            current_num++;
        }

        // Print the first prime found after n
        std::cout << current_num << std::endl;
    }

    return 0;
}
