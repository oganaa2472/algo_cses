#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n,k;
    cin >> n>>k;

    vector<int> heights(n);
    for (int i = 0; i < n; i++) {
        cin >> heights[i];
    }
    sort(heights.begin(), heights.end());

    int left = 0;
    int right = n - 1;
    int rides = 0;
    while (left <= right) {
        if (heights[left] + heights[right] <= k) {
            left++;
        }
        right--;
        rides++;
    }
    cout << rides << "\n";
    return 0;
}