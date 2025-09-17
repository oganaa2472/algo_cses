#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    double expected = 0.0;
    for(int m = 1; m <= k; m++) {
        double prob = pow((double)m / k, n) - pow((double)(m-1) / k, n);
        expected += m * prob;
    }

    cout << fixed << setprecision(6) << expected << "\n";
}
