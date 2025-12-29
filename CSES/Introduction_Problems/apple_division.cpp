#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;

ll n;
vector<ll> weights;

// Рекурсив функц: одоогийн индекс, 1-р ба 2-р группийн нийлбэрүүд
ll find_min_diff(int idx, ll sum1, ll sum2) {
    // Хэрэв бүх алимыг хувааж дууссан бол зөрүүг буцаана
    if (idx == n) {
        return abs(sum1 - sum2);
    }

    // Одоогийн алимыг 1-р группт хийх хувилбар
    ll option1 = find_min_diff(idx + 1, sum1 + weights[idx], sum2);
    
    // Одоогийн алимыг 2-р группт хийх хувилбар
    ll option2 = find_min_diff(idx + 1, sum1, sum2 + weights[idx]);

    // Хоёр хувилбарын хамгийн бага зөрүүг буцаана
    return min(option1, option2);
}

int main() {
    cin >> n;
    weights.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> weights[i];
    }

    // 0-р индексээс, хоёр группийн нийлбэр 0 байхаас эхэлнэ
    cout << find_min_diff(0, 0, 0) << endl;

    return 0;
}