
#include <bits/stdc++.h>
using namespace std;

string minimal_rotation(const string &s) {
    int n = s.size();
    string t = s + s;
    int f[2*n]; // failure function
    fill(f, f+2*n, -1);
    int k = 0; // start of minimal rotation

    for(int j = 1; j < 2*n; j++){
        int i = f[j - k - 1];
        while(i != -1 && t[j] != t[k + i + 1])
            i = f[i];
        if(i == -1 && t[j] != t[k])
            k = j;
        else
            f[j - k] = i + 1;
    }
    return t.substr(k, n);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    cout << minimal_rotation(s) << "\n";
}
