#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
	// your code goes here
    ll n,k;
    cin>>n>>k;
    vector<ll> primes(k);
    for(int i = 0;i<k;i++){
        cin>>primes[i];
    }
    ll answer = 0;
    for(int mask = 1;mask<(1<<k);mask++){
        ll lcm = 1;
        int bits = 0;
 
        for (int i = 0; i < k; ++i) {
            if (mask & (1 << i)) {
                bits++;
                // Overflow болгохоос сэргийлэх
                if (lcm > n / primes[i]) {
                    lcm = n + 1; // too large
                    break;
                }
                lcm *= primes[i];
            }
        }
 
        if (lcm > n) continue;
 
        ll count = n / lcm;
        if (bits % 2 == 1) {
            answer += count; // odd size subset → add
        } else {
            answer -= count; // even size subset → subtract
        }

        
    }
    cout<<answer;
}
