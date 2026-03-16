// Source: https://leetcode.com/problems/find-three-consecutive-integers-that-sum-to-a-given-number/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer num, return three consecutive integers (as a sorted array) that sum to num. If num cannot be expressed as the sum of three consecutive integers, return an empty array.
//
// Example:
// Input: num = 33
// Output: [10,11,12]
// Explanation: 33 can be expressed as 10 + 11 + 12 = 33.
// 10, 11, 12 are 3 consecutive integers, so we return [10, 11, 12].
//
// Constraints:
// 0 <= num <= 1015
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
long long* sumOfThree(long long num, int* returnSize) {
    if (num % 3 != 0) {
        *returnSize = 0;
        return NULL;
    }
    
    long long* result = (long long*)malloc(3 * sizeof(long long));
    long long mid = num / 3;
    
    result[0] = mid - 1;
    result[1] = mid;
    result[2] = mid + 1;
    
    *returnSize = 3;
    return result;      
}
