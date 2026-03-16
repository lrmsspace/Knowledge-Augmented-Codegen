// Source: https://leetcode.com/problems/pizza-with-3n-slices/   |   Difficulty: Hard
//
// Problem Description:
// There is a pizza with 3n slices of varying size, you and your friends will take slices of pizza as follows:
//
//
// 	You will pick any pizza slice.
// 	Your friend Alice will pick the next slice in the anti-clockwise direction of your pick.
// 	Your friend Bob will pick the next slice in the clockwise direction of your pick.
// 	Repeat until there are no more slices of pizzas.
//
//
// Given an integer array slices that represent the sizes of the pizza slices in a clockwise direction, return the maximum possible sum of slice sizes that you can pick.
//
// Example:
// Input: slices = [1,2,3,4,5,6]
// Output: 10
// Explanation: Pick pizza slice of size 4, Alice and Bob will pick slices with size 3 and 5 respectively. Then Pick slices with size 6, finally Alice and Bob will pick slice of size 2 and 1 respectively. Total = 4 + 6.
//
// Constraints:
// 3 * n == slices.length
// 	1 <= slices.length <= 500
// 	1 <= slices[i] <= 1000
//

/**
 * @param {number[]} slices
 * @return {number}
 */
var maxSizeSlices = function(slices) {
    const n = slices.length;
    const dp1 = new Array(n).fill(0);
    const dp2 = new Array(n).fill(0);
    dp1[0] = slices[0];
    dp1[1] = Math.max(slices[0], slices[1]);
    dp2[1] = slices[1];
    for (let i = 2; i < n - 1; i++) {
        dp1[i] = Math.max(dp1[i - 1], dp1[i - 2] + slices[i]);
    }
    for (let i = 2; i < n; i++) {
        dp2[i] = Math.max(dp2[i - 1], dp2[i - 2] + slices[i]);
    }
    return Math.max(dp1[n - 2], dp2[n - 1]);    
};
