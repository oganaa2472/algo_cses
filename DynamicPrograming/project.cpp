#include <bits/stdc++.h>
using namespace std;

struct Project {
    int start, end, profit;
    bool operator<(const Project &other) const {
        return end < other.end;  // End time-аар эрэмбэлэх
    }
};

int main() {
    int n;
    cin >> n;
    vector<Project> projects(n);
    
    for (int i = 0; i < n; i++) 
        cin >> projects[i].start >> projects[i].end >> projects[i].profit;
    
    sort(projects.begin(), projects.end());  // Дуусах хугацаагаар эрэмбэлэх

    vector<long long> dp(n);
    vector<int> ends(n);
    
    for (int i = 0; i < n; i++) ends[i] = projects[i].end;

    for (int i = 0; i < n; i++) {
        int prev = lower_bound(ends.begin(), ends.end(), projects[i].start) - ends.begin();
        prev--;  // Өмнөх хамааралгүй project олох
        
        long long best_prev = (prev >= 0 ? dp[prev] : 0);
        dp[i] = max((i > 0 ? dp[i-1] : 0), best_prev + projects[i].profit);
    }
    
    cout << dp[n-1] << endl;
}
