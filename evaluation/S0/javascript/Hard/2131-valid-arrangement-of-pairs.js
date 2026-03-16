// Source: https://leetcode.com/problems/valid-arrangement-of-pairs/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed 2D integer array pairs where pairs[i] = [starti, endi]. An arrangement of pairs is valid if for every index i where 1 <= i < pairs.length, we have endi-1 == starti.
//
// Return any valid arrangement of pairs.
//
// Note: The inputs will be generated such that there exists a valid arrangement of pairs.
//
// Example:
// Input: pairs = [[5,1],[4,5],[11,9],[9,4]]
// Output: [[11,9],[9,4],[4,5],[5,1]]
// Explanation:
// This is a valid arrangement since endi-1 always equals starti.
// end0 = 9 == 9 = start1 
// end1 = 4 == 4 = start2
// end2 = 5 == 5 = start3
//
// Constraints:
// 1 <= pairs.length <= 105
// 	pairs[i].length == 2
// 	0 <= starti, endi <= 109
// 	starti != endi
// 	No two pairs are exactly the same.
// 	There exists a valid arrangement of pairs.
//

/**
 * @param {number[][]} pairs
 * @return {number[][]}
 */
var validArrangement = function(pairs) {
    const graph = new Map();
    const inDegree = new Map();
    const outDegree = new Map();
    for (const [start, end] of pairs) {
        if (!graph.has(start)) {
            graph.set(start, []);
        }
        graph.get(start).push(end);
        outDegree.set(start, (outDegree.get(start) || 0) + 1);
        inDegree.set(end, (inDegree.get(end) || 0) + 1);
    }
    let startNode = null;
    for (const node of graph.keys()) {
        const out = outDegree.get(node) || 0;
        const inn = inDegree.get(node) || 0;
        if (out - inn === 1) {
            startNode = node;
            break;
        }
    }
    if (startNode === null) {
        startNode = pairs[0][0];
    }
    const result = [];
    const dfs = (node) => {
        while (graph.has(node) && graph.get(node).length > 0) {
            const nextNode = graph.get(node).pop();
            dfs(nextNode);
        }
        result.push(node);
    }
    dfs(startNode);
    return result.reverse().map(node => [node, graph.get(node) ? graph.get(node).pop() : null]).filter(pair => pair[1] !== null);
};
