// Source: https://leetcode.com/problems/minimum-seconds-to-equalize-a-circular-array/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums containing n integers.
//
// At each second, you perform the following operation on the array:
//
//
// 	For every index i in the range [0, n - 1], replace nums[i] with either nums[i], nums[(i - 1 + n) % n], or nums[(i + 1) % n].
//
//
// Note that all the elements get replaced simultaneously.
//
// Return the minimum number of seconds needed to make all elements in the array nums equal.
//
// Example:
// Input: nums = [1,2,1,2]
// Output: 1
// Explanation: We can equalize the array in 1 second in the following way:
// - At 1st second, replace values at each index with [nums[3],nums[1],nums[3],nums[3]]. After replacement, nums = [2,2,2,2].
// It can be proven that 1 second is the minimum amount of seconds needed for equalizing the array.
//
// Constraints:
// 1 <= n == nums.length <= 105
// 	1 <= nums[i] <= 109
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var minimumSeconds = function(nums) {
    const n = nums.length;
    const positionsMap = new Map();
    for (let i = 0; i < n; i++) {
        if (!positionsMap.has(nums[i])) {
            positionsMap.set(nums[i], []);
        }
        positionsMap.get(nums[i]).push(i);
    }
    let minSeconds = Infinity;
    for (const positions of positionsMap.values()) {
        let maxGap = 0;
        const m = positions.length;
        for (let i = 0; i < m; i++) {
            const current = positions[i];
            const next = positions[(i + 1) % m];
            const gap = (next - current + n) % n - 1;
            maxGap = Math.max(maxGap, gap);
        }
        const secondsNeeded = Math.ceil(maxGap / 2);
        minSeconds = Math.min(minSeconds, secondsNeeded);
    }
    return minSeconds;  
};
