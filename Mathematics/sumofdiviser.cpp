#include <iostream>
using namespace std;

#define MOD 1000000007
#define int long long

int sum_sigma(int n) {
    int res = 0;

    // 1-ээс sqrt(n) хүртэл хуваагчдын нийлбэрийг тооцоолох
    for (int i = 1; i * i <= n; i++) {
        int div1 = i, div2 = n / i;
        res = (res + div1 * (n / div1)) % MOD;
        if (div1 != div2) {
            res = (res + div2 * (n / div2)) % MOD;
        }
    }

    return res;
}

int32_t main() {
    int n;
    cin >> n;
    cout << sum_sigma(n) << endl;
    return 0;
}