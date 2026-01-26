#include <bits/stdc++.h>
using namespace std;
#define ll long long
int main() {
	// your code goes here
	int n;
    
    cin>>n;
    vector<ll> nums(n);
    for (int i = 0; i < n; ++i) {
        cin>>nums[i];
    }
    ll left = 0;
    ll right = 0;
    ll answer = 0;
    set<ll> sets;
    while(right<n){
        while(sets.count(nums[right])>0){
             sets.erase(nums[left]);
             left++;
        }
        // cout<<right<<" "<<left<<" "<<endl;
        // cout<<(right-left+1)<<endl;
        answer = answer+(right-left+1);
        sets.insert(nums[right]);
        right++;
    }
    cout<<answer<<endl;
    
 
}