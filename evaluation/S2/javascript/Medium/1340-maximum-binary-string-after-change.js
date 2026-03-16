// Source: https://leetcode.com/problems/maximum-binary-string-after-change/   |   Difficulty: Medium
//
// Problem Description:
// You are given a binary string binary consisting of only 0's or 1's. You can apply each of the following operations any number of times:
//
//
//  Operation 1: If the number contains the substring "00", you can replace it with "10".
//
//  
//   For example, "00010" -> "10010"
//  
//  
//  Operation 2: If the number contains the substring "10", you can replace it with "01".
//  
//   For example, "00010" -> "00001"
//  
//  
//
//
// Return the maximum binary string you can obtain after any number of operations. Binary string x is greater than binary string y if x's decimal representation is greater than y's decimal representation.
//
// Example:
// Input: binary = "000110"
// Output: "111011"
// Explanation: A valid transformation sequence can be:
// "000110" -> "000101" 
// "000101" -> "100101" 
// "100101" -> "110101" 
// "110101" -> "110011" 
// "110011" -> "111011"
//
// Constraints:
// 1 <= binary.length <= 105
//  binary consist of '0' and '1'.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Longest Increasing Subsequence (array, dp-1d, binary-search)
//   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order. It is often applied to optimization problems involving ordered subsets.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence where all elements are sorted in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search optimization, or O(N^2) using basic DP.
//   • Invariants: The 'tails' array always stores the smallest ending element for all increasing subsequences of a given length.; The 'tails' array remains sorted in strictly increasing order throughout the algorithm's execution.
//   • Tips: The O(N log N) approach uses a 'tails' array to store the smallest tail of all increasing subsequences of length 'i+1'.; Binary search is crucial for efficiently finding the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing subsequence with contiguous subarray or substring.; Incorrectly updating or searching in the 'tails' array, leading to wrong lengths or values.
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} binary
 * @return {string}
 */
var maximumBinaryString = function(binary) {
    const chars = binary.split('');
    let zeroCount = 0;
    for (const char of chars) {
        if (char === '0') {
            zeroCount++;
        }
    }
    if (zeroCount === 0) {
        return binary;
    }
    let onesCount = chars.length - zeroCount;
    let result = '';
    for (let i = 0; i < onesCount; i++) {
        result += '1';
    }
    for (let i = 0; i < zeroCount - 1; i++) {
        result += '1';
    }
    result += '0';
    for (let i = 0; i < onesCount; i++) {
        result += '1';
    }
    return result;
};
