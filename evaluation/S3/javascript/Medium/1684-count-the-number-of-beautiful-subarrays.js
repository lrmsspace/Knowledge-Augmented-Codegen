// Source: https://leetcode.com/problems/count-the-number-of-beautiful-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums. In one operation, you can:
//
//
// 	Choose two different indices i and j such that 0 <= i, j < nums.length.
// 	Choose a non-negative integer k such that the kth bit (0-indexed) in the binary representation of nums[i] and nums[j] is 1.
// 	Subtract 2k from nums[i] and nums[j].
//
//
// A subarray is beautiful if it is possible to make all of its elements equal to 0 after applying the above operation any number of times (including zero).
//
// Return the number of beautiful subarrays in the array nums.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Note: Subarrays where all elements are initially 0 are considered beautiful, as no operation is needed.
//
// Example:
// Input: nums = [4,3,1,2,4]
// Output: 2
// Explanation: There are 2 beautiful subarrays in nums: [4,3,1,2,4] and [4,3,1,2,4].
// - We can make all elements in the subarray [3,1,2] equal to 0 in the following way:
//   - Choose [3, 1, 2] and k = 1. Subtract 21 from both numbers. The subarray becomes [1, 1, 0].
//   - Choose [1, 1, 0] and k = 0. Subtract 20 from both numbers. The subarray becomes [0, 0, 0].
// - We can make all elements in the subarray [4,3,1,2,4] equal to 0 in the following way:
//   - Choose [4, 3, 1, 2, 4] and k = 2. Subtract 22 from both numbers. The subarray becomes [0, 3, 1, 2, 0].
//   - Choose [0, 3, 1, 2, 0] and k = 0. Subtract 20 from both numbers. The subarray becomes [0, 2, 0, 2, 0].
//   - Choose [0, 2, 0, 2, 0] and k = 1. Subtract 21 from both numbers. The subarray becomes [0, 0, 0, 0, 0].
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 106
//
// Helpful references (internal KB):
// - Disjoint Sparse Table tutorial (array, ds, number, sparse-table, counting)
//   • When to use: Use when you need to answer range queries on a static array in O(1) time, after an initial O(N log N) preprocessing phase. It is particularly efficient for associative operations like sum, min, or max.
//   • Idea: A Disjoint Sparse Table is a data structure that precomputes results for all possible range queries on a static array using a hierarchical block decomposition. It achieves O(N log N) construction time and space complexity, enabling O(1) query time for associative operations.
//   • Invariants: ST[k][i] stores the result for a range of length 2^k starting at i within its block.; For any level k, blocks are disjoint, but ranges within ST[k] can overlap with ranges in ST[k-1].
//   • Tips: Precompute log2 values or highest set bit for efficient level determination.; Ensure the operation (e.g., sum, min, max) is associative for correct combination.
//   • Pitfalls: Not suitable for arrays that require updates, as it's a static data structure.; Only works for associative operations; non-associative operations cannot be combined this way.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var beautifulSubarrays = function(nums) {
    let prefixXor = 0;
    const freqMap = new Map();
    freqMap.set(0, 1); // Base case: there's one way to have a prefix XOR of 0 (the empty subarray)
    
    let beautifulCount = 0;
    
    for (const num of nums) {
        prefixXor ^= num; // Update the prefix XOR
        
        // If we've seen this prefix XOR before, it means the subarray between the previous index and the current index has an XOR of 0
        if (freqMap.has(prefixXor)) {
            beautifulCount += freqMap.get(prefixXor);
            freqMap.set(prefixXor, freqMap.get(prefixXor) + 1);
        } else {
            freqMap.set(prefixXor, 1);
        }
    }
    
    return beautifulCount;
};
