#include<bits/stdc++.h>
using namespace std;
 
vector<int> tree[200001];
int lvl[200001];
int up[200001][20];
 
void binary_lifting(int src, int par)
{
    lvl[src] = lvl[par] + 1;
    up[src][0] = par;
    for(int i = 1; i < 20; i++)
    {
        if(up[src][i-1] != -1)
            up[src][i] = up[up[src][i-1]][i-1];
        else up[src][i] = -1;
    }
 
    for(int child : tree[src])
    {
        if(child != par)
            binary_lifting(child, src);
    }
}
 
int ans_query(int node, int jump_required)
{
    if(node == -1 || jump_required == 0)
        return node;
 
    for(int i = 19; i >= 0; i--){
        if(jump_required >= (1<<i)){
            return ans_query(up[node][i], jump_required - (1<<i));
        }
    }
}

int lca(int u,int v){
    if(lvl[u]<lvl[v]){
        swap(u,v);
    }
    int diff = lvl[u] - lvl[v];
    for(int i = 0;i<20;i++){
        if((1<<i)&diff){
            u = up[u][i];
        }
    }
    if(u==v) return u;
    
    for(int i = 19;i>=0;i--){
        if(up[u][i]!=up[v][i]){
            u = up[u][i];
            v = up[v][i];
        }
    }
    return up[u][0];
}
int main() {
   
   int t,n,x,node,k,q;
   //cin >> t;
   t = 1;
   while(t--)
   {
        cin >> n >> q;
        for(int i = 2;i<=n;i++)
        {
            cin >> x;
            tree[x].push_back(i);
            tree[i].push_back(x);
        }
        binary_lifting(1, -1);
        while(q--){
            int a, b;
            cin >> a >> b;
            cout << lca(a, b) << '\n';
        }
   }
   return 0;
}