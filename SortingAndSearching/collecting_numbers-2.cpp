#include <bits/stdc++.h>
using namespace std;
int count_round(int x,vector<int>& pos,int n){
    if(x<1||x>=n) return 0;

    return pos[x]>pos[x+1]?1:0;
}
int main() {
    int n,q;
    cin >> n>>q;
    vector<int> num(n+1);
    vector<int> pos(n+1);
    for (int i = 1; i <= n; ++i) {
        cin>>num[i];
        pos[num[i]]=i;
    }

    long long total_round = 1;
    for (int i = 1; i < n; i++) {
        if(pos[i]>pos[i+1])total_round++;
    }
    while(q--){
        int l,r;
        cin>>l>>r;
        int val_a = num[l];
        int val_b = num[r];
        // store all values whose neighbors might be affected
        set<int> affected;
        for(int d = -1;d<=1;d++){
            if(1<=val_a+d&&val_a+d<=n) affected.insert(val_a+d);
            if(1<=val_b+d&&val_b+d<=n) affected.insert(val_b+d);
        }
        for(int x:affected) {
            total_round = total_round - count_round(x,pos,n);
        }
        swap(num[l],num[r]);
        pos[val_a] = r;
        pos[val_b] = l;
        for(int x:affected) {
            total_round = total_round + count_round(x,pos,n);
        }
        cout<<total_round<<endl;
    }
    return 0;
}
