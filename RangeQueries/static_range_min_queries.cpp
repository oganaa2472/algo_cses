#include <bits/stdc++.h>
using namespace std;
struct segtree{
    int size;
    vector<long long> sums;
    void init(int n){
        size = 1;
        while(size<n) size*=2;
        sums.assign(2*size,INT_MAX);
    }
    void set(int i,int v,int x, int lx,int rx){
        if(rx-lx==1){
            sums[x] = v;
            return;
        }
        int m = (lx+rx) / 2;
        if(i<m){
            set(i,v,2*x+1,lx,m);
        }else{
             set(i,v,2*x+2,m,rx);
        }
        sums[x] = min(sums[2*x+1],sums[2*x+2]);
        
    }
    void set(int i,int v){
        set(i,v,0,0,size);
    }
    long long sum(int l,int r,int x,int lx,int rx){
        if(lx>=r||rx<=l) return INT_MAX;
        if(lx>=l&&rx<=r){
            return sums[x];
        }
        int m = (lx+rx) / 2;
        long long s1 = sum(l,r,2*x+1,lx,m);
        long long s2 = sum(l,r,2*x+2,m,rx);
        return min(s1,s2);
    }
    long long sum(int l,int r){
        return sum(l,r,0,0,size);
    }
    void build(vector<int>& a,int x,int lx,int rx){
        if(rx-lx==1){
            if(lx<(int)a.size()){
                sums[x] = a[lx];
            }
            return;
        }
        int m = (lx+rx)/2;
        build(a,2*x+1,lx,m);
        build(a,2*x+2,m,rx);
        sums[x] = min(sums[2*x+1],sums[2*x+2]);
    }
    void build(vector<int>& a){
        build(a,0,0,size);
    }
};
int main() {
	// your code goes here
    int n,m;
    cin>>n>>m;
    segtree st;
    st.init(n);
    vector<int> a(n);
    for(int i = 0;i<n;i++){
        cin>>a[i];
    }
    st.build(a);
    while(m--){
        int l,r;
        cin>>l>>r;
        l=l-1;
        // r = r-1;
        cout<<st.sum(l,r)<<endl;
    }
    
}
