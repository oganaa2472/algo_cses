#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        
        // Step 1: Place each positive integer at its correct position
        // nums[i] should be at index nums[i] - 1
        for (int i = 0; i < n; i++) {
            // While the current element is in valid range [1, n] and not at correct position
            while (nums[i] > 0 && nums[i] <= n && nums[nums[i] - 1] != nums[i]) {
                swap(nums[i], nums[nums[i] - 1]);
            }
        }
        
        // Step 2: Find the first missing positive
        for (int i = 0; i < n; i++) {
            if (nums[i] != i + 1) {
                return i + 1;  // i+1 is missing
            }
        }
        
        // If all numbers from 1 to n are present, return n+1
        return n + 1;
    }
};

// Alternative approach using marking with negative numbers
class Solution2 {
public:
    int firstMissingPositive(vector<int>& nums) {
        int n = nums.size();
        
        // Step 1: Mark numbers outside range [1, n] as n+1
        for (int i = 0; i < n; i++) {
            if (nums[i] <= 0 || nums[i] > n) {
                nums[i] = n + 1;
            }
        }
        
        // Step 2: Mark present numbers as negative
        for (int i = 0; i < n; i++) {
            int num = abs(nums[i]);
            if (num <= n) {
                nums[num - 1] = -abs(nums[num - 1]);
            }
        }
        
        // Step 3: Find first positive number (missing)
        for (int i = 0; i < n; i++) {
            if (nums[i] > 0) {
                return i + 1;
            }
        }
        
        return n + 1;
    }
};

int main() {
    Solution solution;
    
    // Test cases
    vector<vector<int>> testCases = {
        {1, 2, 0},           // Expected: 3
        {3, 4, -1, 1},       // Expected: 2
        {7, 8, 9, 11, 12},   // Expected: 1
        {1, 2, 3, 4},        // Expected: 5
        {1},                 // Expected: 2
        {2, 1},              // Expected: 3
        {1, 1},              // Expected: 2
        {3, 4, -1, 1, 2},    // Expected: 5
    };
    
    cout << "First Missing Positive - Test Results:" << endl;
    cout << "=====================================" << endl;
    
    for (int i = 0; i < testCases.size(); i++) {
        vector<int> nums = testCases[i];
        int result = solution.firstMissingPositive(nums);
        
        cout << "Test " << (i + 1) << ": ";
        cout << "Input: [";
        for (int j = 0; j < nums.size(); j++) {
            cout << nums[j];
            if (j < nums.size() - 1) cout << ", ";
        }
        cout << "] -> Result: " << result << endl;
    }
    
    cout << "\nExplanation:" << endl;
    cout << "=============" << endl;
    cout << "1. We use the array itself as a hash table" << endl;
    cout << "2. Place each positive integer at index (value - 1)" << endl;
    cout << "3. After rearrangement, nums[i] should equal i+1" << endl;
    cout << "4. First position where this doesn't hold is our answer" << endl;
    cout << "5. If all positions are correct, answer is n+1" << endl;
    cout << "\nTime Complexity: O(n)" << endl;
    cout << "Space Complexity: O(1)" << endl;
    
    return 0;
}