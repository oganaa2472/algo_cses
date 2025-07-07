#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
    int n;
    cin>>n;
    vector<int> nums(n);
    for(int i = 0;i<n;i++ )cin>>nums[i];
    sort(nums.begin(),nums.end());
    int c = 0;
    int prev = -1;
    for(int i = 0;i<n;i++){
        if(prev==-1){
            prev= nums[i];
            c++;
        }else if(prev!=nums[i]){
            c++;
            prev= nums[i];
        }
    }
    cout<<c;
    
}
