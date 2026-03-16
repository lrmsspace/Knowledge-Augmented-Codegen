// Source: https://leetcode.com/problems/minimum-cost-to-convert-string-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given two 0-indexed strings source and target, both of length n and consisting of lowercase English letters. You are also given two 0-indexed character arrays original and changed, and an integer array cost, where cost[i] represents the cost of changing the character original[i] to the character changed[i].
//
// You start with the string source. In one operation, you can pick a character x from the string and change it to the character y at a cost of z if there exists any index j such that cost[j] == z, original[j] == x, and changed[j] == y.
//
// Return the minimum cost to convert the string source to the string target using any number of operations. If it is impossible to convert source to target, return -1.
//
// Note that there may exist indices i, j such that original[j] == original[i] and changed[j] == changed[i].
//
// Example:
// Input: source = "abcd", target = "acbe", original = ["a","b","c","c","e","d"], changed = ["b","c","b","e","b","e"], cost = [2,5,5,1,2,20]
// Output: 28
// Explanation: To convert the string "abcd" to string "acbe":
// - Change value at index 1 from 'b' to 'c' at a cost of 5.
// - Change value at index 2 from 'c' to 'e' at a cost of 1.
// - Change value at index 2 from 'e' to 'b' at a cost of 2.
// - Change value at index 3 from 'd' to 'e' at a cost of 20.
// The total cost incurred is 5 + 1 + 2 + 20 = 28.
// It can be shown that this is the minimum possible cost.
//
// Constraints:
// 1 <= source.length == target.length <= 105
// 	source, target consist of lowercase English letters.
// 	1 <= cost.length == original.length == changed.length <= 2000
// 	original[i], changed[i] are lowercase English letters.
// 	1 <= cost[i] <= 106
// 	original[i] != changed[i]
//

/**
 * @param {string} source
 * @param {string} target
 * @param {character[]} original
 * @param {character[]} changed
 * @param {number[]} cost
 * @return {number}
 */
var minimumCost = function(source, target, original, changed, cost) {
    const graph = {};
    for (let i = 0; i < original.length; i++) {
        if (!graph[original[i]]) {
            graph[original[i]] = [];
        }
        graph[original[i]].push([changed[i], cost[i]]);
    }
    const n = source.length;
    let totalCost = 0;
    for (let i = 0; i < n; i++) {
        if (source[i] === target[i]) {
            continue;
        }
        const minCost = dijkstra(graph, source[i], target[i]);  
        if (minCost === Infinity) {
            return -1;
        }
        totalCost += minCost;
    }
    return totalCost;   
};
