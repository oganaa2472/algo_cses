#include <iostream>
#include <vector>
using namespace std;

const long long MOD = 1e9 + 7;

// Function to compute the number of derangements D(n)
long long derangements(int n) {
    if (n == 0) return 1;
    if (n == 1) return 0;
    if (n == 2) return 1;
    
    vector<long long> D(n + 1);
    D[0] = 1;
    D[1] = 0;
    D[2] = 1;

    for (int i = 3; i <= n; ++i) {
        D[i] = (i - 1) * (D[i - 1] + D[i - 2]) % MOD;
    }

    return D[n];
}

int main() {
    int n;
    cin >> n;

    cout << derangements(n) << endl;

    return 0;
}
