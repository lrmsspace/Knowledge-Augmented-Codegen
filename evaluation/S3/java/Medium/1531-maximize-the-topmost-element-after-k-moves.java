// Source: https://leetcode.com/problems/maximize-the-topmost-element-after-k-moves/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array nums representing the contents of a pile, where nums[0] is the topmost element of the pile.
//
// In one move, you can perform either of the following:
//
//
// 	If the pile is not empty, remove the topmost element of the pile.
// 	If there are one or more removed elements, add any one of them back onto the pile. This element becomes the new topmost element.
//
//
// You are also given an integer k, which denotes the total number of moves to be made.
//
// Return the maximum value of the topmost element of the pile possible after exactly k moves. In case it is not possible to obtain a non-empty pile after k moves, return -1.
//
// Example:
// Input: nums = [5,2,2,4,0,6], k = 4
// Output: 5
// Explanation:
// One of the ways we can end with 5 at the top of the pile after 4 moves is as follows:
// - Step 1: Remove the topmost element = 5. The pile becomes [2,2,4,0,6].
// - Step 2: Remove the topmost element = 2. The pile becomes [2,4,0,6].
// - Step 3: Remove the topmost element = 2. The pile becomes [4,0,6].
// - Step 4: Add 5 back onto the pile. The pile becomes [5,4,0,6].
// Note that this is not the only way to end with 5 at the top of the pile. It can be shown that 5 is the largest answer possible after 4 moves.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i], k <= 109
//
// Helpful references (internal KB):
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Josephus Problem (number, simulation, recursion)
//   • When to use: Use when determining the survivor's position in a circular game where every k-th person is eliminated, especially for large N where direct simulation is too slow.
//   • Idea: This algorithm finds the position of the last remaining person in the Josephus problem by iteratively reducing the problem size using a recursive formula and modulo arithmetic. It achieves an optimized time complexity of O(k log n).
//   • Invariants: The number of remaining elements decreases in each recursive step.; The relative order of the remaining elements is preserved throughout the process.
//   • Tips: Handle the base case where n < k separately to avoid infinite loops or incorrect calculations.; Use 0-indexing for simpler modulo arithmetic in the recursive formulas.
//   • Pitfalls: Incorrectly handling index shifts after elements are removed can lead to wrong results.; Forgetting the base case n < k can lead to infinite recursion or incorrect behavior.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int maximumTop(int[] nums, int k) {
        int n = nums.length;
        if (k == 0) {
            return nums[0];
        }
        if (n == 1) {
            return k % 2 == 0 ? nums[0] : -1;
        }
        if (k < n) {
            int max = -1;
            for (int i = 0; i < k - 1; i++) {
                max = Math.max(max, nums[i]);
            }
            return Math.max(max, nums[k]);
        } else {
            int max = -1;
            for (int i = 0; i < n - 1; i++) {
                max = Math.max(max, nums[i]);
            }
            return max;
        }           
    }
}
