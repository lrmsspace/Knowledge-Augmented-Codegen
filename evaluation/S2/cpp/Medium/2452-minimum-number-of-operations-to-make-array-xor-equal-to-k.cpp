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
// - Bit manipulation (number, counting)
//   • When to use: When you need to manipulate individual bits within an integer, optimize space, or perform fast operations on boolean flags or small sets. It's ideal for low-level control and specific integer property checks.
//   • Idea: Bit manipulation involves directly operating on the binary representation of numbers using bitwise operators like AND, OR, XOR, NOT, and shifts. These operations allow for efficient setting, clearing, flipping, and checking of individual bits, typically with O(1) complexity per operation.
//   • Invariants: The state of any bit `i` where `i != x` is preserved during an operation on the `x`-th bit.; After `n = n | (1 << x)`, the `x`-th bit of `n` is 1.
//   • Tips: Use `1 << x` to create a mask for the x-th bit.; Understand the difference between `&`, `|`, `^`, `~`, `<<`, `>>` operators.
//   • Pitfalls: Incorrect operator precedence (e.g., `&` vs `&&`).; Off-by-one errors with bit indices (0-indexed vs 1-indexed).
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Sprague-Grundy theorem. Nim (array, number, game-theory, prefix-xor)
//   • When to use: Use when analyzing impartial games with perfect information and no draws, especially to determine winning/losing states or to find a winning strategy. It's particularly useful for games that can be reduced to Nim.
//   • Idea: The Sprague-Grundy theorem states that every impartial game under the normal play convention is equivalent to a Nim pile of a certain size (its nim-value or grundy number). For Nim, a position is a winning position if and only if the XOR sum of all pile sizes is non-zero, allowing for O(N) classification.
//   • Invariants: The XOR sum of the pile sizes (nim-sum) represents the game's current nim-value.; If the nim-sum is zero, any valid move will result in a non-zero nim-sum for the opponent.
//   • Tips: Understand the definition of impartial games and their properties.; Calculate the XOR sum of game components to determine the nim-sum.
//   • Pitfalls: Confusing impartial games with partisan games where players have different moves.; Incorrectly calculating the XOR sum, leading to wrong state classifications.
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
        int n = nums.size();
        int xorSum = 0;
        for (int num : nums) {
            xorSum ^= num;
        }
        int target = xorSum ^ k;
        int operations = 0;
        for (int num : nums) {
            if ((num ^ target) < num) {
                operations++;
            }
        }
        return operations;          
    }
};
