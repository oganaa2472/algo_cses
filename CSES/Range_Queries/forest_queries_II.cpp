#include <iostream>
#include <vector>

using namespace std;

/**
 * PROBLEM: Forest Queries II (CSES)
 * Technique: 2D Fenwick Tree (Binary Indexed Tree)
 * Time Complexity: Update O(log N * log N), Query O(log N * log N)
 * Space Complexity: O(N^2)
 */

const int MAXN = 1005;
int bit[MAXN][MAXN];
int grid[MAXN][MAXN];
int n, q;

// 2D BIT шинэчлэх функц
void update(int y, int x, int val) {
    for (int i = y; i <= n; i += i & -i) {
        for (int j = x; j <= n; j += j & -j) {
            bit[i][j] += val;
        }
    }
}

// (1, 1)-ээс (y, x) хүртэлх нийлбэрийг олох
int query(int y, int x) {
    int sum = 0;
    for (int i = y; i > 0; i -= i & -i) {
        for (int j = x; j > 0; j -= j & -j) {
            sum += bit[i][j];
        }
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    cin >> n >> q;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            char c;
            cin >> c;
            if (c == '*') {
                grid[i][j] = 1;
                update(i, j, 1);
            } else {
                grid[i][j] = 0;
            }
        }
    }

    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int y, x;
            cin >> y >> x;
            // Төлөвийг солих: мод байвал устгана, байхгүй бол нэмнэ
            if (grid[y][x] == 1) {
                update(y, x, -1);
                grid[y][x] = 0;
            } else {
                update(y, x, 1);
                grid[y][x] = 1;
            }
        } else {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;
            // Inclusion-Exclusion томьёо ашиглан нийлбэрийг олох
            int result = query(y2, x2) 
                       - query(y1 - 1, x2) 
                       - query(y2, x1 - 1) 
                       + query(y1 - 1, x1 - 1);
            cout << result << "\n";
        }
    }

    return 0;
}