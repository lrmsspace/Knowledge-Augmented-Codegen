// Source: https://leetcode.com/problems/minimum-operations-to-make-the-array-alternating/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums consisting of n positive integers.
//
// The array nums is called alternating if:
//
//
// 	nums[i - 2] == nums[i], where 2 <= i <= n - 1.
// 	nums[i - 1] != nums[i], where 1 <= i <= n - 1.
//
//
// In one operation, you can choose an index i and change nums[i] into any positive integer.
//
// Return the minimum number of operations required to make the array alternating.
//
// Example:
// Input: nums = [3,1,3,2,4,3]
// Output: 3
// Explanation:
// One way to make the array alternating is by converting it to [3,1,3,1,3,1].
// The number of operations required in this case is 3.
// It can be proven that it is not possible to make the array alternating in less than 3 operations.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 105
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var minimumOperations = function(nums) {
    const n = nums.length;
    const evenCount = new Map();
    const oddCount = new Map();
    for (let i = 0; i < n; i++) {
        if (i % 2 === 0) {
            evenCount.set(nums[i], (evenCount.get(nums[i]) || 0) + 1);
        } else {
            oddCount.set(nums[i], (oddCount.get(nums[i]) || 0) + 1);
        }
    }
    const evenArr = Array.from(evenCount.entries()).sort((a, b) => b[1] - a[1]);
    const oddArr = Array.from(oddCount.entries()).sort((a, b) => b[1] - a[1]);
    const evenTop1 = evenArr[0] || [null, 0];
    const evenTop2 = evenArr[1] || [null, 0];
    const oddTop1 = oddArr[0] || [null, 0];
    const oddTop2 = oddArr[1] || [null, 0];
    if (evenTop1[0] !== oddTop1[0]) {
        return n - evenTop1[1] - oddTop1[1];
    } else {
        return Math.min(
            n - evenTop1[1] - oddTop2[1],
            n - evenTop2[1] - oddTop1[1]
        );
    }
};