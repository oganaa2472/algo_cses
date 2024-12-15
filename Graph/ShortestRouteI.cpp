#include<bits/stdc++.h>
using namespace std;
const int INF = 1000000000;

int32_t main(){
      int n,m;
      cin >> n >> m;
      
    vector<vector<pair<int, int>>> neighbors(n);
	for (int i = 0; i < m; i++) {
		int a, b, c;
		cin >> a >> b >> c;
		neighbors[a - 1].push_back({b - 1, c});
	}
      
     vector<long long> dist(n, LLONG_MAX);

	// Dijkstra's algorithm
	using T = pair<long long, int>;
	priority_queue<T, vector<T>, greater<T>> pq;

	int start = 0;
	dist[start] = 0;  // The shortest path from a node to itself is 0
	pq.push({0, start});

	while (!pq.empty()) {
		const auto [cdist, node] = pq.top();
		pq.pop();
		if (cdist != dist[node]) { continue; }
		for (const pair<int, int> &i : neighbors[node]) {
			// If we can reach a neighbouring node faster,
			// we update its minimum distance
			if (cdist + i.second < dist[i.first]) {
				pq.push({dist[i.first] = cdist + i.second, i.first});
			}
		}
	}
	for(int i=0;i<n;i++)
       cout << dist[i] <<" ";

}
