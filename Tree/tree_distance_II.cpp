#include <bits/stdc++.h>
using namespace std;

const int N = 2e5+5;
vector<int> tree[N];
long long dp[N], ans[N];
int subtree_size[N];  // Энэ int байж болно, учир нь хамгийн ихдээ n хүртэл тоолно
int n;

void dfs1(int node, int parent) {
    subtree_size[node] = 1;
    for (int child : tree[node]) {
        if (child == parent) continue;
        dfs1(child, node);
        subtree_size[node] += subtree_size[child];
        dp[node] += dp[child] + subtree_size[child];
    }
}

void dfs2(int node, int parent) {
    for (int child : tree[node]) {
        if (child == parent) continue;
        ans[child] = ans[node] - subtree_size[child] + (n - subtree_size[child]);
        dfs2(child, node);
    }
}

int main() {
    cin >> n;
    for (int i = 0; i < n-1; i++) {
        int a, b;
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    dfs1(1, 0);
    ans[1] = dp[1];
    dfs2(1, 0);

    for (int i = 1; i <= n; i++) {
        cout << ans[i] << " ";
    }
    cout << "\n";
}
