#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

typedef tree<
    int,
    null_type,
    less<int>,
    rb_tree_tag,
    tree_order_statistics_node_update> ordered_set;


int main() {
	// your code goes here
	int n,k;
    
    cin>>n>>k;
    ordered_set set;
    for(int i = 1;i<=n;i++){
        set.insert(i);
    }
    int cur = 0;
    vector<int> result;
    while(!set.empty()){
        cur = (cur+k)%set.size();
        auto it = set.find_by_order(cur);
        result.push_back(*it);
        set.erase(it);
    }
    for(int x:result) cout<<x<<" ";
    
 
}