#include <iostream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

// DP table: [position][previous_digit][leading_zeros][tight_constraint]
long long dp[20][11][2][2];
string s;

long long solve(int idx, int prev, bool leading_zeros, bool tight) {
    // Base case: If we constructed a full number
    if (idx == s.length()) {
        return 1;
    }
    
    // Check memoization
    if (dp[idx][prev][leading_zeros][tight] != -1) {
        return dp[idx][prev][leading_zeros][tight];
    }

    long long ans = 0;
    // Determine the upper bound for the current digit
    int limit = tight ? (s[idx] - '0') : 9;

    for (int digit = 0; digit <= limit; digit++) {
        // Calculate new tight constraint
        // It remains tight only if we are currently tight AND we picked the max limit digit
        bool next_tight = tight && (digit == limit);

        if (leading_zeros) {
            if (digit == 0) {
                // If we place 0 while in leading_zeros, we stay in leading_zeros
                // prev stays 10 (representing 'none')
                ans += solve(idx + 1, 10, true, next_tight);
            } else {
                // We placed the first non-zero digit
                // leading_zeros becomes false
                ans += solve(idx + 1, digit, false, next_tight);
            }
        } else {
            // Standard case: cannot place the same digit as the previous one
            if (digit == prev) continue;
            
            ans += solve(idx + 1, digit, false, next_tight);
        }
    }

    return dp[idx][prev][leading_zeros][tight] = ans;
}

// Helper function to count valid numbers in [0, n]
long long count_valid(long long n) {
    if (n < 0) return 0;
    if (n == 0) return 1; // 0 is a valid number
    
    s = to_string(n);
    // Initialize DP table with -1
    memset(dp, -1, sizeof(dp));
    
    // Start recursion: 
    // index 0, prev 10 (none), leading_zeros true, tight true
    return solve(0, 10, true, true);
}

int main() {
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    long long a, b;
    if (!(cin >> a >> b)) return 0;

    // Answer is range [0, b] minus range [0, a-1]
    cout << count_valid(b) - count_valid(a - 1) << "\n";

    return 0;
}