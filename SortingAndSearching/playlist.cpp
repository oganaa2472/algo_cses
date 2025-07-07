#include <bits/stdc++.h>

using namespace std;
#define ll long long
int main() {
    ll n;
    cin>>n;
    vector<int> songs(n);
    for(int i =0;i<n;i++) cin>>songs[i];
    unordered_set<int> seen;
    int left = 0;
    int right = 0;
    int maxLen = 0;
    while(right<n){
        if(seen.count(songs[right])==0){
            seen.insert(songs[right]);
            maxLen = maxLen(right-left+1,maxLen);
            right++;
        }else{
            seen.erase(songs[left]);
            left++;
        }
        
    }
	cout<<maxLen<<endl;
}
