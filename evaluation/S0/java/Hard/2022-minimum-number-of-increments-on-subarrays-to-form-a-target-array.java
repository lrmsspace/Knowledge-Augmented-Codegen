// Source: https://leetcode.com/problems/minimum-number-of-increments-on-subarrays-to-form-a-target-array/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array target. You have an integer array initial of the same size as target with all elements initially zeros.
//
// In one operation you can choose any subarray from initial and increment each value by one.
//
// Return the minimum number of operations to form a target array from initial.
//
// The test cases are generated so that the answer fits in a 32-bit integer.
//
// Example:
// Input: target = [1,2,3,2,1]
// Output: 3
// Explanation: We need at least 3 operations to form the target array from the initial array.
// [0,0,0,0,0] increment 1 from index 0 to 4 (inclusive).
// [1,1,1,1,1] increment 1 from index 1 to 3 (inclusive).
// [1,2,2,2,1] increment 1 at index 2.
// [1,2,3,2,1] target array is formed.
//
// Constraints:
// 1 <= target.length <= 105
// 	1 <= target[i] <= 105
//

class Solution {
    public int minNumberOperations(int[] target) {
        int operations = target[0];

        for (int i = 1; i < target.length; i++) {
            if (target[i] > target[i - 1]) {
                operations += target[i] - target[i - 1];
            }
        }

        return operations;                  
    }
}
