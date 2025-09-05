class Solution {
    public:
        int maxArea(vector<int>& height) {
            int left = 0; // Pointer at the start of the array
            int right = height.size() - 1; // Pointer at the end of the array
            int max_area = 0; // Initialize max_area to track the largest area found
    
            // While left pointer is less than right pointer
            while (left < right) {
                // Calculate the height as the minimum of height[left] and height[right]
                int current_height = min(height[left], height[right]);
                // Calculate the width as the distance between the two pointers
                int width = right - left;
                // Calculate the current area
                int current_area = current_height * width;
                // Update the maximum area if the current area is larger
                max_area = max(max_area, current_area);
    
                // Move the pointer of the shorter line inward
                if (height[left] < height[right]) {
                    left++; // Move the left pointer rightwards
                } else {
                    right--; // Move the right pointer leftwards
                }
            }
    
            return max_area;
        }
    };