class Solution {
    public:
        
    
        vector<vector<int>> subsets(vector<int>& nums) {
            vector<vector<int>> result;
            int n = nums.size();
            for(int mask = 0; mask < (1 << n); mask++) {
                vector<int> subset;
                for(int j = 0; j < n; j++) {
                    if(mask & (1 << j)) { 
                        subset.push_back(nums[j]);
                    }
                }
                result.push_back(subset);
            }
            return result;
        }
    };