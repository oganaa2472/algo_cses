#include <bits/stdc++.h>
using namespace std;

struct Project {
    long long start, end, reward;
};
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n;
    cin >> n;
    vector<Project> projects(n);
    for (int i = 0; i < n; ++i) {
        cin >> projects[i].start >> projects[i].end >> projects[i].reward;
    }
    sort(projects.begin(), projects.end(), [](const Project &a, const Project &b) {
        return a.end < b.end;
    });
    vector<long long> ends(n);
    for (int i = 0; i < n; ++i) ends[i] = projects[i].end;
    vector<long long> dp(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        auto &pr = projects[i - 1];
        // Find the last project that ends before pr.start
        int j = upper_bound(ends.begin(), ends.end(), pr.start - 1) - ends.begin();
        j--; // index of last non-overlapping project

        dp[i] = max(dp[i - 1], dp[j + 1] + pr.reward);
    }
    cout << dp[n] << "\n";
}