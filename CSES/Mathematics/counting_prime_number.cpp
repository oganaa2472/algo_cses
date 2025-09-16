#include <bits/stdc++.h>
using namespace std;

const int MAX = 1e6 + 5;

int mu[MAX];
bool is_prime[MAX];
int freq[MAX];
int f[MAX];

void mobius_sieve() {
    for (int i = 1; i < MAX; i++) mu[i] = 1;
    for (int i = 2; i < MAX; i++) {
        if (!is_prime[i]) {
            for (int j = i; j < MAX; j += i) {
                mu[j] *= -1;
            }
            long long sq = 1LL * i * i;
            for (long long j = sq; j < MAX; j += sq) {
                mu[j] = 0;
            }
            for (int j = i; j < MAX; j += i) is_prime[j] = true;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    int max_a = 0;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        freq[a[i]]++;
        max_a = max(max_a, a[i]);
    }

    mobius_sieve();

    // Count multiples
    for (int d = 1; d <= max_a; d++) {
        f[d] = 0;
        for (int mult = d; mult <= max_a; mult += d)
            f[d] += freq[mult];
    }

    long long ans = 0;
    for (int d = 1; d <= max_a; d++) {
        if (f[d] >= 2)
            ans += 1LL * mu[d] * f[d] * (f[d] - 1) / 2;
    }

    cout << ans << "\n";
}
