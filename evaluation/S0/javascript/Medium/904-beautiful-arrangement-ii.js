// Source: https://leetcode.com/problems/beautiful-arrangement-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given two integers n and k, construct a list answer that contains n different positive integers ranging from 1 to n and obeys the following requirement:
//
//
// 	Suppose this list is answer = [a1, a2, a3, ... , an], then the list [|a1 - a2|, |a2 - a3|, |a3 - a4|, ... , |an-1 - an|] has exactly k distinct integers.
//
//
// Return the list answer. If there multiple valid answers, return any of them.
//
// Example:
// Input: n = 3, k = 1
// Output: [1,2,3]
// Explanation: The [1,2,3] has three different positive integers ranging from 1 to 3, and the [1,1] has exactly 1 distinct integer: 1
//
// Constraints:
// 1 <= k < n <= 104
//

/**
 * @param {number} n
 * @param {number} k
 * @return {number[]}
 */
var constructArray = function(n, k) {
    const result = [];
    let left = 1;
    let right = n;
    while (left <= right) {
        if (k > 1) {
            if (k % 2 === 1) {
                result.push(left++);
            } else {
                result.push(right--);
            }
            k--;
        } else {
            result.push(left++);
        }
    }
    return result;
};