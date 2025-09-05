#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> height(n);
    for(int i = 0;i<n;i++){
        cin >> height[i];
    }
    int left = 0;
    int right = n-1;
    int left_max = 0;
    int right_max = 0;
    int result = 0;
    while(left<right){
        if(height[left]<height[right]){
            if(height[left]>left_max){
                left_max = height[left];
            }else{
                result += left_max - height[left];
            }
            left++;
        }else{
            if(height[right]>right_max){
                right_max = height[right];
            }else{
                result += right_max - height[right];
            }
            right--;
        }
    }
    cout<<result;
    return 0;

}   