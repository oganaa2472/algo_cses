#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Элементүүдийн бүх боломжит дэд олонлогийн нийлбэрийг олох функц
vector<long long> get_subset_sums(const vector<long long>& nums) {
    int n = nums.size();
    vector<long long> sums;
    
    // 2^n боломжоор гүйнэ
    for (int i = 0; i < (1 << n); i++) {
        long long current_sum = 0;
        for (int j = 0; j < n; j++) {
            if ((i >> j) & 1) {
                current_sum += nums[j];
            }
        }
        sums.push_back(current_sum);
    }
    return sums;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long x;
    if (!(cin >> n >> x)) return 0;

    vector<long long> left, right;
    for (int i = 0; i < n; i++) {
        long long val;
        cin >> val;
        if (i < n / 2) {
            left.push_back(val);
        } else {
            right.push_back(val);
        }
    }

    // Зүүн ба баруун талын бүх нийлбэрүүдийг олно
    vector<long long> left_sums = get_subset_sums(left);
    vector<long long> right_sums = get_subset_sums(right);

    // Хоёртын хайлт хийхийн тулд баруун талын нийлбэрүүдийг эрэмбэлнэ
    sort(right_sums.begin(), right_sums.end());

    long long total_ways = 0;

    // Зүүн талын нийлбэр бүрт тохирох (x - s) утгыг баруун талаас хайна
    for (long long s : left_sums) {
        long long target = x - s;
        // equal_range нь target-тай тэнцүү элементүүдийн давтамжийг олно
        auto range = equal_range(right_sums.begin(), right_sums.end(), target);
        total_ways += (range.second - range.first);
    }

    cout << total_ways << "\n";

    return 0;
}