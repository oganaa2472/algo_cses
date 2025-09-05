class Solution {
    public:
        int subarraySum(vector<int>& nums, int k) {
            unordered_map<int, int> sumCount; // Map to store cumulative sum & its frequency
            sumCount[0] = 1; // Initialize to handle the case when subarray starts from index 0
            int runningSum = 0; // Initialize running sum to 0
            int count = 0; // Initialize the count of subarray sums that equal k
    
            // Iterate through the array
            for (int num : nums) {
                runningSum += num; // Update the running sum by adding the current number
    
                // Check if there exists a prefix sum that, when subtracted from runningSum, gives k
                if (sumCount.find(runningSum - k) != sumCount.end()) {
                    count += sumCount[runningSum - k]; // Increase the count by the number of such prefix sums
                }
    
                // Increment the frequency of the current running sum in the map
                sumCount[runningSum]++;
            }
    
            return count; // Return the total count of subarrays with sum equals to k
        }
    };

Time Complexity: O(n) - We iterate through the array once, and each operation inside the loop is O(1).
Space Complexity: O(n) - In the worst case we could store all unique sums in the map.