#include <iostream>
#include <stack>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> x(n);
    for (int i = 0; i < n; ++i)
        cin >> x[i];
    stack<pair<int, int>> st;
    vector<int> result(n);
    for (int i = 0; i < n; ++i) {
      
        while (!st.empty() && st.top().first >= x[i]) {
            st.pop();
        }

        if (st.empty()) {
            result[i] = 0;
        } else {
            result[i] = st.top().second;
        }

        st.push({x[i], i + 1});
    }

    for (int i = 0; i < n; ++i)
        cout << result[i] << " ";
    cout << "\n";

    return 0;
}
