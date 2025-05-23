#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <utility> // For std::pair

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Number of mountains

    std::vector<int> h(n); // Heights of mountains
    std::vector<std::pair<int, int>> sorted_mountains(n); // Pair: {height, original_index}
    for (int i = 0; i < n; ++i) {
        std::cin >> h[i];
        sorted_mountains[i] = {h[i], i};
    }

    // Sort mountains by height in descending order
    std::sort(sorted_mountains.rbegin(), sorted_mountains.rend());

    // prev_greater[i]: index of the first mountain to the left of i with height > h[i]
    // next_greater[i]: index of the first mountain to the right of i with height > h[i]
    std::vector<int> prev_greater(n, -1);
    std::vector<int> next_greater(n, -1);

    // Compute prev_greater using a monotonic stack (decreasing heights)
    std::stack<int> s;
    for (int i = 0; i < n; ++i) {
        while (!s.empty() && h[s.top()] <= h[i]) {
            s.pop();
        }
        if (!s.empty()) {
            prev_greater[i] = s.top();
        }
        s.push(i);
    }

    // Clear the stack for the next computation
    while (!s.empty()) {
        s.pop();
    }

    // Compute next_greater using a monotonic stack (decreasing heights) from right to left
    for (int i = n - 1; i >= 0; --i) {
        while (!s.empty() && h[s.top()] <= h[i]) {
            s.pop();
        }
        if (!s.empty()) {
            next_greater[i] = s.top();
        }
        s.push(i);
    }

    // dp[i]: maximum number of mountains visited ending at mountain i
    std::vector<int> dp(n, 1);
    int max_mountains = 0;

    // Iterate through mountains in decreasing order of height
    for (const auto& mountain : sorted_mountains) {
        int current_height = mountain.first;
        int original_index = mountain.second;

        // If there is a taller mountain to the left that can glide to current
        if (prev_greater[original_index] != -1) {
            int p = prev_greater[original_index];
            // Since we process by decreasing height, dp[p] is already computed
            dp[original_index] = std::max(dp[original_index], dp[p] + 1);
        }

        // If there is a taller mountain to the right that can glide to current
        if (next_greater[original_index] != -1) {
            int n_idx = next_greater[original_index];
            // Since we process by decreasing height, dp[n_idx] is already computed
            dp[original_index] = std::max(dp[original_index], dp[n_idx] + 1);
        }

        // Update the overall maximum number of mountains
        max_mountains = std::max(max_mountains, dp[original_index]);
    }

    // If n is 1, the loop for max_mountains might not execute if initialized to 0.
    // The minimum answer is 1 (visiting the starting mountain).
    if (n > 0) {
         std::cout << max_mountains << std::endl;
    } else {
         std::cout << 0 << std::endl; // Should not happen based on constraints (1 <= n)
    }


    return 0;
}
