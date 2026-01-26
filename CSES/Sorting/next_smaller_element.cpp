#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    // Стек нь {утга, индекс} хосыг хадгална
    stack<pair<int, int>> st;

    for (int i = 1; i <= n; i++) {
        int val;
        cin >> val;

        // Стекийн оройд байгаа тоо одоогийн тооноос их буюу тэнцүү байвал
        // тэр тоо хэзээ ч "хамгийн ойр бага тоо" болж чадахгүй тул хасна.
        while (!st.empty() && st.top().first >= val) {
            st.pop();
        }

        // Хэрэв стек хоосон бол зүүн талд бага тоо байхгүй
        if (st.empty()) {
            cout << 0 << " ";
        } else {
            // Стек хоосон биш бол оройд байгаа нь хариулт мөн
            cout << st.top().second << " ";
        }

        // Одоогийн тоог стект нэмнэ (дараагийн тоонуудад хэрэг болж магадгүй)
        st.push({val, i});
    }

    return 0;
}