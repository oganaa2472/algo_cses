#include <iostream>
#include <vector>
#include <string>
#include <set> // Using std::set for current_frontier to handle unique cells efficiently
#include <algorithm> // For std::min
#include <utility> // For std::pair
#include <unordered_set> 
#include<bits/stdc++.h>
using namespace std;
int main() {
    // Optimize C++ standard streams for faster input/output
    // This is crucial for large inputs like N=3000.
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n; // Read the size of the grid (up to 3000)

    // Declare a 2D vector to store the grid characters
    std::vector<std::vector<char>> grid(n, std::vector<char>(n));
    std::unordered_set<char> st;
    // Read the grid characters
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> grid[i][j];
            st.insert(grid[i][j]);
        }
    }
    if(st.size()==1){
        for(int i = 0;i<n*2-1;i++){
            cout<<*st.begin();
        }
        return 0;
    }
    std::string result_string = ""; // This will store the final lexicographically minimal path

    // current_frontier stores (row, col) pairs of cells that are part of
    // the lexicographically minimal paths up to the current length.
    // std::set is used to automatically handle duplicates and allows
    // efficient lookups/insertions for `next_frontier`.
    // The maximum size of the frontier is N (when r + c = n - 1).
    std::set<std::pair<int, int>> current_frontier;

    // Base case: Start at (0,0)
    // The first character of the minimal path is always the character at (0,0).
    result_string += grid[0][0];
    current_frontier.insert({0, 0});

    // The total path length from (0,0) to (n-1, n-1) is (n-1) right moves + (n-1) down moves + 1 starting cell
    // = 2 * n - 1 characters.
    // We have already added the first character (at index 0).
    // The loop iterates to determine the characters at indices 1 through 2*n - 2.
    // The loop variable 'k' represents the current character's 0-indexed position in the result string.
    for (int k = 1; k < 2 * n - 1; ++k) {
        // In this phase, we find the minimum possible character that can appear
        // at the current position 'k' in any lexicographically minimal path.
        char min_char_for_this_len = 'Z' + 1; // Initialize with a character greater than 'Z'

        // Iterate through all cells that were part of the minimal paths up to length k-1.
        // These are the cells in `current_frontier`.
        for (const auto& cell : current_frontier) {
            int r = cell.first;
            int c = cell.second;

            // Check the cell reachable by moving Right
            if (c + 1 < n) {
                // Update the minimum character found so far for this position
                min_char_for_this_len = std::min(min_char_for_this_len, grid[r][c+1]);
            }
            // Check the cell reachable by moving Down
            if (r + 1 < n) {
                // Update the minimum character found so far for this position
                min_char_for_this_len = std::min(min_char_for_this_len, grid[r+1][c]);
            }
        }

        // The character at position 'k' in the lexicographically minimal string is
        // the minimum character we just found. Append it to the result.
        result_string += min_char_for_this_len;

        // Phase 2: Update the `current_frontier` for the next iteration (path length k+1).
        // These are the cells that are reachable from the previous frontier cells
        // by moving to a cell containing the `min_char_for_this_len`.
        std::set<std::pair<int, int>> next_frontier;

        // Iterate through the cells from the previous frontier again.
        for (const auto& cell : current_frontier) {
            int r = cell.first;
            int c = cell.second;

            // Check the cell reachable by moving Right
            if (c + 1 < n) {
                // If moving right leads to a cell with the minimum character for this level,
                // this cell is part of the new frontier.
                if (grid[r][c+1] == min_char_for_this_len) {
                    next_frontier.insert({r, c+1});
                }
            }
            // Check the cell reachable by moving Down
            if (r + 1 < n) {
                // If moving down leads to a cell with the minimum character for this level,
                // this cell is part of the new frontier.
                if (grid[r+1][c] == min_char_for_this_len) {
                    next_frontier.insert({r+1, c});
                }
            }
        }
        // The set of optimal cells for the next path length becomes the new current_frontier.
        current_frontier = next_frontier;

        // If at any point the frontier becomes empty, it means there's no way to extend
        // any optimal path with the required minimum character. For a grid with only
        // right/down moves and n >= 1, this shouldn't happen before reaching (n-1, n-1).
        // This check is mostly for robustness.
        if (current_frontier.empty()) {
            break;
        }

        // Optimization for all 'A's case or similar: If the bottom-right cell is reached
        // and is the only cell in the frontier, we can potentially stop early.
        // This is a minor optimization and not strictly necessary for correctness
        // as the loop will finish naturally.
        if (current_frontier.size() == 1 && current_frontier.count({n-1, n-1})) {
             // The bottom-right cell is the only cell in the frontier, and we've reached it.
             // The remaining characters must be the ones on the path from the last frontier
             // cell to (n-1, n-1). However, the loop structure already handles this
             // by correctly determining the min_char and advancing the frontier until (n-1, n-1)
             // is the only cell and the loop finishes.
        }
    }

    // Print the final lexicographically minimal string
    std::cout << result_string << std::endl;

    return 0;
}
