#include <bits/stdc++.h>
using namespace std;

int main() {
	// your code goes here
	int n;
    
    cin >> n;

    int a;
    int result = 0;
    multiset<int> myset;
    for (int i = 0; i < n; ++i) {
        cin>>a;
        auto it = myset.upper_bound(a);
        if(it!=myset.end()){
            myset.erase(it);
            myset.insert(a);
        }else{
            myset.insert(a);
          
        }
        result = max(result,(int)myset.size());
    }
    cout<<result;
}
