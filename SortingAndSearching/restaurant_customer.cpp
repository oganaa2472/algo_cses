#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<pair<int, int>> events;

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        events.push_back({a, 1});  
        events.push_back({b, -1}); 
    }
    
    sort(events.begin(),events.end());
    int cur = 0;
    int result = 0;
    for(int i = 0;i<events.size();i++){
        cur += events[i].second;
        result = max(cur,result);
    }    
    cout<<result;
    
    return 0;
}