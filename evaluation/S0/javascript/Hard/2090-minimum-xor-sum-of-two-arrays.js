// Source: https://leetcode.com/problems/minimum-xor-sum-of-two-arrays/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integer arrays nums1 and nums2 of length n.
//
// The XOR sum of the two integer arrays is (nums1[0] XOR nums2[0]) + (nums1[1] XOR nums2[1]) + ... + (nums1[n - 1] XOR nums2[n - 1]) (0-indexed).
//
//
// 	For example, the XOR sum of [1,2,3] and [3,2,1] is equal to (1 XOR 3) + (2 XOR 2) + (3 XOR 1) = 2 + 0 + 2 = 4.
//
//
// Rearrange the elements of nums2 such that the resulting XOR sum is minimized.
//
// Return the XOR sum after the rearrangement.
//
// Example:
// Input: nums1 = [1,2], nums2 = [2,3]
// Output: 2
// Explanation: Rearrange nums2 so that it becomes [3,2].
// The XOR sum is (1 XOR 3) + (2 XOR 2) = 2 + 0 = 2.
//
// Constraints:
// n == nums1.length
// 	n == nums2.length
// 	1 <= n <= 14
// 	0 <= nums1[i], nums2[i] <= 107
//

/**
 * @param {number[]} nums1
 * @param {number[]} nums2
 * @return {number}
 */
var minimumXORSum = function(nums1, nums2) {
    const n = nums1.length;
    const memo = new Map();
    const dfs = (mask) => {
        if (mask === (1 << n) - 1) {
            return 0;
        }
        if (memo.has(mask)) {
            return memo.get(mask);
        }
        let minSum = Infinity;
        const index = countBits(mask);
        for (let j = 0; j < n; j++) {
            if ((mask & (1 << j)) === 0) {
                const sum = (nums1[index] ^ nums2[j]) + dfs(mask | (1 << j));
                minSum = Math.min(minSum, sum);
            }
        }
        memo.set(mask, minSum);
        return minSum;
    }
    const countBits = (num) => {
        let count = 0;
        while (num > 0) {
            count += num & 1;
            num >>= 1;
        }
        return count;
    }
    return dfs(0);  
};
