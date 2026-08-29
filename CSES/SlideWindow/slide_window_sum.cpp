#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n, k;
    cin >> n >> k;

    long long x, a, b, c;
    cin >> x >> a >> b >> c;

    vector<long long> window(k);

    long long cur = x;
    long long sum = 0;

    // эхний window
    for (int i = 0; i < k; i++) {
        if (i > 0)
            cur = (a * cur + b) % c;

        window[i] = cur;
        sum += cur;
    }

    long long ans = sum;

    int idx = 0;

    // дараагийн window-ууд
    for (int i = k; i < n; i++) {

        cur = (a * cur + b) % c;

        sum -= window[idx];
        sum += cur;

        window[idx] = cur;

        idx = (idx + 1) % k;

        ans ^= sum;
    }

    cout << ans << '\n';
}