// Source: https://leetcode.com/problems/minimum-cost-to-convert-string-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given two 0-indexed strings source and target, both of length n and consisting of lowercase English characters. You are also given two 0-indexed string arrays original and changed, and an integer array cost, where cost[i] represents the cost of converting the string original[i] to the string changed[i].
//
// You start with the string source. In one operation, you can pick a substring x from the string, and change it to y at a cost of z if there exists any index j such that cost[j] == z, original[j] == x, and changed[j] == y. You are allowed to do any number of operations, but any pair of operations must satisfy either of these two conditions:
//
//
// 	The substrings picked in the operations are source[a..b] and source[c..d] with either b < c or d < a. In other words, the indices picked in both operations are disjoint.
// 	The substrings picked in the operations are source[a..b] and source[c..d] with a == c and b == d. In other words, the indices picked in both operations are identical.
//
//
// Return the minimum cost to convert the string source to the string target using any number of operations. If it is impossible to convert source to target, return -1.
//
// Note that there may exist indices i, j such that original[j] == original[i] and changed[j] == changed[i].
//
// Example:
// Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
// Output: 28
// Explanation: To convert "abcd" to "acbe", do the following operations:
// - Change substring source[1..1] from "b" to "c" at a cost of 5.
// - Change substring source[2..2] from "c" to "e" at a cost of 1.
// - Change substring source[2..2] from "e" to "b" at a cost of 2.
// - Change substring source[3..3] from "d" to "e" at a cost of 20.
// The total cost incurred is 5 + 1 + 2 + 20 = 28. 
// It can be shown that this is the minimum possible cost.
//
// Constraints:
// 1 <= source.length == target.length <= 1000
// 	source, target consist only of lowercase English characters.
// 	1 <= cost.length == original.length == changed.length <= 100
// 	1 <= original[i].length == changed[i].length <= source.length
// 	original[i], changed[i] consist only of lowercase English characters.
// 	original[i] != changed[i]
// 	1 <= cost[i] <= 106
//

/**
 * @param {string} source
 * @param {string} target
 * @param {string[]} original
 * @param {string[]} changed
 * @param {number[]} cost
 * @return {number}
 */
var minimumCost = function(source, target, original, changed, cost) {
    const n = source.length;
    const m = original.length;
    const dp = new Array(n + 1).fill(Infinity);
    dp[0] = 0;
    for (let i = 1; i <= n; i++) {
        dp[i] = Math.min(dp[i], dp[i - 1] + (source[i - 1] === target[i - 1] ? 0 : Infinity));
        for (let j = 0; j < m; j++) {
            const len = original[j].length;
            if (i >= len && source.slice(i - len, i) === original[j] && target.slice(i - len, i) === changed[j]) {
                dp[i] = Math.min(dp[i], dp[i - len] + cost[j]);
            }
        }
    }
    return dp[n] === Infinity ? -1 : dp[n]; 
};
