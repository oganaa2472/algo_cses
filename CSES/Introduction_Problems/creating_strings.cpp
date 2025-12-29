#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    // Оролт гаралтыг хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    string s;
    cin >> s;

    // 1. Тэмдэгтүүдийг цагаан толгойн дарааллаар эрэмбэлэх
    sort(s.begin(), s.end());

    vector<string> results;

    // 2. Бүх ялгаатай сэлгэмэлүүдийг үүсгэх
    do {
        results.push_back(s);
    } while (next_permutation(s.begin(), s.end()));

    // 3. Нийт тоо болон сэлгэмэлүүдийг хэвлэх
    cout << results.size() << "\n";
    for (const string& str : results) {
        cout << str << "\n";
    }

    return 0;
}