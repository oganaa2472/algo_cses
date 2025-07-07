#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> pos(n,0);
    for (int i = 0; i < n; ++i) {
        int num;
        cin>>num;
        pos[--num]=i;
    }

    long long total_round = 1;
    for (int i = 0; i < n-1; i++) {
        if(pos[i]>pos[i+1])total_round++;
    }

    cout << total_round << "\n";
    return 0;
}
