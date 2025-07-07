#include <bits/stdc++.h>
using namespace std;
 
int main() {
    int n;
    cin >> n;
 
    vector<pair<int, int>> movies(n);
    for (int i = 0; i < n; ++i)
        cin >> movies[i].first >> movies[i].second;
 
    sort(movies.begin(), movies.end(), [](auto &a, auto &b) {
        return a.second < b.second;
    });
    
    int last_end = 0,result = 0;
    for(auto [start,end]:movies){
        if(last_end<=start){
            result++;
            last_end = end;
        }
        
    }    
    cout<<result;
    
    return 0;
}