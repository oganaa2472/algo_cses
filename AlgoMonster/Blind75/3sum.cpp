class Solution {
    public:
        vector<vector<int>> threeSum(vector<int>& nums) {
            // Sort the vector to facilitate the two-pointer approach
            sort(nums.begin(), nums.end());
            int n = nums.size();
            vector<vector<int>> result;
            
            for (int i = 0; i < n - 2; ++i) {
                if (i > 0 && nums[i] == nums[i - 1]) continue; // Skip duplicate elements
                
                int left = i + 1;
                int right = n - 1;
                while (left < right) {
                    int sum = nums[i] + nums[left] + nums[right];
                    
                    if (sum < 0) {
                        left++; // Move the left pointer to increase the sum
                    } else if (sum > 0) {
                        right--; // Move the right pointer to decrease the sum
                    } else {
                        result.push_back({nums[i], nums[left], nums[right]});
                        // Avoid duplicates for the second element
                        while (left < right && nums[left] == nums[left + 1]) left++;
                        // Avoid duplicates for the third element
                        while (left < right && nums[right] == nums[right - 1]) right--;
                        left++;
                        right--;
                    }
                }
            }
            
            return result;
        }
    };