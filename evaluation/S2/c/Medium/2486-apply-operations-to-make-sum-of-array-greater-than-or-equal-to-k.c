// Source: https://leetcode.com/problems/apply-operations-to-make-sum-of-array-greater-than-or-equal-to-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given a positive integer k. Initially, you have an array nums = [1].
//
// You can perform any of the following operations on the array any number of times (possibly zero):
//
//
// 	Choose any element in the array and increase its value by 1.
// 	Duplicate any element in the array and add it to the end of the array.
//
//
// Return the minimum number of operations required to make the sum of elements of the final array greater than or equal to k.
//
// Example:
// Input: k = 11
//
// Output: 5
//
// Explanation:
//
// We can do the following operations on the array nums = [1]:
//
//
// 	Increase the element by 1 three times. The resulting array is nums = [4].
// 	Duplicate the element two times. The resulting array is nums = [4,4,4].
//
//
// The sum of the final array is 4 + 4 + 4 = 12 which is greater than or equal to k = 11.
// The total number of operations performed is 3 + 2 = 5.
//
// Constraints:
// 1 <= k <= 105
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Linear Diophantine Equation (number, greedy)
//   • When to use: Use when a problem can be solved by making the locally optimal choice at each step, hoping this leads to a globally optimal solution. This strategy is often simpler and faster than dynamic programming.
//   • Idea: The greedy algorithm makes the best choice at each stage with the hope of finding a global optimum, without reconsidering previous choices. Its time complexity is typically O(N log N) or O(N).
//   • Invariants: At each step, the chosen element is the best available according to the greedy criterion.; The partial solution constructed so far remains optimal for the subproblem considered.
//   • Tips: Prove correctness by exchange argument or induction.; Sort input data if it helps identify the greedy choice.
//   • Pitfalls: Failing to prove the greedy choice property.; Making a locally optimal choice that prevents a global optimum.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minOperations(int k) {
    int operations = 0;
    long long sum = 1; // Start with the initial array [1]
    long long currentValue = 1; // The value of the last element in the array

    while (sum < k) {
        if (currentValue * 2 <= k - sum) {
            // If doubling the current value does not exceed the needed sum, duplicate it
            sum += currentValue; // Add the duplicated value to the sum
            currentValue *= 2; // Update the current value to its double
            operations++; // Count the duplication operation
        } else {
            // Otherwise, increase the current value by 1
            sum += 1; // Add 1 to the sum
            currentValue += 1; // Increase the current value by 1
            operations++; // Count the increment operation
        }
    }

    return operations;      
}
