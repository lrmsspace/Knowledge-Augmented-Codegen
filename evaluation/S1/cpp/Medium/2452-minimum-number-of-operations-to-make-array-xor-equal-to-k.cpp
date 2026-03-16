// Source: https://leetcode.com/problems/minimum-number-of-operations-to-make-array-xor-equal-to-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums and a positive integer k.
//
// You can apply the following operation on the array any number of times:
//
//
// 	Choose any element of the array and flip a bit in its binary representation. Flipping a bit means changing a 0 to 1 or vice versa.
//
//
// Return the minimum number of operations required to make the bitwise XOR of all elements of the final array equal to k.
//
// Note that you can flip leading zero bits in the binary representation of elements. For example, for the number (101)2 you can flip the fourth bit and obtain (1101)2.
//
// Example:
// Input: nums = [2,1,3,4], k = 1
// Output: 2
// Explanation: We can do the following operations:
// - Choose element 2 which is 3 == (011)2, we flip the first bit and we obtain (010)2 == 2. nums becomes [2,1,2,4].
// - Choose element 0 which is 2 == (010)2, we flip the third bit and we obtain (110)2 = 6. nums becomes [6,1,2,4].
// The XOR of elements of the final array is (6 XOR 1 XOR 2 XOR 4) == 1 == k.
// It can be shown that we cannot make the XOR equal to k in less than 2 operations.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 106
// 	0 <= k <= 106
//
// Helpful references (internal KB):
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
// - Bit manipulation (number, counting)
//   • When to use: When you need to manipulate individual bits within an integer, optimize space, or perform fast operations on boolean flags or small sets. It's ideal for low-level control and specific integer property checks.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators like AND, OR, XOR, NOT, and shifts. These operations allow for efficient setting, clearing, flipping, and checking of individual bits, typically with O(1) complexity per operation.
//   • Invariants: The state of any bit `i` where `i != x` is preserved during an operation on the `x`-th bit.; After `n = n | (1 << x)`, the `x`-th bit of `n` is 1.
//   • Tips: Use `1 << x` to create a mask for the x-th bit.; Understand the difference between `&`, `|`, `^`, `~`, `<<`, `>>` operators.
//   • Pitfalls: Incorrect operator precedence (e.g., `&` vs `&&`).; Off-by-one errors with bit indices (0-indexed vs 1-indexed).
// - Stars and bars (number, counting)
//   • When to use: When counting the number of ways to distribute 'n' identical items into 'k' distinct containers, or finding the number of non-negative integer solutions to an equation x1 + ... + xk = n.
//   • Idea: A combinatorial technique to count arrangements of identical items into distinct bins, or non-negative integer solutions to a sum, by modeling them as permutations of 'n' stars and 'k-1' bars. It typically has a time complexity of O(1) after binomial coefficient precomputation, or O(min(n, k)) for direct calculation.
//   • Invariants: The total number of stars remains 'n' throughout the arrangement.; The total number of bars remains 'k-1' throughout the arrangement.
//   • Tips: Clearly identify 'n' (identical objects) and 'k' (distinct bins/variables).; Remember the formula: C(n + k - 1, k - 1) or C(n + k - 1, n).
//   • Pitfalls: Confusing identical objects with distinct objects.; Incorrectly identifying 'n' or 'k' in the problem statement.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        int xorAll = 0;
        for (int num : nums) {
            xorAll ^= num;
        }
        int target = xorAll ^ k;
        int operations = 0;

        for (int bit = 0; bit <= 20; ++bit) {
            int bitMask = 1 << bit;
            if ((target & bitMask) == 0) {
                continue; // No need to change this bit
            }

            int countOnes = 0;
            for (int num : nums) {
                if (num & bitMask) {
                    countOnes++;
                }
            }
            int countZeros = nums.size() - countOnes;

            // To flip this bit in the final XOR, we can either:
            // 1. Flip all 1s to 0s (cost: countOnes)
            // 2. Flip all 0s to 1s (cost: countZeros)
            operations += (countOnes < countZeros) ? countOnes : countZeros;
        }

        return operations;          
    }
};
