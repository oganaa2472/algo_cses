#include <bits/stdc++.h>
using namespace std;
const int MAX_N = 1e6;
// max_div[i] contains the largest prime that goes into i
int max_div[MAX_N + 1];
void sieve(){
        for (int i = 2; i*i <= MAX_N; i++) {
    		if (max_div[i] == 0) {
    			for (int j = i; j <= MAX_N; j += i) { max_div[j] = i; }
    		}
    	}
    }
void solve(){
    int n;
    cin>>n;
    
   int div_num = 1;
	while (n != 1) {
		/*
		 * get the largest prime that can divide x and see
		 * how many times it goes into x (stored in count)
		 */
		int prime = max_div[n];
		int count = 0;
		while (n % prime == 0) {
			count++;
			n /= prime;
		}
		div_num *= count + 1;
	}
	cout << div_num << '\n';
    
}
int main() {
	// your code goes here
    int t ;
    cin>>t;
    sieve();
    while(t--) solve();
    
}
