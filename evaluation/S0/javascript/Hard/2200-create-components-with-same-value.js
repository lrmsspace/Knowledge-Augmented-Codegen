// Source: https://leetcode.com/problems/create-components-with-same-value/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 0 to n - 1.
//
// You are given a 0-indexed integer array nums of length n where nums[i] represents the value of the ith node. You are also given a 2D integer array edges of length n - 1 where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the tree.
//
// You are allowed to delete some edges, splitting the tree into multiple connected components. Let the value of a component be the sum of all nums[i] for which node i is in the component.
//
// Return the maximum number of edges you can delete, such that every connected component in the tree has the same value.
//
// Example:
// Input: nums = [6,2,2,2,6], edges = [[0,1],[1,2],[1,3],[3,4]] 
// Output: 2 
// Explanation: The above figure shows how we can delete the edges [0,1] and [3,4]. The created components are nodes [0], [1,2,3] and [4]. The sum of the values in each component equals 6. It can be proven that no better deletion exists, so the answer is 2.
//
// Constraints:
// 1 <= n <= 2 * 104
// 	nums.length == n
// 	1 <= nums[i] <= 50
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	0 <= edges[i][0], edges[i][1] <= n - 1
// 	edges represents a valid tree.
//

/**
 * @param {number[]} nums
 * @param {number[][]} edges
 * @return {number}
 */
var componentValue = function(nums, edges) {
    const n = nums.length;
    const graph = Array.from({ length: n }, () => []);
    for (const [u, v] of edges) {
        graph[u].push(v);
        graph[v].push(u);
    }
    const totalSum = nums.reduce((a, b) => a + b, 0);
    let maxComponents = 1;
    for (let components = 2; components <= n; components++) {
        if (totalSum % components === 0) {
            const target = totalSum / components;
            let count = 0;
            const dfs = (node, parent) => {
                let sum = nums[node];
                for (const neighbor of graph[node]) {
                    if (neighbor !== parent) {
                        sum += dfs(neighbor, node);
                    }
                }
                if (sum === target) {
                    count++;
                    return 0;
                }   
                return sum;
            }
            dfs(0, -1);
            if (count === components) {
                maxComponents = components;
            }
        }
    }
    return maxComponents - 1;   
};
