#include <iostream>
#include <vector>

int main() {
    // Fast I/O
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n, q;
    std::cin >> n >> q;

    // Use a 2D vector for the prefix sum array.
    // It's convenient to use (n+1) x (n+1) to handle 1-based indexing from the problem.
    // All values are initialized to 0.
    std::vector<std::vector<int>> prefix_sum(n + 1, std::vector<int>(n + 1, 0));

    // Pre-computation step
    for (int y = 1; y <= n; ++y) {
        std::string row;
        std::cin >> row;
        for (int x = 1; x <= n; ++x) {
            // Count a tree if the character is '*'
            int is_tree = (row[x - 1] == '*');

            // Apply the 2D prefix sum formula
            prefix_sum[y][x] = is_tree + prefix_sum[y - 1][x] + prefix_sum[y][x - 1] - prefix_sum[y - 1][x - 1];
        }
    }

    // Process queries
    for (int i = 0; i < q; ++i) {
        int y1, x1, y2, x2;
        std::cin >> y1 >> x1 >> y2 >> x2;

        // Apply the query formula
        int count = prefix_sum[y2][x2] - prefix_sum[y1 - 1][x2] - prefix_sum[y2][x1 - 1] + prefix_sum[y1 - 1][x1 - 1];
        std::cout << count << "\n";
    }

    return 0;
}