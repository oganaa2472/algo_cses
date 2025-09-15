#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;
long long largestRectangleArea(vector<long long>& heights) {
    int n = heights.size();
    vector<long long> nextSmaller(n, n);
    vector<long long> prevSmaller(n, -1);
    stack<int> st;

    // Previous Smaller (left)
    for(int i = 0; i < n; i++) {
        while(!st.empty() && heights[st.top()] >= heights[i]) {
            st.pop();
        }
        if(!st.empty()) prevSmaller[i] = st.top();
        st.push(i);
    }

    // clear stack for next loop
    while(!st.empty()) st.pop();

    // Next Smaller (right)
    for(int i = n-1; i >= 0; i--) {
        while(!st.empty() && heights[st.top()] >= heights[i]) {
            st.pop();
        }
        if(!st.empty()) nextSmaller[i] = st.top();
        st.push(i);
    }

    long long answer = 0;
    for(int i = 0; i < n; i++) {
        long long width = nextSmaller[i] - prevSmaller[i] - 1;
        long long area = heights[i] * width;
        answer = max(answer, area);
    }
    return answer;
}
int main() {
	// your code goes here
	int n;
	cin>>n;
	vector<long long> a(n);
	for(int i = 0;i<n;i++){
		cin>>a[i];
	}
	cout<<largestRectangleArea(a)<<endl;
}