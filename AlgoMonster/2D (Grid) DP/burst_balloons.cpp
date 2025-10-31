class Solution {
public:
    int dp(vector<int>& nums, vector<vector<int>>& memo, int left, int right) {
        // If the subproblem is already solved, return the solution
        if (left + 1 == right) return 0;
        if (memo[left][right] != -1) return memo[left][right];

        // Try bursting each balloon between left and right
        int maxCoins = 0;
        for (int i = left + 1; i < right; ++i) {
            // Coins collected from this particular choice
            int coins = nums[left] * nums[i] * nums[right];
            // Recursively compute the maximum coins by bursting sub-problems
            coins += dp(nums, memo, left, i) + dp(nums, memo, i, right);
            // Update the maximum
            maxCoins = max(maxCoins, coins);
        }
        // Save the computed result
        memo[left][right] = maxCoins;
        return maxCoins;
    }
    
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        nums.insert(nums.begin(), 1);
        nums.push_back(1);
        vector<vector<int>> memo(n + 2, vector<int>(n + 2, -1));
        return dp(nums, memo, 0, n + 1);
    }
};