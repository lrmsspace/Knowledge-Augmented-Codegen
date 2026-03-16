// Source: https://leetcode.com/problems/trapping-rain-water/   |   Difficulty: Hard
//
// Problem Description:
// Given n non-negative integers representing an elevation map where the width of each bar is 1, compute how much water it can trap after raining.
//
// Example:
// Input: height = [0,1,0,2,1,0,1,3,2,1,2,1]
// Output: 6
// Explanation: The above elevation map (black section) is represented by array [0,1,0,2,1,0,1,3,2,1,2,1]. In this case, 6 units of rain water (blue section) are being trapped.
//
// Constraints:
// n == height.length
// 	1 <= n <= 2 * 104
// 	0 <= height[i] <= 105
//

int trap(int* height, int heightSize) {
    if (heightSize <= 2) return 0;
    int left = 0, right = heightSize - 1;
    int leftMax = height[left], rightMax = height[right];
    int water = 0;
    while (left < right) {
        if (leftMax < rightMax) {
            left++;
            if (height[left] < leftMax) {
                water += leftMax - height[left];
            } else {
                leftMax = height[left];
            }
        } else {
            right--;
            if (height[right] < rightMax) {
                water += rightMax - height[right];
            } else {
                rightMax = height[right];
            }
        }
    }
    return water;       
}
