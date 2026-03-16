// Source: https://leetcode.com/problems/tallest-billboard/   |   Difficulty: Hard
//
// Problem Description:
// You are installing a billboard and want it to have the largest height. The billboard will have two steel supports, one on each side. Each steel support must be an equal height.
//
// You are given a collection of rods that can be welded together. For example, if you have rods of lengths 1, 2, and 3, you can weld them together to make a support of length 6.
//
// Return the largest possible height of your billboard installation. If you cannot support the billboard, return 0.
//
// Example:
// Input: rods = [1,2,3,6]
// Output: 6
// Explanation: We have two disjoint subsets {1,2,3} and {6}, which have the same sum = 6.
//
// Constraints:
// 1 <= rods.length <= 20
// 	1 <= rods[i] <= 1000
// 	sum(rods[i]) <= 5000
//

/**
 * @param {number[]} rods
 * @return {number}
 */
var tallestBillboard = function(rods) {
    const dp = new Map();
    dp.set(0, 0);
    for (const rod of rods) {
        const newDp = new Map(dp);
        for (const [diff, height] of dp.entries()) {
            newDp.set(diff + rod, Math.max(newDp.get(diff + rod) || 0, height));
            newDp.set(Math.abs(diff - rod), Math.max(newDp.get(Math.abs(diff - rod)) || 0, height + Math.min(diff, rod)));
        }
        dp.clear();
        for (const [diff, height] of newDp.entries()) {
            dp.set(diff, height);
        }
    }
    return dp.get(0) || 0;  
};
