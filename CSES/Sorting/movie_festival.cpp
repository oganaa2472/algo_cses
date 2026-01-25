#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("O3")
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n;

    vector<pair<int,int>> movies;
    for (int i = 0; i < n; ++i) {
        int start,end;
        cin >> start >> end;
        movies.push_back({start, end});
    }

    sort(movies.begin(), movies.end(), [](const pair<int,int>& a, const  pair<int,int>& b){
        return a.second < b.second;
    });

    int max_movies = 0;
    int last_end_time = 0;
    for (const auto& movie : movies) {
        if (movie.first >= last_end_time) {
            max_movies++;
            last_end_time = movie.second;
        }
    }
    cout << max_movies << "\n";
    return 0;
}