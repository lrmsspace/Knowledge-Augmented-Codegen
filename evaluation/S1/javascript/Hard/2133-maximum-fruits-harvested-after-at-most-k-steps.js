// Source: https://leetcode.com/problems/maximum-fruits-harvested-after-at-most-k-steps/   |   Difficulty: Hard
//
// Problem Description:
// Fruits are available at some positions on an infinite x-axis. You are given a 2D integer array fruits where fruits[i] = [positioni, amounti] depicts amounti fruits at the position positioni. fruits is already sorted by positioni in ascending order, and each positioni is unique.
//
// You are also given an integer startPos and an integer k. Initially, you are at the position startPos. From any position, you can either walk to the left or right. It takes one step to move one unit on the x-axis, and you can walk at most k steps in total. For every position you reach, you harvest all the fruits at that position, and the fruits will disappear from that position.
//
// Return the maximum total number of fruits you can harvest.
//
// Example:
// Input: fruits = [[2,8],[6,3],[8,6]], startPos = 5, k = 4
// Output: 9
// Explanation: 
// The optimal way is to:
// - Move right to position 6 and harvest 3 fruits
// - Move right to position 8 and harvest 6 fruits
// You moved 3 steps and harvested 3 + 6 = 9 fruits in total.
//
// Constraints:
// 1 <= fruits.length <= 105
// 	fruits[i].length == 2
// 	0 <= startPos, positioni <= 2 * 105
// 	positioni-1 < positioni for any i > 0 (0-indexed)
// 	1 <= amounti <= 104
// 	0 <= k <= 2 * 105
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
//   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
//   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
//   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
//   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} fruits
 * @param {number} startPos
 * @param {number} k
 * @return {number}
 */
var maxTotalFruits = function(fruits, startPos, k) {
    const n = fruits.length;
    const prefixSum = new Array(n + 1).fill(0);

    for (let i = 0; i < n; i++) {
        prefixSum[i + 1] = prefixSum[i] + fruits[i][1];
    }

    const getFruits = (left, right) => {
        const leftIdx = bisectLeft(fruits, left);
        const rightIdx = bisectRight(fruits, right);
        return prefixSum[rightIdx] - prefixSum[leftIdx];
    };

    let maxFruits = 0;

    for (let leftSteps = 0; leftSteps <= k; leftSteps++) {
        const rightSteps = k - 2 * leftSteps;
        if (rightSteps < 0) continue;

        maxFruits = Math.max(maxFruits, getFruits(startPos - leftSteps, startPos + rightSteps));
    }

    for (let rightSteps = 0; rightSteps <= k; rightSteps++) {
        const leftSteps = k - 2 * rightSteps;
        if (leftSteps < 0) continue;

        maxFruits = Math.max(maxFruits, getFruits(startPos - leftSteps, startPos + rightSteps));
    }

    return maxFruits;
};
