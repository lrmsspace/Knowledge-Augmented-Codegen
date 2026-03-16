// Source: https://leetcode.com/problems/largest-component-size-by-common-factor/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer array of unique positive integers nums. Consider the following graph:
//
//
// 	There are nums.length nodes, labeled nums[0] to nums[nums.length - 1],
// 	There is an undirected edge between nums[i] and nums[j] if nums[i] and nums[j] share a common factor greater than 1.
//
//
// Return the size of the largest connected component in the graph.
//
// Example:
// Input: nums = [4,6,15,35]
// Output: 4
//
// Constraints:
// 1 <= nums.length <= 2 * 104
// 	1 <= nums[i] <= 105
// 	All the values of nums are unique.
//

/**
 * @param {number[]} nums
 * @return {number}
 */
var largestComponentSize = function(nums) {
    const maxNum = Math.max(...nums);
    const parent = new Array(maxNum + 1).fill(0).map((_, index) => index);
    const size = new Array(maxNum + 1).fill(1);

    const find = (x) => {
        if (parent[x] !== x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    };

    const union = (x, y) => {
        const rootX = find(x);
        const rootY = find(y);
        if (rootX !== rootY) {
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    };

    for (const num of nums) {
        for (let factor = 2; factor * factor <= num; factor++) {
            if (num % factor === 0) {
                union(num, factor);
                union(num, num / factor);
            }
        }
    }
    const componentSize = new Map();
    let maxSize = 1;
    for (const num of nums) {
        const root = find(num);
        componentSize.set(root, (componentSize.get(root) || 0) + 1);
        maxSize = Math.max(maxSize, componentSize.get(root));
    }
    return maxSize; 
};
