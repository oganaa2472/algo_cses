#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    int MAX = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        MAX = max(MAX, a[i]);
    }

    vector<int> freq(MAX + 1, 0);
    for (int x : a) freq[x]++;

    for (int g = MAX; g >= 1; g--) {
        int count = 0;
        for (int multiple = g; multiple <= MAX; multiple += g) {
            count += freq[multiple];
            if (count >= 2) break;
        }
        if (count >= 2) {
            cout << g << "\n";
            return 0;
        }
    }
}
