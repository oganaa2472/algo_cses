#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Function to calculate GCD
long long gcd(long long a, long long b) {
    return b == 0 ? a : gcd(b, a % b);
}

// Function to calculate LCM using GCD
long long lcm(long long a, long long b) {
    return (a * b) / gcd(a, b);
}

// Function to calculate the number of integers divisible by at least one prime using Inclusion-Exclusion
long long countDivisible(long long n, const vector<long long>& primes) {
    long long result = 0;
    int k = primes.size();
    
    // Loop over all subsets of primes (bitwise)
    for (int i = 1; i < (1 << k); ++i) {
        long long current_lcm = 1;
        int bits = __builtin_popcount(i); // Count the number of primes in this subset
        
        // Loop over each bit in the subset
        for (int j = 0; j < k; ++j) {
            if (i & (1 << j)) {
                current_lcm = lcm(current_lcm, primes[j]);
                // If the LCM exceeds n, break out early (no number <= n can be divisible by it)
                if (current_lcm > n) {
                    current_lcm = n + 1;
                    break;
                }
            }
        }
        
        // If LCM is valid (<= n), add or subtract the count based on inclusion-exclusion
        if (current_lcm <= n) {
            long long divisible_count = n / current_lcm;
            if (bits % 2 == 1) {
                result += divisible_count; // Include for odd-sized subsets
            } else {
                result -= divisible_count; // Exclude for even-sized subsets
            }
        }
    }
    
    return result;
}

int main() {
    long long n, k;
    cin >> n >> k;
    
    vector<long long> primes(k);
    for (int i = 0; i < k; ++i) {
        cin >> primes[i];
    }
    
    // Calculate the result using Inclusion-Exclusion
    cout << countDivisible(n, primes) << endl;
    
    return 0;
}
