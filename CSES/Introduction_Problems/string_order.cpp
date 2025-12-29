#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool can_complete(int remaining_len, const vector<int>& counts) {
    for (int i = 0; i < 26; i++) {
        // Аль нэг тэмдэгтийн тоо үлдсэн зайн хагасаас хэтэрвэл боломжгүй
        if (counts[i] > (remaining_len + 1) / 2) return false;
    }
    return true;
}

int main() {
    string s;
    cin >> s;
    int n = s.length();
    vector<int> counts(26, 0);
    for (char c : s) counts[c - 'A']++;

    // Боломжтой эсэхийг урьдчилан шалгах
    if (!can_complete(n, counts)) {
        cout << -1 << endl;
        return 0;
    }

    string result = "";
    int last_idx = -1;

    for (int i = 0; i < n; i++) {
        bool found = false;
        for (int j = 0; j < 26; j++) {
            if (counts[j] > 0 && j != last_idx) {
                // Түр сонгож үзээд шалгах
                counts[j]--;
                if (can_complete(n - 1 - i, counts)) {
                    result += (char)(j + 'A');
                    last_idx = j;
                    found = true;
                    break;
                }
                // Болохгүй бол буцааж нэмэх
                counts[j]++;
            }
        }
        if (!found) {
            cout << -1 << endl;
            return 0;
        }
    }

    cout << result << endl;
    return 0;
}