// Source: https://leetcode.com/problems/smallest-missing-genetic-value-in-each-subtree/   |   Difficulty: Hard
//
// Problem Description:
// There is a family tree rooted at 0 consisting of n nodes numbered 0 to n - 1. You are given a 0-indexed integer array parents, where parents[i] is the parent for node i. Since node 0 is the root, parents[0] == -1.
//
// There are 105 genetic values, each represented by an integer in the inclusive range [1, 105]. You are given a 0-indexed integer array nums, where nums[i] is a distinct genetic value for node i.
//
// Return an array ans of length n where ans[i] is the smallest genetic value that is missing from the subtree rooted at node i.
//
// The subtree rooted at a node x contains node x and all of its descendant nodes.
//
// Example:
// Input: parents = [-1,0,0,2], nums = [1,2,3,4]
// Output: [5,1,1,1]
// Explanation: The answer for each subtree is calculated as follows:
// - 0: The subtree contains nodes [0,1,2,3] with values [1,2,3,4]. 5 is the smallest missing value.
// - 1: The subtree contains only node 1 with value 2. 1 is the smallest missing value.
// - 2: The subtree contains nodes [2,3] with values [3,4]. 1 is the smallest missing value.
// - 3: The subtree contains only node 3 with value 4. 1 is the smallest missing value.
//
// Constraints:
// n == parents.length == nums.length
// 	2 <= n <= 105
// 	0 <= parents[i] <= n - 1 for i != 0
// 	parents[0] == -1
// 	parents represents a valid tree.
// 	1 <= nums[i] <= 105
// 	Each nums[i] is distinct.
//

/**
 * @param {number[]} parents
 * @param {number[]} nums
 * @return {number[]}
 */
var smallestMissingValueSubtree = function(parents, nums) {
    const n = parents.length;
    const tree = new Array(n).fill(0).map(() => []);
    for (let i = 1; i < n; i++) {
        tree[parents[i]].push(i);
    }

    const ans = new Array(n).fill(1);
    const visited = new Array(100001).fill(false);
    let missingValue = 1;

    const dfs = (node) => {
        visited[nums[node]] = true;
        for (const child of tree[node]) {
            dfs(child);
        }
        while (visited[missingValue]) {
            missingValue += 1;
        }
        ans[node] = missingValue;
    }
    dfs(0);
    return ans; 
};
