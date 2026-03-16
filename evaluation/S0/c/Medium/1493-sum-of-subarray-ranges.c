// Source: https://leetcode.com/problems/sum-of-subarray-ranges/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums. The range of a subarray of nums is the difference between the largest and smallest element in the subarray.
//
// Return the sum of all subarray ranges of nums.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [1,2,3]
// Output: 4
// Explanation: The 6 subarrays of nums are the following:
// [1], range = largest - smallest = 1 - 1 = 0 
// [2], range = 2 - 2 = 0
// [3], range = 3 - 3 = 0
// [1,2], range = 2 - 1 = 1
// [2,3], range = 3 - 2 = 1
// [1,2,3], range = 3 - 1 = 2
// So the sum of all ranges is 0 + 0 + 0 + 1 + 1 + 2 = 4.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	-109 <= nums[i] <= 109
//
//
//  
// Follow-up: Could you find a solution with O(n) time complexity?
//

long long subArrayRanges(int* nums, int numsSize) {
    long long totalMax = 0, totalMin = 0;
    int stack[numsSize];
    int top, i, j;

    // Calculate totalMax
    top = -1;
    for (i = 0; i <= numsSize; i++) {
        while (top != -1 && (i == numsSize || nums[stack[top]] < nums[i])) {
            j = stack[top--];
            int left = (top == -1) ? j + 1 : j - stack[top];
            int right = i - j;
            totalMax += (long long)nums[j] * left * right;
        }
        stack[++top] = i;
    }

    // Calculate totalMin
    top = -1;
    for (i = 0; i <= numsSize; i++) {
        while (top != -1 && (i == numsSize || nums[stack[top]] > nums[i])) {
            j = stack[top--];
            int left = (top == -1) ? j + 1 : j - stack[top];
            int right = i - j;
            totalMin += (long long)nums[j] * left * right;
        }
        stack[++top] = i;
    }

    return totalMax - totalMin;     
}
