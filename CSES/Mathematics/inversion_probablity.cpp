#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> r(n);
    for(int i=0;i<n;i++) cin >> r[i];

    double expected = 0.0;
    for(int a=0;a<n;a++){
        for(int b=a+1;b<n;b++){
            int ra = r[a], rb = r[b];
            double cnt = 0.0;
            for(int i=1;i<=ra;i++){
                cnt += min(i-1, rb);
            }
            expected += cnt / (ra * rb);
        }
    }

    cout << fixed << setprecision(6) << expected << "\n";
}
