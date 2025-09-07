class Solution {
    public:
        bool isValid(string s) {
            stack<char> matchStack;
            // Iterate through each character in the string
            for (char c : s) {
                // If opening bracket, push to stack
                if (c == '(' || c == '[' || c == '{') {
                    matchStack.push(c);
                } else {
                    // If stack is empty or mismatch in closing bracket, return false
                    if (matchStack.empty() || 
                        (c == ')' && matchStack.top() != '(') ||
                        (c == ']' && matchStack.top() != '[') ||
                        (c == '}' && matchStack.top() != '{')) {
                        return false;
                    }
                    // Matching bracket found, pop the top
                    matchStack.pop();
                }
            }
            // If stack is empty, all brackets matched, hence valid
            return matchStack.empty();
        }
    };