#include<bits/stdc++.h>
using namespace std;

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    int k;
    cin >> n >> k;
    vector<long long> primes(k);
    for (int i = 0; i < k; i++) cin >> primes[i];
    long long ans = 0;
    for (int mask = 1; mask < (1 << k); mask++) {
        long long prod = 1;
        int bits = __builtin_popcount(mask);
        bool overflow = false;
        for(int i = 0;i<k;i++){
            if(mask&(1<<i)){
                if(prod>n/primes[i]){
                    overflow = true;
                    break;
                }
                prod *=primes[i]; 
            }
        }
        if(overflow) continue;
        long long count = n/prod;
        if(bits%2==1) ans+=count;
        else ans = ans-=count;
    }
    cout<<ans<<endl;
}