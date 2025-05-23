#include <bits/stdc++.h>
#define ll long long
using namespace std;



class DisjointSet {
    
    
public:
    vector<ll> rank, parent, size;
    DisjointSet(ll n) {
        rank.resize(n + 1, 0);
        parent.resize(n + 1);
        size.resize(n + 1);
        for (ll i = 0; i <= n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }

    ll findUPar(ll node) {
        if (node == parent[node])
            return node;
        return parent[node] = findUPar(parent[node]);
    }

    void unionByRank(ll u, ll v) {
        ll ulp_u = findUPar(u);
        ll ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (rank[ulp_u] < rank[ulp_v]) {
            parent[ulp_u] = ulp_v;
        }
        else if (rank[ulp_v] < rank[ulp_u]) {
            parent[ulp_v] = ulp_u;
        }
        else {
            parent[ulp_v] = ulp_u;
            rank[ulp_u]++;
        }
    }

    void unionBySize(ll u, ll v) {
        ll ulp_u = findUPar(u);
        ll ulp_v = findUPar(v);
        if (ulp_u == ulp_v) return;
        if (size[ulp_u] < size[ulp_v]) {
            parent[ulp_u] = ulp_v;
            size[ulp_v] += size[ulp_u];
        }
        else {
            parent[ulp_v] = ulp_u;
            size[ulp_u] += size[ulp_v];
        }
    }
};
ll kruskals(ll g_nodes, vector<pair<ll, pair<ll, ll>>>& edges) {
     
    
       sort(edges.begin(),edges.end());
       DisjointSet ds(g_nodes);
       
        sort(edges.begin(),edges.end());
        ll mstWt = 0;
        ll count = 0;
        bool isConnected = true;
        for (auto it : edges) {
            ll wt = it.first;
            ll u = it.second.first;
            ll v = it.second.second;

            if (ds.findUPar(u) != ds.findUPar(v)) {
                mstWt += wt;
                count++;
                ds.unionByRank(u, v);
            }
        }
       if(count == g_nodes-1){
         return mstWt;
       }else{
           return -1;
       }
       
       
}

int main()
{
    ll n,m;
    cin>>n>>m;


    vector<pair<ll, pair<ll, ll>>> edges;

    for (int i = 0; i < m; i++) {

        ll a,b,c;
        cin>>a>>b>>c;
        edges.push_back({c,{a,b}});
    }

    ll res = kruskals(n, edges);
    if(res==-1) cout<<"IMPOSSIBLE";
    else cout<<res<<endl;
    
    return 0;
}
  

