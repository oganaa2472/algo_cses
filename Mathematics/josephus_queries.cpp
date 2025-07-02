#include <bits/stdc++.h>
using namespace std;
long long solve(long long n, long long k) {
    if (n == 1) return 1;

    if (k <= (n+1)/2) {
        if (2*k > n) return 2*k%n;
        else return 2*k;
    }
    long long temp = solve(n / 2, k - (n + 1) / 2);
    if (n % 2 == 1) return 2 * temp + 1;
    return 2 * temp - 1;
}

int main() {
	// your code goes here
	long long n;
	cin>>n;
	while(n--){
	   int a,k;
	   cin>>a>>k;
	   cout<<solve(a,k)<<endl;
	}
   
}
