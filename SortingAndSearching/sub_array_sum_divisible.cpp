#include <bits/stdc++.h>
 
using namespace std;
#define ll long long
int main() {
    ll n;
    cin>>n;
    vector<ll>v(n);
    for(int i=0;i<n;++i)
        cin>>v[i];
    ll sum=0,cnt=0;
    map<ll,ll>mp;
    mp[0] = 1;
    for(int i=0;i<n;++i)
    {
    	sum+=v[i];
    	int mod = ((sum % n) + n) % n; 
    	cnt+=mp[mod];
    	
		mp[mod]++;
	}
	cout<<cnt<<endl;
}