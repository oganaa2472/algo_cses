#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, x;
    cin >> n >> x;
    vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        cin >> p[i];
    }
    sort(p.begin(),p.end());
    int answer = 0;
    int i = 0;
    int j = n-1;
    while(i<=j){
        if(p[i]+p[j]>x){
            j--;
        }
        else{
            i++;
            j--;
            
        }
        answer++;
    }
    cout<<answer<<endl;
    return 0;
}