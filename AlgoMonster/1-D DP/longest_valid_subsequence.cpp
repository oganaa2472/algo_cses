//Using Dynamic Programming,
//  we maintain an array dp where dp[i] stores the length of the longest valid parentheses substring ending at i.
class Solution {
public:
    
    int longestValidParentheses(string s) {
        int n = s.size();
        vector<int> dp(n,0);
        int ans = 0;
        for(int i = 1;i<n;i++){
            if(s[i]==')'){
                if(s[i-1]=='(') {
                    dp[i] = (i >= 2 ? dp[i - 2] : 0) + 2;
                }
                else if(i - dp[i - 1] > 0&&s[i - dp[i - 1] - 1] == '('){
                    dp[i] = dp[i - 1] + ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) + 2;
                }
            }
            ans = max(ans,dp[i]);
        }
        return ans;
    }
};