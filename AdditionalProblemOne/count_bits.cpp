#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	long long n;
	cin>>n;
	n++;
	long long cnt = 0;
	for(long long i = 2; i/2<n; i=i*2){
	    long long k = n / i;
	    cnt+=k * i/2;
	    
	    long long remainder = n%i;
	    if(remainder>i/2){
	        cnt+=remainder-i/2 ;
	    }
	}
	cout<<cnt<<endl;

}
