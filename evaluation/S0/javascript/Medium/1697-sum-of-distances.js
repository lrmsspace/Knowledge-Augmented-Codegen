// Source: https://leetcode.com/problems/sum-of-distances/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums. There exists an array arr of length nums.length, where arr[i] is the sum of |i - j| over all j such that nums[j] == nums[i] and j != i. If there is no such j, set arr[i] to be 0.
//
// Return the array arr.
//
// Example:
// Input: nums = [1,3,1,1,2]
// Output: [5,0,3,4,0]
// Explanation: 
// When i = 0, nums[0] == nums[2] and nums[0] == nums[3]. Therefore, arr[0] = |0 - 2| + |0 - 3| = 5. 
// When i = 1, arr[1] = 0 because there is no other index with value 3.
// When i = 2, nums[2] == nums[0] and nums[2] == nums[3]. Therefore, arr[2] = |2 - 0| + |2 - 3| = 3. 
// When i = 3, nums[3] == nums[0] and nums[3] == nums[2]. Therefore, arr[3] = |3 - 0| + |3 - 2| = 4. 
// When i = 4, arr[4] = 0 because there is no other index with value 2.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 109
//
//
//  
// Note: This question is the same as  2121: Intervals Between Identical Elements.
//

/**
 * @param {number[]} nums
 * @return {number[]}
 */
var distance = function(nums) {
    const indexMap = new Map();
    const result = new Array(nums.length).fill(0);
    for (let i = 0; i < nums.length; i++) {
        const num = nums[i];
        if (!indexMap.has(num)) {
            indexMap.set(num, []);
        }
        indexMap.get(num).push(i);
    }
    for (const [num, indices] of indexMap.entries()) {
        const n = indices.length;
        let prefixSum = new Array(n + 1).fill(0);
        for (let i = 0; i < n; i++) {
            prefixSum[i + 1] = prefixSum[i] + indices[i];
        }
        for (let i = 0; i < n; i++) {
            const index = indices[i];
            const leftCount = i;
            const rightCount = n - i - 1;
            const leftSum = prefixSum[i];
            const rightSum = prefixSum[n] - prefixSum[i + 1];
            result[index] = (index * leftCount - leftSum) + (rightSum - index * rightCount);
        }
    }
    return result;
        
};
