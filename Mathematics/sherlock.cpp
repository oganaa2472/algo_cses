#include <bits/stdc++.h>
using namespace std;

const int MAX_N = 1e5;
bool isPrime[MAX_N + 1];

void sieve() {
    fill(isPrime, isPrime + MAX_N + 1, true); // Бүх утгыг эхэнд true болгох
    isPrime[0] = isPrime[1] = true ;

    for (int p = 2; p * p <= MAX_N; ++p) {
        if (isPrime[p]) {
            for (int i = p * p; i <= MAX_N; i += p)
                isPrime[i] = false;
        }
    }
}

string solve(vector<int> a) {
    unordered_map<int, int> mp;
    for (auto &b : a) mp[b]++;
    
    if (a.size() != mp.size()) return "NO"; // давхардсан тоо байна

    int count = 0;
    for (int i = 0; i < a.size(); i++) {
        if (isPrime[a[i]]) count++;
    }

    if (count == a.size()) return "YES"; // бүх тоо prime бол YES
    return "NO";
}

int main() {
    int t;
    cin >> t;
    sieve();

    for (int t_itr = 0; t_itr < t; t_itr++) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) cin >> a[i];

        string result = solve(a);
        cout << result << "\n";
    }

    return 0;
}
