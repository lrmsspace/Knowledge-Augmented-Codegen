// Source: https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/   |   Difficulty: Medium
//
// Problem Description:
// Given a 1-indexed array of integers numbers that is already sorted in non-decreasing order, find two numbers such that they add up to a specific target number. Let these two numbers be numbers[index1] and numbers[index2] where 1 <= index1 < index2 <= numbers.length.
//
// Return the indices of the two numbers, index1 and index2, added by one as an integer array [index1, index2] of length 2.
//
// The tests are generated such that there is exactly one solution. You may not use the same element twice.
//
// Your solution must use only constant extra space.
//
// Example:
// Input: numbers = [2,7,11,15], target = 9
// Output: [1,2]
// Explanation: The sum of 2 and 7 is 9. Therefore, index1 = 1, index2 = 2. We return [1, 2].
//
// Constraints:
// 2 <= numbers.length <= 3 * 104
// 	-1000 <= numbers[i] <= 1000
// 	numbers is sorted in non-decreasing order.
// 	-1000 <= target <= 1000
// 	The tests are generated such that there is exactly one solution.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int left = 0;
    int right = numbersSize - 1;
    int* result = (int*)malloc(2 * sizeof(int));
    
    while (left < right) {
        int sum = numbers[left] + numbers[right];
        
        if (sum == target) {
            result[0] = left + 1;  // Convert to 1-indexed
            result[1] = right + 1; // Convert to 1-indexed
            *returnSize = 2;
            return result;
        } else if (sum < target) {
            left++;
        } else {
            right--;
        }
    }
    
    // In case there is no solution, though the problem guarantees one.
    *returnSize = 0;
    free(result);
    return NULL;        
}
