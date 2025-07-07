#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    long long k;
    cin >> n >> m >> k;
    vector<long long> a(n), b(m);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < m; i++) cin >> b[i];
    
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    int i = 0;
    int j = 0;
    int c = 0;
    while(i<n&&j<m){
        long long diff = abs(b[j]-a[i]);
        if(diff<=k){
           c++;
           i++;
           j++;
        }else if(b[j]-a[i]>0){
            i++;
        }else{
            j++;
        }
    }
    cout<<c<<endl;
    return 0;
}