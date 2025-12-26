#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * PROBLEM: Movie Festival Queries
 * FIX: Use Suffix Min to find the absolute earliest ending movie starting after time T.
 */

const int MAXN = 200005;
const int LOG = 19;

struct Movie {
    int s, e, id;
};

Movie movies[MAXN];
int up[MAXN][LOG];
int suffix_min_idx[MAXN];

int main() {
    ios::sync_with_stdio(0); cin.tie(0);

    int n, q;
    cin >> n >> q;

    for (int i = 0; i < n; i++) {
        cin >> movies[i].s >> movies[i].e;
        movies[i].id = i;
    }

    // 1. Эхлэх цагаар эрэмбэлнэ
    sort(movies, movies + n, [](const Movie& a, const Movie& b) {
        if (a.s != b.s) return a.s < b.s;
        return a.e < b.e;
    });

    // 2. Suffix Minimum байгуулна: i-ээс хойш эхлэх кинонууд дундаас хамгийн эрт дуусах киноны индекс
    suffix_min_idx[n] = n;
    int min_e = 2e9;
    int best_idx = n;
    for (int i = n - 1; i >= 0; i--) {
        if (movies[i].e < min_e) {
            min_e = movies[i].e;
            best_idx = i;
        }
        suffix_min_idx[i] = best_idx;
    }

    // 3. Binary Lifting хүснэгт (up[i][0] олох)
    vector<int> start_times(n);
    for (int i = 0; i < n; i++) start_times[i] = movies[i].s;

    for (int i = 0; i < n; i++) {
        // i кино дууссаны дараа эхлэх боломжтой анхны киног хайна
        int it = lower_bound(start_times.begin(), start_times.end(), movies[i].e) - start_times.begin();
        if (it < n) {
            // Тэр цагаас хойш эхлэх бүх кинонууд дотроос хамгийн эрт дуусахыг нь сонгоно
            up[i][0] = suffix_min_idx[it];
        } else {
            up[i][0] = n;
        }
    }

    // Binary Lifting-ийн хоосон утга
    for (int j = 0; j < LOG; j++) up[n][j] = n;

    for (int j = 1; j < LOG; j++) {
        for (int i = 0; i < n; i++) {
            up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }

    while (q--) {
        int a, b;
        cin >> a >> b;

        // a цагаас хойш эхлэх боломжтой хамгийн эрт дуусах анхны киног олно
        int it = lower_bound(start_times.begin(), start_times.end(), a) - start_times.begin();
        if (it == n) {
            cout << 0 << "\n";
            continue;
        }

        int curr = suffix_min_idx[it];
        if (movies[curr].e > b) {
            cout << 0 << "\n";
            continue;
        }

        int ans = 1;
        for (int j = LOG - 1; j >= 0; j--) {
            int jump = up[curr][j];
            if (jump < n && movies[jump].e <= b) {
                ans += (1 << j);
                curr = jump;
            }
        }
        cout << ans << "\n";
    }

    return 0;
}