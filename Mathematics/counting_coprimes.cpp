#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int maxVal = 1e6+5;
int main() {
	// your code goes here
    int n ;
    cin>>n;
    vector<int> values(n);
    for(int i =0;i<n;i++) cin>>values[i];
    vector<int> sieve(maxVal);
    vector<vector<int>> divisor(maxVal);
    for(int i = 2;i<maxVal;i++){
        if(divisor[i].size()==0) // primes
        {
            divisor[i].push_back(i);
            for(int j = i*2;j<maxVal;j=j+i){
                divisor[j].push_back(i);
            }
        }
    }
    vector<int> valuesDivisibleBy(maxVal);
    vector<int> primeDivisibleOf(maxVal);
    for(int i =0;i<n;i++){
        for(int mask = 1;mask<(1<<divisor[values[i]].size());mask++){
            int combination = 1;
            int primeDivisor = 0;
            for(int j = 0;j<divisor[values[i]].size();j++){
                if(mask&(1<<j)){
                    combination *= divisor[values[i]][j];
                    primeDivisor++;
                }
            }
            valuesDivisibleBy[combination]++;
            primeDivisibleOf[combination] = primeDivisor;
        }
    }
    long long tot = ((ll)n* ((ll)n-1) )/2;
    long long count = 0;
    for(int i = 0;i<maxVal;i++){
        if(primeDivisibleOf[i]%2){
            ll k = valuesDivisibleBy[i];
            count+=(k*(k-1))/2;
        }else{
             ll k = valuesDivisibleBy[i];
            count-=(k*(k-1))/2;
        }
    }
    cout<<tot-count;
}
