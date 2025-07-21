#include <bits/stdc++.h>
 
using namespace std;
#define ll long long
int main() {
     int n;
    cin >> n;
    vector<long long> books(n);
    
    long long total = 0;
    long long max_time = 0;

    for (int i = 0; i < n; ++i) {
        cin >> books[i];
        total += books[i];
        max_time = max(max_time, books[i]);
    }

    // The answer is the max between total time and 2 * max book time
    cout << max(total, 2 * max_time) << endl;
}