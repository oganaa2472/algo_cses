// hashmap
// intuition is to use a hashmap to store the frequency of the elements
// we can then find the majority element by finding the element with the highest frequency
// time complexity is O(n)
// space complexity is O(n)
class Solution {
    public:
        int majorityElement(vector<int>& nums) {
            
            unordered_map<int,int> freq;
            for(auto num:nums){
                freq[num]++;
            }
            int size = nums.size();
            int majorityElement = (size+1)/2;
    
            for(auto [key,value]:freq){
                if(value>=majorityElement){
                    return key;
                }
            }
            return -1;
        }
    };