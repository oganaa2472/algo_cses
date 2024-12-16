#include<bits/stdc++.h>
using namespace std;
struct Edge {
    int a, b, cost;
};
const int INF = 1000000000;
int32_t main(){
      long long n,m;
      cin >> n >>m;
    vector<int> d(n, INF);
    d[0] = 0;
    vector<int> p(n, -1);
    vector<Edge> edges(m);
    int x;
    for (int j = 0; j < m; j++) {
            int a, b, w;
            cin>>a>>b>>w;
            a--;
            b--;
           edges[j] = {a, b, w};
    }
    for (int i = 0; i < n; ++i) {
        x = -1;
        for (Edge e : edges)
            if (d[e.a] < INF)
                if (d[e.b] > d[e.a] + e.cost) {
                    d[e.b] = max(-INF, d[e.a] + e.cost);
                    p[e.b] = e.a;
                    x = e.b;
                }
    }
  if (x == -1)
        cout <<-1;
    else
    cout<<d[n-1]<<endl;
 
}