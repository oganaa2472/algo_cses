#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Олонлогуудаас элемент хасах болон нэмэх туслах систем
multiset<long long> left_set, right_set;
long long left_sum = 0, right_sum = 0;
int k;

// Хоёр олонлогийн хэмжээг тэнцвэржүүлэх
void balance() {
    while (left_set.size() > (k + 1) / 2) {
        auto it = prev(left_set.end());
        long long val = *it;
        left_set.erase(it);
        left_sum -= val;
        
        right_set.insert(val);
        right_sum += val;
    }
    
    while (left_set.size() < (k + 1) / 2 && !right_set.empty()) {
        auto it = right_set.begin();
        long long val = *it;
        right_set.erase(it);
        right_sum -= val;
        
        left_set.insert(val);
        left_sum += val;
    }
}

// Шинэ элемент нэмэх
void add(long long val) {
    if (left_set.empty() || val <= *prev(left_set.end())) {
        left_set.insert(val);
        left_sum += val;
    } else {
        right_set.insert(val);
        right_sum += val;
    }
    balance();
}

// Хуучин элемент хасах
void remove(long long val) {
    auto it = left_set.find(val);
    if (it != left_set.end()) {
        left_set.erase(it);
        left_sum -= val;
    } else {
        it = right_set.find(val);
        right_set.erase(it);
        right_sum -= val;
    }
    balance();
}

// Хамгийн бага зардлыг тооцоолох
long long get_cost() {
    long long median = *prev(left_set.end());
    long long left_count = left_set.size();
    long long right_count = right_set.size();
    
    long long cost = (median * left_count - left_sum) + (right_sum - median * right_count);
    return cost;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n >> k)) return 0;

    vector<long long> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }

    // Эхний k элементийг оруулж цонхыг бэлдэнэ
    for (int i = 0; i < k; i++) {
        add(x[i]);
    }

    cout << get_cost();

    // Гулсах цонхыг баруун тийш шилжүүлэх
    for (int i = k; i < n; i++) {
        add(x[i]);
        remove(x[i - k]);
        cout << " " << get_cost();
    }
    cout << "\n";

    return 0;
}