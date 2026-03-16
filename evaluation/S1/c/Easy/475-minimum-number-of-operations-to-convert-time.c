// Source: https://leetcode.com/problems/minimum-number-of-operations-to-convert-time/   |   Difficulty: Easy
//
// Problem Description:
// You are given two strings current and correct representing two 24-hour times.
//
// 24-hour times are formatted as "HH:MM", where HH is between 00 and 23, and MM is between 00 and 59. The earliest 24-hour time is 00:00, and the latest is 23:59.
//
// In one operation you can increase the time current by 1, 5, 15, or 60 minutes. You can perform this operation any number of times.
//
// Return the minimum number of operations needed to convert current to correct.
//
// Example:
// Input: current = "02:30", correct = "04:35"
// Output: 3
// Explanation:
// We can convert current to correct in 3 operations as follows:
// - Add 60 minutes to current. current becomes "03:30".
// - Add 60 minutes to current. current becomes "04:30".
// - Add 5 minutes to current. current becomes "04:35".
// It can be proven that it is not possible to convert current to correct in fewer than 3 operations.
//
// Constraints:
// current and correct are in the format "HH:MM"
// 	current <= correct
//
// Helpful references (internal KB):
// - Scheduling jobs on two machines (array, greedy)
//   • When to use: Use when optimizing the order of a sequence of tasks on two machines to minimize total idle time or makespan. It is typically applied when a greedy exchange argument can prove optimality.
//   • Idea: This algorithm determines an optimal sequence for jobs on two machines by iteratively applying a greedy choice, often proven optimal via an exchange argument. It typically achieves an optimal solution in polynomial time, commonly O(N log N) or O(N^2).
//   • Invariants: The relative order of jobs already placed in the schedule is optimal.; The total idle time for the current prefix of scheduled jobs is correctly calculated.
//   • Tips: Focus on the local effect of swapping adjacent elements to derive the greedy criterion.; Identify a metric (e.g., total idle time or makespan) that changes predictably with swaps.
//   • Pitfalls: The greedy choice might not be globally optimal for problems with more than two machines.; Incorrectly defining the cost function for idle time or makespan can lead to suboptimal solutions.
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int convertTime(char* current, char* correct) {
    int curr_hours = (current[0] - '0') * 10 + (current[1] - '0');
    int curr_minutes = (current[3] - '0') * 10 + (current[4] - '0');
    int corr_hours = (correct[0] - '0') * 10 + (correct[1] - '0');
    int corr_minutes = (correct[3] - '0') * 10 + (correct[4] - '0');

    int total_curr_minutes = curr_hours * 60 + curr_minutes;
    int total_corr_minutes = corr_hours * 60 + corr_minutes;

    int diff = total_corr_minutes - total_curr_minutes;
    int operations = 0;

    int increments[] = {60, 15, 5, 1};
    for (int i = 0; i < 4; i++) {
        operations += diff / increments[i];
        diff %= increments[i];
    }

    return operations;      
}
