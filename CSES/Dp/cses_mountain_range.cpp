#include <iostream>
#include <vector>
#include <algorithm> // For std::lower_bound

int main() {
    // Optimize C++ I/O streams for speed
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int n;
    std::cin >> n;

    // This vector will store the smallest ending element for
    // increasing subsequences of a given length.
    // We use long long because the heights can be large.
    std::vector<long long> tails;

    for (int i = 0; i < n; ++i) {
        long long h;
        std::cin >> h;
        
        // Negate the height to turn LDS into LIS
        long long x = -h;

        // Find the first element in tails that is >= x
        // (i.e., not less than x)
        auto it = std::lower_bound(tails.begin(), tails.end(), x);

        if (it == tails.end()) {
            // x is larger than all current "tails".
            // This means we found a new, longer subsequence.
            tails.push_back(x);
        } else {
            // We found an existing subsequence of some length
            // that can now end with a smaller number (x).
            // This gives us a better "platform" for future elements.
            *it = x;
        }
    }

    // The size of the tails vector is the length of the
    // Longest Increasing Subsequence (of the negated numbers).
    std::cout << tails.size() << "\n";

    return 0;
}