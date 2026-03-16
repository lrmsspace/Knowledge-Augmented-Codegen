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
// - 0-1 BFS (graph, array, dijkstra, bfs)
//   • When to use: Use when finding the shortest path in a graph where all edge weights are either 0 or 1. It efficiently determines minimum costs without a full priority queue.
//   • Idea: A specialized Breadth-First Search variant that finds shortest paths in graphs with only 0 or 1 edge weights. It uses a deque to process 0-weight edges before 1-weight edges, achieving O(V+E) time complexity.
//   • Invariants: All nodes currently in the deque have a distance value of either `k` or `k+1` for some integer `k`.; Nodes pushed to the front of the deque always have a distance equal to the current node's distance.
//   • Tips: Utilize a deque to maintain the order of processing nodes.; Add nodes reached via 0-weight edges to the front of the deque.
//   • Pitfalls: Incorrectly using a standard queue instead of a deque.; Failing to initialize distances to infinity for all nodes except the source.
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
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
    const n = binary.length;
    let zeroCount = 0;
    let firstZeroIndex = -1;
    
    for (let i = 0; i < n; i++) {
        if (binary[i] === '0') {
            zeroCount++;
            if (firstZeroIndex === -1) {
                firstZeroIndex = i;
            }
        }
    }
    
    if (zeroCount <= 1) {
        return binary;
    }
    
    const result = binary.split('');
    result[firstZeroIndex + zeroCount - 1] = '0';
    for (let i = firstZeroIndex; i < firstZeroIndex + zeroCount - 1; i++) {
        result[i] = '1';
    }
    
    return result.join('');
};
