#include <algorithm>

#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    multiset<int> tickets;
    for (int i = 0; i < n; ++i) {
        int price;
        cin >> price;
        tickets.insert(price);
    }
    for (int i = 0; i < m; ++i) {
        int max_price;
        cin >> max_price;

        auto it = tickets.upper_bound(max_price);
        if (it != tickets.begin()) {
            --it;
            cout << *it << "\n";
            tickets.erase(it);
        } else {
            cout << -1 << "\n";
        }
    }

    return 0;
}
