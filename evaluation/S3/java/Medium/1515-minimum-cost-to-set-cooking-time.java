// Source: https://leetcode.com/problems/minimum-cost-to-set-cooking-time/   |   Difficulty: Medium
//
// Problem Description:
// A generic microwave supports cooking times for:
//
//
// 	at least 1 second.
// 	at most 99 minutes and 99 seconds.
//
//
// To set the cooking time, you push at most four digits. The microwave normalizes what you push as four digits by prepending zeroes. It interprets the first two digits as the minutes and the last two digits as the seconds. It then adds them up as the cooking time. For example,
//
//
// 	You push 9 5 4 (three digits). It is normalized as 0954 and interpreted as 9 minutes and 54 seconds.
// 	You push 0 0 0 8 (four digits). It is interpreted as 0 minutes and 8 seconds.
// 	You push 8 0 9 0. It is interpreted as 80 minutes and 90 seconds.
// 	You push 8 1 3 0. It is interpreted as 81 minutes and 30 seconds.
//
//
// You are given integers startAt, moveCost, pushCost, and targetSeconds. Initially, your finger is on the digit startAt. Moving the finger above any specific digit costs moveCost units of fatigue. Pushing the digit below the finger once costs pushCost units of fatigue.
//
// There can be multiple ways to set the microwave to cook for targetSeconds seconds but you are interested in the way with the minimum cost.
//
// Return the minimum cost to set targetSeconds seconds of cooking time.
//
// Remember that one minute consists of 60 seconds.
//
// Example:
// Input: startAt = 1, moveCost = 2, pushCost = 1, targetSeconds = 600
// Output: 6
// Explanation: The following are the possible ways to set the cooking time.
// - 1 0 0 0, interpreted as 10 minutes and 0 seconds.
//   The finger is already on digit 1, pushes 1 (with cost 1), moves to 0 (with cost 2), pushes 0 (with cost 1), pushes 0 (with cost 1), and pushes 0 (with cost 1).
//   The cost is: 1 + 2 + 1 + 1 + 1 = 6. This is the minimum cost.
// - 0 9 6 0, interpreted as 9 minutes and 60 seconds. That is also 600 seconds.
//   The finger moves to 0 (with cost 2), pushes 0 (with cost 1), moves to 9 (with cost 2), pushes 9 (with cost 1), moves to 6 (with cost 2), pushes 6 (with cost 1), moves to 0 (with cost 2), and pushes 0 (with cost 1).
//   The cost is: 2 + 1 + 2 + 1 + 2 + 1 + 2 + 1 = 12.
// - 9 6 0, normalized as 0960 and interpreted as 9 minutes and 60 seconds.
//   The finger moves to 9 (with cost 2), pushes 9 (with cost 1), moves to 6 (with cost 2), pushes 6 (with cost 1), moves to 0 (with cost 2), and pushes 0 (with cost 1).
//   The cost is: 2 + 1 + 2 + 1 + 2 + 1 = 9.
//
// Constraints:
// 0 <= startAt <= 9
// 	1 <= moveCost, pushCost <= 105
// 	1 <= targetSeconds <= 6039
//
// Helpful references (internal KB):
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
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int minCostSetTime(int startAt, int moveCost, int pushCost, int targetSeconds) {
        int minCost = Integer.MAX_VALUE;

        for (int minutes = 0; minutes <= 99; minutes++) {
            int seconds = targetSeconds - minutes * 60;
            if (seconds < 0 || seconds > 99) {
                continue;
            }

            String timeStr = String.format("%02d%02d", minutes, seconds);
            int cost = calculateCost(timeStr, startAt, moveCost, pushCost);
            minCost = Math.min(minCost, cost);
        }

        return minCost;         
    }
}
