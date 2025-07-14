#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
    int n ;
    cin>>n;
    deque<int> dq;
    vector<int> remove_order;
    for(int i = 1;i<=n;i++) dq.push_back(i);
    while(!dq.empty()){
        dq.push_back(dq.front());
        dq.pop_front();
        remove_order.push_back(dq.front());
        dq.pop_front();
    }
    for(int i = 0;i<n;i++){
        cout<<remove_order[i]<<" ";
    }
}
