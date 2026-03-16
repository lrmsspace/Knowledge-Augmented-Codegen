// Source: https://leetcode.com/problems/k-items-with-the-maximum-sum/   |   Difficulty: Easy
//
// Problem Description:
// There is a bag that consists of items, each item has a number 1, 0, or -1 written on it.
//
// You are given four non-negative integers numOnes, numZeros, numNegOnes, and k.
//
// The bag initially contains:
//
//
// 	numOnes items with 1s written on them.
// 	numZeroes items with 0s written on them.
// 	numNegOnes items with -1s written on them.
//
//
// We want to pick exactly k items among the available items. Return the maximum possible sum of numbers written on the items.
//
// Example:
// Input: numOnes = 3, numZeros = 2, numNegOnes = 0, k = 2
// Output: 2
// Explanation: We have a bag of items with numbers written on them {1, 1, 1, 0, 0}. We take 2 items with 1 written on them and get a sum in a total of 2.
// It can be proven that 2 is the maximum possible sum.
//
// Constraints:
// 0 <= numOnes, numZeros, numNegOnes <= 50
// 	0 <= k <= numOnes + numZeros + numNegOnes
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int kItemsWithMaximumSum(int numOnes, int numZeros, int numNegOnes, int k) {
        // We want to maximize the sum, so we should take as many 1s as possible first, then 0s, and finally -1s if needed.
        int sum = 0;

        // Take as many 1s as possible
        int onesToTake = Math.min(numOnes, k);
        sum += onesToTake; // Each 1 contributes 1 to the sum
        k -= onesToTake; // Decrease k by the number of items taken

        // If we still need to take more items, take 0s next (they don't affect the sum)
        int zerosToTake = Math.min(numZeros, k);
        k -= zerosToTake; // Decrease k by the number of items taken

        // If we still need to take more items, take -1s last (each contributes -1 to the sum)
        int negOnesToTake = Math.min(numNegOnes, k);
        sum -= negOnesToTake; // Each -1 contributes -1 to the sum

        return sum;         
    }
}
