// Source: https://leetcode.com/problems/minimize-hamming-distance-after-swap-operations/   |   Difficulty: Medium
//
// Problem Description:
// You are given two integer arrays, source and target, both of length n. You are also given an array allowedSwaps where each allowedSwaps[i] = [ai, bi] indicates that you are allowed to swap the elements at index ai and index bi (0-indexed) of array source. Note that you can swap elements at a specific pair of indices multiple times and in any order.
//
// The Hamming distance of two arrays of the same length, source and target, is the number of positions where the elements are different. Formally, it is the number of indices i for 0 <= i <= n-1 where source[i] != target[i] (0-indexed).
//
// Return the minimum Hamming distance of source and target after performing any amount of swap operations on array source.
//
// Example:
// Input: source = [1,2,3,4], target = [2,1,4,5], allowedSwaps = [[0,1],[2,3]]
// Output: 1
// Explanation: source can be transformed the following way:
// - Swap indices 0 and 1: source = [2,1,3,4]
// - Swap indices 2 and 3: source = [2,1,4,3]
// The Hamming distance of source and target is 1 as they differ in 1 position: index 3.
//
// Constraints:
// n == source.length == target.length
// 	1 <= n <= 105
// 	1 <= source[i], target[i] <= 105
// 	0 <= allowedSwaps.length <= 105
// 	allowedSwaps[i].length == 2
// 	0 <= ai, bi <= n - 1
// 	ai != bi
//

/**
 * @param {number[]} source
 * @param {number[]} target
 * @param {number[][]} allowedSwaps
 * @return {number}
 */
var minimumHammingDistance = function(source, target, allowedSwaps) {
    const parent = Array(source.length).fill(0).map((_, index) => index);

    function find(x) {
        if (parent[x] !== x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    function union(x, y) {
        const rootX = find(x);
        const rootY = find(y);
        if (rootX !== rootY) {
            parent[rootY] = rootX;
        }
    }

    for (const [a, b] of allowedSwaps) {
        union(a, b);
    }

    const groups = new Map();

    for (let i = 0; i < source.length; i++) {
        const root = find(i);
        if (!groups.has(root)) {
            groups.set(root, []);
        }
        groups.get(root).push(i);
    }

    let minHammingDistance = 0;

    for (const indices of groups.values()) {
        const countSource = new Map();
        const countTarget = new Map();

        for (const index of indices) {
            countSource.set(source[index], (countSource.get(source[index]) || 0) + 1);
            countTarget.set(target[index], (countTarget.get(target[index]) || 0) + 1);
        }

        for (const [num, count] of countSource.entries()) {
            const targetCount = countTarget.get(num) || 0;
            if (count > targetCount) {
                minHammingDistance += count - targetCount;
            }
        }
    }

    return minHammingDistance;
};