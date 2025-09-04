// prefix and suffix product
// intuition is to use prefix and suffix product to get the product of the array except self
// prefix product is the product of the elements before the current element
// suffix product is the product of the elements after the current element
// we can use two arrays to store the prefix and suffix product
// we can then use the prefix and suffix product to get the product of the array except self
// we can then return the answer array
// time complexity is O(n)
// space complexity is O(n)
class Solution {
    public:
        vector<int> productExceptSelf(vector<int>& nums) {
            int n = nums.size();
            vector<int> prefix(n,1);
            vector<int> suffix(n,1);
            prefix[0] = nums[0];
            for(int i = 1;i<n;i++){
                prefix[i] = prefix[i-1]*nums[i];
            }
            suffix[n-1] = nums[n-1];
            for(int i = n-2;i>=0;i--){
                suffix[i] = suffix[i+1]*nums[i];
    
            }
            vector<int> answer(n,0);
            for(int i = 0;i<n;i++){
                if(i==0){
                    answer[i] = suffix[i+1];
                }else if(i==n-1){
                    answer[i] = prefix[i-1];
                }
                else{
                    answer[i] = prefix[i-1]*suffix[i+1];
                }
            }
            return answer;
        }
    };