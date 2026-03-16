// Source: https://leetcode.com/problems/calculate-score-after-performing-instructions/   |   Difficulty: Medium
//
// Problem Description:
// You are given two arrays, instructions and values, both of size n.
//
// You need to simulate a process based on the following rules:
//
//
// 	You start at the first instruction at index i = 0 with an initial score of 0.
// 	If instructions[i] is "add":
// 	
// 		Add values[i] to your score.
// 		Move to the next instruction (i + 1).
// 	
// 	
// 	If instructions[i] is "jump":
// 	
// 		Move to the instruction at index (i + values[i]) without modifying your score.
// 	
// 	
//
//
// The process ends when you either:
//
//
// 	Go out of bounds (i.e., i < 0 or i >= n), or
// 	Attempt to revisit an instruction that has been previously executed. The revisited instruction is not executed.
//
//
// Return your score at the end of the process.
//
// Example:
// Input: instructions = ["jump","add","add","jump","add","jump"], values = [2,1,3,1,-2,-3]
//
// Output: 1
//
// Explanation:
//
// Simulate the process starting at instruction 0:
//
//
// 	At index 0: Instruction is "jump", move to index 0 + 2 = 2.
// 	At index 2: Instruction is "add", add values[2] = 3 to your score and move to index 3. Your score becomes 3.
// 	At index 3: Instruction is "jump", move to index 3 + 1 = 4.
// 	At index 4: Instruction is "add", add values[4] = -2 to your score and move to index 5. Your score becomes 1.
// 	At index 5: Instruction is "jump", move to index 5 + (-3) = 2.
// 	At index 2: Already visited. The process ends.
//
// Constraints:
// n == instructions.length == values.length
// 	1 <= n <= 105
// 	instructions[i] is either "add" or "jump".
// 	-105 <= values[i] <= 105
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Bit manipulation (number, enumeration, simulation)
//   • When to use: When problems involve manipulating individual bits of numbers, representing sets as bitmasks, or optimizing operations on powers of two. It is also useful for certain combinatorics and dynamic programming problems.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators. This technique is often used to optimize computations, manage boolean flags efficiently, or represent subsets, typically achieving O(1) complexity for fixed-size integers.
//   • Invariants: Each bit in the mask accurately reflects the inclusion or exclusion status of its corresponding element.; Bitwise operations maintain the integrity of unaffected bits.
//   • Tips: Use (1 << k) to create a mask with the k-th bit set.; n & (n-1) clears the least significant set bit.
//   • Pitfalls: Incorrect operator precedence can lead to subtle bugs.; Mixing signed and unsigned integers in bitwise operations can yield unexpected results.
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long calculateScore(vector<string>& instructions, vector<int>& values) {
        int n = instructions.size();
        vector<bool> visited(n, false);
        long long score = 0;
        int i = 0;

        while (i >= 0 && i < n && !visited[i]) {
            visited[i] = true;
            if (instructions[i] == "add") {
                score += values[i];
                i++;
            } else { // "jump"
                i += values[i];
            }
        }

        return score;           
    }
};
