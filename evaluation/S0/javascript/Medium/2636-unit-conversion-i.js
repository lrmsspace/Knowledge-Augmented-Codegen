// Source: https://leetcode.com/problems/unit-conversion-i/   |   Difficulty: Medium
//
// Problem Description:
// There are n types of units indexed from 0 to n - 1. You are given a 2D integer array conversions of length n - 1, where conversions[i] = [sourceUniti, targetUniti, conversionFactori]. This indicates that a single unit of type sourceUniti is equivalent to conversionFactori units of type targetUniti.
//
// Return an array baseUnitConversion of length n, where baseUnitConversion[i] is the number of units of type i equivalent to a single unit of type 0. Since the answer may be large, return each baseUnitConversion[i] modulo 109 + 7.
//
// Example:
// Input: conversions = [[0,1,2],[1,2,3]]
//
// Output: [1,2,6]
//
// Explanation:
//
//
// 	Convert a single unit of type 0 into 2 units of type 1 using conversions[0].
// 	Convert a single unit of type 0 into 6 units of type 2 using conversions[0], then conversions[1].
//
// Constraints:
// 2 <= n <= 105
// 	conversions.length == n - 1
// 	0 <= sourceUniti, targetUniti < n
// 	1 <= conversionFactori <= 109
// 	It is guaranteed that unit 0 can be converted into any other unit through a unique combination of conversions without using any conversions in the opposite direction.
//

/**
 * @param {number[][]} conversions
 * @return {number[]}
 */
var baseUnitConversions = function(conversions) {
    const mod = 1e9 + 7;
    const n = conversions.length + 1;
    const graph = Array.from({ length: n }, () => []);
    for (const [source, target, factor] of conversions) {
        graph[source].push([target, factor]);
    }
    const baseUnitConversion = Array(n).fill(0);
    baseUnitConversion[0] = 1;
    const queue = [0];
    while (queue.length > 0) {
        const current = queue.shift();
        for (const [next, factor] of graph[current]) {
            baseUnitConversion[next] = (baseUnitConversion[current] * factor) % mod;
            queue.push(next);
        }
    }
    return baseUnitConversion;
};