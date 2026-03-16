// Source: https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer x. In one operation, you can either remove the leftmost or the rightmost element from the array nums and subtract its value from x. Note that this modifies the array for future operations.
//
// Return the minimum number of operations to reduce x to exactly 0 if it is possible, otherwise, return -1.
//
// Example:
// Input: nums = [1,1,4,2,3], x = 5
// Output: 2
// Explanation: The optimal solution is to remove the last two elements to reduce x to zero.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 104
// 	1 <= x <= 109
//

int minOperations(int* nums, int numsSize, int x) {
    int total = 0;
    for (int i = 0; i < numsSize; i++) {
        total += nums[i];
    }
    
    int target = total - x;
    if (target < 0) {
        return -1;
    }
    if (target == 0) {
        return numsSize;
    }
    
    int maxLength = -1;
    int currentSum = 0;
    int left = 0;
    
    for (int right = 0; right < numsSize; right++) {
        currentSum += nums[right];
        
        while (currentSum > target && left <= right) {
            currentSum -= nums[left];
            left++;
        }
        
        if (currentSum == target) {
            int currentLength = right - left + 1;
            if (currentLength > maxLength) {
                maxLength = currentLength;
            }
        }
    }
    
    return maxLength == -1 ? -1 : numsSize - maxLength;     
}
