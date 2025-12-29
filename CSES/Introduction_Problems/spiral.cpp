#include <iostream>
#include <algorithm>

using namespace std;

void solve() {
    long long y, x;
    cin >> y >> x;
    
    long long z = max(y, x); // Аль үед байгааг олох
    long long result;

    if (z % 2 == 0) {
        // Тэгш үеийн үед
        if (y == z) {
            // Мөр нь үеийн дугаартай тэнцүү бол баруун тийш өснө
            result = z * z - x + 1;
        } else {
            // Багана нь үеийн дугаартай тэнцүү бол доошоо өснө
            result = (z - 1) * (z - 1) + y;
        }
    } else {
        // Сондгой үеийн үед
        if (x == z) {
            // Багана нь үеийн дугаартай тэнцүү бол доошоо өснө
            result = z * z - y + 1;
        } else {
            // Мөр нь үеийн дугаартай тэнцүү бол баруун тийш өснө
            result = (z - 1) * (z - 1) + x;
        }
    }
    
    cout << result << "\n";
}

int main() {
    // Оролт гаралтыг хурдасгах
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}