// Source: https://leetcode.com/problems/move-zeroes/   |   Difficulty: Easy
//
// Problem Description:
// Given an integer array nums, move all 0's to the end of it while maintaining the relative order of the non-zero elements.
//
// Note that you must do this in-place without making a copy of the array.
//
// Example:
// Input: nums = [0,1,0,3,12]
// Output: [1,3,12,0,0]
//
// Constraints:
// 1 <= nums.length <= 104
// 	-231 <= nums[i] <= 231 - 1
//
//
//  
// Follow up: Could you minimize the total number of operations done?
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: Use when needing to uniquely encode or decode a labeled tree into a sequence of numbers, or to count the number of spanning trees for a complete graph. It's also useful for problems involving tree properties like degree sequences.
//   • Idea: Prüfer code is a unique sequence representing a labeled tree, allowing conversion between a tree and a sequence of numbers. Its generation and decoding typically involve an iterative process of finding and removing leaves, achieving O(N log N) or O(N) complexity with optimized leaf finding.
//   • Invariants: The Prüfer sequence always has N-2 elements for an N-vertex tree.; Each vertex's degree is correctly maintained throughout the process.
//   • Tips: Maintain a degree array to efficiently find leaves.; Use a min-priority queue or a two-pointer approach for finding the smallest leaf.
//   • Pitfalls: Off-by-one errors in sequence length or vertex indexing.; Incorrectly handling the last two vertices during decoding.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    void moveZeroes(vector<int>& nums) {
        int n = nums.size();
        int j = 0; // Pointer for the position of the next non-zero element

        // Move all non-zero elements to the front of the array
        for (int i = 0; i < n; ++i) {
            if (nums[i] != 0) {
                nums[j++] = nums[i]; // Place non-zero element at index j and increment j
            }
        }

        // Fill the remaining positions with zeros
        for (int i = j; i < n; ++i) {
            nums[i] = 0;
        }           
    }
};
