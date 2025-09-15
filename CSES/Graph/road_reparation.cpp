
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, size;
    int components;
    int largest;

    DSU(int n) {
        parent.resize(n + 1);
        size.assign(n + 1, 1);
        for (int i = 1; i <= n; i++) parent[i] = i;
        components = n;
        largest = 1;
    }

    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]); // path compression
    }

    bool unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return false; // already in same set

        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
      
        return true;
    }
};

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>> edges;
    for(int i = 0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        edges.push_back({c,a,b});
    }
    int count = 0;
    sort(edges.begin(),edges.end());
    DSU dsu(n);
    long long ans = 0;
    for(auto &edge : edges){
        int a = edge[1];
        int b = edge[2];
        int c = edge[0];
        if(dsu.unite(a,b)){
            ans += c;
            count++;
        }
    }
    if(count == n-1){
        cout<<ans<<endl;
      }else{
          cout<<"IMPOSSIBLE"<<endl;
      }
      
}