#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long x;
    cin >> n >> x;

    vector<long long> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];

    int mid = n / 2;

    vector<long long> left, right;

    // Зүүн хэсгийн бүх subset sum
    for (int mask = 0; mask < (1 << mid); mask++) {
        long long sum = 0;
        for (int i = 0; i < mid; i++) {
            if (mask & (1 << i)) {
                sum += a[i];
            }
        }
        left.push_back(sum);
    }

    // Баруун хэсгийн бүх subset sum
    for (int mask = 0; mask < (1 << (n - mid)); mask++) {
        long long sum = 0;
        for (int i = 0; i < n - mid; i++) {
            if (mask & (1 << i)) {
                sum += a[mid + i];
            }
        }
        right.push_back(sum);
    }

    // Баруун хэсгийг эрэмбэлэх
    sort(right.begin(), right.end());

    long long ans = 0;

    // Хослуулах
    for (long long s : left) {
        long long need = x - s;
        ans += upper_bound(right.begin(), right.end(), need)
             - lower_bound(right.begin(), right.end(), need);
    }

    cout << ans << "\n";
    return 0;
}
