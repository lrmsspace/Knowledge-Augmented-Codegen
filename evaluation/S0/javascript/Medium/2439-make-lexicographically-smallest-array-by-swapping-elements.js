// Source: https://leetcode.com/problems/make-lexicographically-smallest-array-by-swapping-elements/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array of positive integers nums and a positive integer limit.
//
// In one operation, you can choose any two indices i and j and swap nums[i] and nums[j] if |nums[i] - nums[j]| <= limit.
//
// Return the lexicographically smallest array that can be obtained by performing the operation any number of times.
//
// An array a is lexicographically smaller than an array b if in the first position where a and b differ, array a has an element that is less than the corresponding element in b. For example, the array [2,10,3] is lexicographically smaller than the array [10,2,3] because they differ at index 0 and 2 < 10.
//
// Example:
// Input: nums = [1,5,3,9,8], limit = 2
// Output: [1,3,5,8,9]
// Explanation: Apply the operation 2 times:
// - Swap nums[1] with nums[2]. The array becomes [1,3,5,9,8]
// - Swap nums[3] with nums[4]. The array becomes [1,3,5,8,9]
// We cannot obtain a lexicographically smaller array by applying any more operations.
// Note that it may be possible to get the same result by doing different operations.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	1 <= limit <= 109
//

/**
 * @param {number[]} nums
 * @param {number} limit
 * @return {number[]}
 */
var lexicographicallySmallestArray = function(nums, limit) {
    const n = nums.length;
    const visited = Array(n).fill(false);
    const result = Array(n);.fill(0);
    for (let i = 0; i < n; i++) {
        if (!visited[i]) {
            const componentIndices = [];
            const queue = [i];
            visited[i] = true;
            while (queue.length > 0) {
                const current = queue.shift();
                componentIndices.push(current);
                for (let j = 0; j < n; j++) {
                    if (!visited[j] && Math.abs(nums[current] - nums[j]) <= limit) {
                        visited[j] = true;
                        queue.push(j);
                    }
                }
            }
            const componentValues = componentIndices.map(index => nums[index]);
            componentIndices.sort((a, b) => a - b);
            componentValues.sort((a, b) => a - b);
            for (let k = 0; k < componentIndices.length; k++) {
                result[componentIndices[k]] = componentValues[k];
            }
        }
    }
    return result;
};
