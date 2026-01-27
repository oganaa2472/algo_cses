#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Project {
    int start, end, reward;
};

// Төслүүдийг дуусах хугацаагаар нь эрэмбэлэх функц
bool compareProjects(const Project& a, const Project& b) {
    return a.end < b.end;
}

int main() {
    // Хурдан оролт гаралт
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<Project> projects(n);
    for (int i = 0; i < n; i++) {
        cin >> projects[i].start >> projects[i].end >> projects[i].reward;
    }

    // 1. Дуусах хугацаагаар эрэмбэлнэ
    sort(projects.begin(), projects.end(), compareProjects);

    // Binary search хийхэд хялбар болгох үүднээс зөвхөн дуусах хугацаануудыг тусад нь хадгалая
    vector<int> end_times;
    for (const auto& p : projects) {
        end_times.push_back(p.end);
    }

    // dp[i] = Эхний i төслөөс олох хамгийн их ашиг (1-based index ашиглая)
    vector<long long> dp(n + 1, 0);

    for (int i = 0; i < n; i++) {
        // Одоогийн төсөл: projects[i]
        // Сонголт 1: Энэ төслийг алгасах
        long long skip_reward = dp[i]; // dp[i] нь i-1 дэх төслийн үр дүн (index зөрүүтэйг анхаар)

        // Сонголт 2: Энэ төслийг авах
        long long take_reward = projects[i].reward;

        // Энэ төсөлтэй давхцахгүй хамгийн сүүлийн төслийг хайх
        // end_times дотроос projects[i].start-аас бага дуусах хугацаатайг хайна.
        // lower_bound нь >= утгыг олдог тул түүнээс нэг ухрах хэрэгтэй.
        auto it = lower_bound(end_times.begin(), end_times.end(), projects[i].start);
        
        int idx = distance(end_times.begin(), it) - 1;

        // Хэрэв давхцахгүй төсөл олдвол түүний ашгийг нэмнэ
        if (idx >= 0) {
            take_reward += dp[idx + 1]; // dp массив 1-based index-тэй тул +1
        }

        // Аль ихийг нь сонгож dp-д хадгална
        dp[i + 1] = max(skip_reward, take_reward);
    }

    cout << dp[n] << "\n";

    return 0;
}