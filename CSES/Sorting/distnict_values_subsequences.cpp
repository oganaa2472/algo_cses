#include <iostream>
#include <vector>
#include <map>

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    map<int, int> counts;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        counts[x]++;
    }

    long long ans = 1;
    long long MOD = 1e9 + 7;

    // Бүх ялгаатай тоо бүрийн хувьд (тооны давтамж + 1)-ээр үржүүлнэ
    for (auto const& [key, val] : counts) {
        ans = (ans * (val + 1)) % MOD;
    }

    // Хоосон дарааллыг хасна
    ans = (ans - 1 + MOD) % MOD;

    cout << ans << endl;

    return 0;
}