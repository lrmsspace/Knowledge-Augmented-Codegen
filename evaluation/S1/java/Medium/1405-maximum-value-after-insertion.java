// Source: https://leetcode.com/problems/maximum-value-after-insertion/   |   Difficulty: Medium
//
// Problem Description:
// You are given a very large integer n, represented as a string,​​​​​​ and an integer digit x. The digits in n and the digit x are in the inclusive range [1, 9], and n may represent a negative number.
//
// You want to maximize n's numerical value by inserting x anywhere in the decimal representation of n​​​​​​. You cannot insert x to the left of the negative sign.
//
//
// 	For example, if n = 73 and x = 6, it would be best to insert it between 7 and 3, making n = 763.
// 	If n = -55 and x = 2, it would be best to insert it before the first 5, making n = -255.
//
//
// Return a string representing the maximum value of n​​​​​​ after the insertion.
//
// Example:
// Input: n = "99", x = 9
// Output: "999"
// Explanation: The result is the same regardless of where you insert 9.
//
// Constraints:
// 1 <= n.length <= 105
// 	1 <= x <= 9
// 	The digits in n​​​ are in the range [1, 9].
// 	n is a valid representation of an integer.
// 	In the case of a negative n,​​​​​​ it will begin with '-'.
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use when you need to efficiently represent all distinct substrings of a string, or perform various string operations like counting unique substrings, finding occurrences, or string matching in an online fashion.
//   • Idea: A suffix automaton is a powerful data structure that represents all distinct substrings of a given string in a compact form, typically as a Directed Acyclic Word Graph (DAWG). It can be constructed in linear time O(N) and space O(N) for a string of length N.
//   • Invariants: Each state in the automaton represents a set of substrings that share the same end-positions in the original string.; For any state `v`, `len(v)` is the length of the longest string represented by `v`.
//   • Tips: Understand the properties of `len` (length of the longest string in a state) and `link` (suffix link to the longest proper suffix).; The construction is online, processing characters one by one from left to right.
//   • Pitfalls: Incorrectly handling the `link` updates, especially when cloning states during construction.; Forgetting to update the `last` pointer after each character addition step.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public String maxValue(String n, int x) {
        StringBuilder result = new StringBuilder();
        char xChar = (char) (x + '0');
        boolean inserted = false;

        if (n.charAt(0) == '-') {
            result.append('-');
            for (int i = 1; i < n.length(); i++) {
                char currentChar = n.charAt(i);
                if (!inserted && currentChar - '0' > x) {
                    result.append(xChar);
                    inserted = true;
                }
                result.append(currentChar);
            }
        } else {
            for (int i = 0; i < n.length(); i++) {
                char currentChar = n.charAt(i);
                if (!inserted && currentChar - '0' < x) {
                    result.append(xChar);
                    inserted = true;
                }
                result.append(currentChar);
            }
        }

        if (!inserted) {
            result.append(xChar);
        }

        return result.toString();           
    }
}
