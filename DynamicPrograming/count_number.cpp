#include <iostream>
#include <string>
#include <vector>
#include <cstring> // For memset
#include <algorithm>

using namespace std;

// dp[pos][tight][prev_digit_or_10]
// pos: current digit position (0 to length of N - 1)
// tight: boolean flag, true if restricted by the digits of the upper bound number string
// prev_digit_or_10: previous digit (0-9), or 10 if no previous digit (initial state or after leading zeros)
long long dp[20][2][11];
string s; // Using 's' to represent the number string

// Recursive function with memoization to count valid numbers
// starting from 'pos' with given constraints
long long solve(int pos, bool tight, int prev_digit_or_10) {
    // Base case: We have processed all digits
    if (pos == s.size()) {
        return 1; // We have successfully formed one valid number
    }

    // Memoization: If the state has been computed, return the stored result
    if (dp[pos][tight][prev_digit_or_10] != -1) {
        return dp[pos][tight][prev_digit_or_10];
    }

    long long res = 0; // Result for the current state
    int limit = tight ? (s[pos] - '0') : 9; // Upper limit for the current digit

    // Iterate through possible digits for the current position
    for (int digit = 0; digit <= limit; digit++) {
        // Check the constraint: no two adjacent digits are the same
        // If there was a previous non-leading digit (prev_digit_or_10 != 10)
        // AND the current digit is the same as the previous one, skip.
        if (prev_digit_or_10 != 10 && digit == prev_digit_or_10) {
            continue;
        }

        // Calculate the next state for the previous digit
        // If the current digit is 0 AND the previous state was 10 (meaning we are still placing leading zeros),
        // the next previous state remains 10.
        // Otherwise, the next previous state is the current digit.
        int next_prev_digit_or_10 = (digit == 0 && prev_digit_or_10 == 10) ? 10 : digit;

        // Recursively call for the next position
        // Update tight flag: it remains tight only if it was tight AND we chose the limit digit
        res += solve(pos + 1, tight && (digit == limit), next_prev_digit_or_10);
    }

    // Store and return the result
    return dp[pos][tight][prev_digit_or_10] = res;
}

// Helper function to count valid numbers from 0 up to N (inclusive)
long long countValid(long long N) {
    if (N < 0) return 0; // No valid numbers less than 0
    s = to_string(N); // Convert N to string
    // Initialize DP table with -1 to indicate uncomputed states
    memset(dp, -1, sizeof(dp));
    // Start solving from position 0, initially tight (restricted by N),
    // with no previous digit (represented by 10)
    return solve(0, true, 10);
}

int main() {
    // Optimize input/output operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long a, b;
    cin >> a >> b; // Read the input range [a, b]

    // Count valid numbers up to 'b'
    long long count_b = countValid(b);

    // Count valid numbers up to 'a - 1'
    long long count_a_minus_1 = countValid(a - 1);

    // The result for the range [a, b] is the difference
    cout << count_b - count_a_minus_1 << endl;

    return 0;
}
