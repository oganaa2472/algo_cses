#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        int nim_sum = 0;
        for(int i = 0; i < n; i++) {
            int x;
            cin >> x;
            nim_sum ^= x;
        }
        cout << (nim_sum ? "first" : "second") << "\n";
    }
}
