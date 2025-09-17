#include <bits/stdc++.h>
using namespace std;

int main() {
    int t;
    cin >> t;
    while(t--) {
        int n;
        cin >> n;
        int xor_sum = 0;
        for(int i = 0; i < n; i++) {
            int x;
            cin >> x;
            xor_sum ^= (x % 4); // Grundy number for heap with {1,2,3} moves
        }
        cout << (xor_sum ? "first" : "second") << "\n";
    }
}
