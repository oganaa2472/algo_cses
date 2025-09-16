#include <bits/stdc++.h>
using namespace std;

int count_divisors(int x) {
    int count = 0;
    for (int i = 1; i * i <= x; i++) {
        if (x % i == 0) {
            if (i * i == x) count += 1;  // perfect square
            else count += 2;             // pair of divisors
        }
    }
    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    while (n--) {
        int x;
        cin >> x;
        cout << count_divisors(x) << "\n";
    }
}
