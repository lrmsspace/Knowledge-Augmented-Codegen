// Source: https://leetcode.com/problems/count-pairs-with-xor-in-a-range/   |   Difficulty: Hard
//
// Problem Description:
// Given a (0-indexed) integer array nums and two integers low and high, return the number of nice pairs.
//
// A nice pair is a pair (i, j) where 0 <= i < j < nums.length and low <= (nums[i] XOR nums[j]) <= high.
//
// Example:
// Input: nums = [1,4,2,7], low = 2, high = 6
// Output: 6
// Explanation: All nice pairs (i, j) are as follows:
//     - (0, 1): nums[0] XOR nums[1] = 5 
//     - (0, 2): nums[0] XOR nums[2] = 3
//     - (0, 3): nums[0] XOR nums[3] = 6
//     - (1, 2): nums[1] XOR nums[2] = 6
//     - (1, 3): nums[1] XOR nums[3] = 3
//     - (2, 3): nums[2] XOR nums[3] = 5
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i] <= 2 * 104
// 	1 <= low <= high <= 2 * 104
//

/**
 * @param {number[]} nums
 * @param {number} low
 * @param {number} high
 * @return {number}
 */
var countPairs = function(nums, low, high) {
    const countLessOrEqual = (limit) => {
        let count = 0;
        const trie = new Trie();
        for (const num of nums) {
            count += trie.countLessOrEqual(num, limit);
            trie.insert(num);
        }
        return count;
    }
    return countLessOrEqual(high) - countLessOrEqual(low - 1);  
};
