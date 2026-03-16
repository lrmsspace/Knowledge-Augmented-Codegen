// Source: https://leetcode.com/problems/number-of-laser-beams-in-a-bank/   |   Difficulty: Medium
//
// Problem Description:
// Anti-theft security devices are activated inside a bank. You are given a 0-indexed binary string array bank representing the floor plan of the bank, which is an m x n 2D matrix. bank[i] represents the ith row, consisting of '0's and '1's. '0' means the cell is empty, while'1' means the cell has a security device.
//
// There is one laser beam between any two security devices if both conditions are met:
//
//
// 	The two devices are located on two different rows: r1 and r2, where r1 < r2.
// 	For each row i where r1 < i < r2, there are no security devices in the ith row.
//
//
// Laser beams are independent, i.e., one beam does not interfere nor join with another.
//
// Return the total number of laser beams in the bank.
//
// Example:
// Input: bank = ["011001","000000","010100","001000"]
// Output: 8
// Explanation: Between each of the following device pairs, there is one beam. In total, there are 8 beams:
//  * bank[0][1] -- bank[2][1]
//  * bank[0][1] -- bank[2][3]
//  * bank[0][2] -- bank[2][1]
//  * bank[0][2] -- bank[2][3]
//  * bank[0][5] -- bank[2][1]
//  * bank[0][5] -- bank[2][3]
//  * bank[2][1] -- bank[3][2]
//  * bank[2][3] -- bank[3][2]
// Note that there is no beam between any device on the 0th row with any on the 3rd row.
// This is because the 2nd row contains security devices, which breaks the second condition.
//
// Constraints:
// m == bank.length
// 	n == bank[i].length
// 	1 <= m, n <= 500
// 	bank[i][j] is either '0' or '1'.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Number of paths of fixed length / Shortest paths of fixed length (graph, matrix, matrix-exp, counting)
//   • When to use: Use when needing to count the number of paths of a specific length between all pairs of vertices in a graph, or to find reachability in a fixed number of steps.
//   • Idea: This algorithm leverages matrix exponentiation to find the number of paths of a fixed length `k` between all pairs of vertices in a graph. Each matrix multiplication step extends path lengths by one, resulting in an O(N^3 log K) time complexity for an N-vertex graph.
//   • Invariants: After `m` matrix multiplications, `C_m[i][j]` stores the number of paths of length `m` from `i` to `j`.; The initial adjacency matrix `G` remains constant throughout the exponentiation process.
//   • Tips: Represent the graph as an adjacency matrix where `G[i][j]` is the number of direct edges.; Matrix multiplication `C_k * G` yields `C_{k+1}` for path counts.
//   • Pitfalls: Standard matrix multiplication is O(N^3), leading to O(N^3 log K) overall time complexity.; Memory usage is O(N^2) for storing matrices, which can be prohibitive for very large graphs.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int numberOfBeams(String[] bank) {
        int prevDevices = 0;
        int totalBeams = 0;

        for (String row : bank) {
            int currentDevices = 0;
            for (char cell : row.toCharArray()) {
                if (cell == '1') {
                    currentDevices++;
                }
            }

            if (currentDevices > 0) {
                totalBeams += prevDevices * currentDevices;
                prevDevices = currentDevices;
            }
        }

        return totalBeams;          
    }
}
