// Source: https://leetcode.com/problems/maximum-good-subtree-score/   |   Difficulty: Hard
//
// Problem Description:
// You are given an undirected tree rooted at node 0 with n nodes numbered from 0 to n - 1. Each node i has an integer value vals[i], and its parent is given by par[i].
//
// A subset of nodes within the subtree of a node is called good if every digit from 0 to 9 appears at most once in the decimal representation of the values of the selected nodes.
//
// The score of a good subset is the sum of the values of its nodes.
//
// Define an array maxScore of length n, where maxScore[u] represents the maximum possible sum of values of a good subset of nodes that belong to the subtree rooted at node u, including u itself and all its descendants.
//
// Return the sum of all values in maxScore.
//
// Since the answer may be large, return it modulo 109 + 7.
//
// Example:
// Input: vals = [2,3], par = [-1,0]
//
// Output: 8
//
// Explanation:
//
//
//
//
// 	The subtree rooted at node 0 includes nodes {0, 1}. The subset {2, 3} is good as the digits 2 and 3 appear only once. The score of this subset is 2 + 3 = 5.
// 	The subtree rooted at node 1 includes only node {1}. The subset {3} is good. The score of this subset is 3.
// 	The maxScore array is [5, 3], and the sum of all values in maxScore is 5 + 3 = 8. Thus, the answer is 8.
//
// Constraints:
// 1 <= n == vals.length <= 500
// 	1 <= vals[i] <= 109
// 	par.length == n
// 	par[0] == -1
// 	0 <= par[i] < n for i in [1, n - 1]
// 	The input is generated such that the parent array par represents a valid tree.
//

/**
 * @param {number[]} vals
 * @param {number[]} par
 * @return {number}
 */
var goodSubtreeSum = function(vals, par) {
    const MOD = 1e9 + 7;
    const n = vals.length;
    const graph = new Array(n).fill(0).map(() => []);
    for (let i = 1; i < n; i++) {
        graph[par[i]].push(i);
    }

    const getDigitsMask = (num) => {
        let mask = 0;
        while (num > 0) {
            const digit = num % 10;
            mask |= (1 << digit);
            num = Math.floor(num / 10);
        }
        return mask;
    }
    const dp = Array.from({ length: n }, () => new Map());

    const dfs = (node) => {
        const nodeMask = getDigitsMask(vals[node]);
        dp[node].set(nodeMask, vals[node]);
        for (const child of graph[node]) {
            dfs(child);
            const childDP = dp[child];
            const newDP = new Map(dp[node]);
            for (const [mask1, sum1] of dp[node]) {
                for (const [mask2, sum2] of childDP) {
                    if ((mask1 & mask2) === 0) {
                        const newMask = mask1 | mask2;
                        const newSum = sum1 + sum2;
                        if (!newDP.has(newMask) || newDP.get(newMask) < newSum) {
                            newDP.set(newMask, newSum);
                        }
                    }
                }
            }
            dp[node] = newDP;
        }
    };
    dfs(0);
    let result = 0;
    for (let i = 0; i < n; i++) {
        let maxScore = 0;
        for (const sum of dp[i].values()) {
            if (sum > maxScore) {
                maxScore = sum;
            }
        }
        result = (result + maxScore) % MOD;
    }
    return result;
};
