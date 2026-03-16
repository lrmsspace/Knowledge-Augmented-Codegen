// Source: https://leetcode.com/problems/count-connected-components-in-lcm-graph/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums of size n and a positive integer threshold.
//
// There is a graph consisting of n nodes with the ith node having a value of nums[i]. Two nodes i and j in the graph are connected via an undirected edge if lcm(nums[i], nums[j]) <= threshold.
//
// Return the number of connected components in this graph.
//
// A connected component is a subgraph of a graph in which there exists a path between any two vertices, and no vertex of the subgraph shares an edge with a vertex outside of the subgraph.
//
// The term lcm(a, b) denotes the least common multiple of a and b.
//
// Example:
// Input: nums = [2,4,8,3,9], threshold = 5
//
// Output: 4
//
// Explanation: 
//
//
//
//  
//
// The four connected components are (2, 4), (3), (8), (9).
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
// 	All elements of nums are unique.
// 	1 <= threshold <= 2 * 105
//

/**
 * @param {number[]} nums
 * @param {number} threshold
 * @return {number}
 */
var countComponents = function(nums, threshold) {
    const parent = new Map();
    const rank = new Map();
    const find = (x) => {
        if (parent.get(x) !== x) {
            parent.set(x, find(parent.get(x)));
        }
        return parent.get(x);
    }
    const union = (x, y) => {
        const rootX = find(x);
        const rootY = find(y);
        if (rootX !== rootY) {
            if (rank.get(rootX) > rank.get(rootY)) {
                parent.set(rootY, rootX);
            } else if (rank.get(rootX) < rank.get(rootY)) {
                parent.set(rootX, rootY);
            } else {
                parent.set(rootY, rootX);
                rank.set(rootX, rank.get(rootX) + 1);
            }
        }
    }
    const numSet = new Set(nums);
    for (const num of nums) {
        parent.set(num, num);
        rank.set(num, 0);
    }
    for (let i = threshold + 1; i <= 2 * 10 ** 5; i++) {
        let first = -1;
        for (let multiple = i; multiple <= 10 ** 9; multiple += i) {
            if (numSet.has(multiple)) {
                if (first === -1) {
                    first = multiple;
                } else {
                    union(first, multiple);
                }
            }
        }
    }
    const components = new Set();
    for (const num of nums) {
        components.add(find(num));
    }
    return components.size;
};
