#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin>>n;
    vector<array<int,3>> ranges(n);
    for(int i = 0;i<n;i++){
        int x,y;
        cin>>x>>y;
        ranges[i] = {x,y,i};
    }
    
    sort(ranges.begin(), ranges.end(), [](auto &a, auto &b) {
        if (a[0] != b[0]) return a[0] < b[0];
        return a[1] > b[1];
    });
    vector<int> contains(n), contained(n);
    int maxEnd = -1;
    for(auto &[x,y,i]:ranges){
        if(y<=maxEnd)
            contained[i] = 1;
        maxEnd = max(maxEnd,y);
    }
    int minEnd = INT_MAX;
    for(int j = n-1;j>=0;j--){
        auto [x,y,i] = ranges[j];
        if(y>=minEnd) contains[i] = 1;
        minEnd = min(minEnd,y);
    }
  
    for (int i = 0; i < n; ++i) cout << contains[i] << " ";
    cout<<endl;
    for (int i = 0; i < n; ++i) cout << contained[i] << " ";
    cout<<endl;
   
}
