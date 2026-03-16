// Source: https://leetcode.com/problems/possible-bipartition/   |   Difficulty: Medium
//
// Problem Description:
// We want to split a group of n people (labeled from 1 to n) into two groups of any size. Each person may dislike some other people, and they should not go into the same group.
//
// Given the integer n and the array dislikes where dislikes[i] = [ai, bi] indicates that the person labeled ai does not like the person labeled bi, return true if it is possible to split everyone into two groups in this way.
//
// Example:
// Input: n = 4, dislikes = [[1,2],[1,3],[2,4]]
// Output: true
// Explanation: The first group has [1,4], and the second group has [2,3].
//
// Constraints:
// 1 <= n <= 2000
// 	0 <= dislikes.length <= 104
// 	dislikes[i].length == 2
// 	1 <= ai < bi <= n
// 	All the pairs of dislikes are unique.
//

/**
 * @param {number} n
 * @param {number[][]} dislikes
 * @return {boolean}
 */
var possibleBipartition = function(n, dislikes) {
    const graph = Array.from({ length: n + 1 }, () => []);

    for (const [a, b] of dislikes) {
        graph[a].push(b);
        graph[b].push(a);
    }    

    const colors = new Array(n + 1).fill(0);

    const dfs = (node, color) => {
        colors[node] = color;
        for (const neighbor of graph[node]) {
            if (colors[neighbor] === color) {
                return false;
            }
            if (colors[neighbor] === 0 && !dfs(neighbor, -color)) {
                return false;
            }
        }
        return true;
    };

    for (let i = 1; i <= n; i++) {
        if (colors[i] === 0 && !dfs(i, 1)) {
            return false;
        }
    }

    return true;
};