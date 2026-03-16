// Source: https://leetcode.com/problems/can-i-win/   |   Difficulty: Medium
//
// Problem Description:
// In the "100 game" two players take turns adding, to a running total, any integer from 1 to 10. The player who first causes the running total to reach or exceed 100 wins.
//
// What if we change the game so that players cannot re-use integers?
//
// For example, two players might take turns drawing from a common pool of numbers from 1 to 15 without replacement until they reach a total >= 100.
//
// Given two integers maxChoosableInteger and desiredTotal, return true if the first player to move can force a win, otherwise, return false. Assume both players play optimally.
//
// Example:
// Input: maxChoosableInteger = 10, desiredTotal = 11
// Output: false
// Explanation:
// No matter which integer the first player choose, the first player will lose.
// The first player can choose an integer from 1 up to 10.
// If the first player choose 1, the second player can only choose integers from 2 up to 10.
// The second player will win by choosing 10 and get a total = 11, which is >= desiredTotal.
// Same with other integers chosen by the first player, the second player will always win.
//
// Constraints:
// 1 <= maxChoosableInteger <= 20
// 	0 <= desiredTotal <= 300
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number} maxChoosableInteger
 * @param {number} desiredTotal
 * @return {boolean}
 */
var canIWin = function(maxChoosableInteger, desiredTotal) {
    // If the sum of all choosable integers is less than the desired total, it's impossible to win
    const totalSum = (maxChoosableInteger * (maxChoosableInteger + 1)) / 2;
    if (totalSum < desiredTotal) return false;

    // If the desired total is 0 or less, the first player wins by default
    if (desiredTotal <= 0) return true;

    const memo = new Map(); // Memoization map to store previously computed states

    const canWin = (usedNumbers, currentTotal) => {
        if (currentTotal >= desiredTotal) return false; // Opponent wins if current total reaches or exceeds desired total

        const memoKey = usedNumbers.toString(); // Convert used numbers to string for memoization key
        if (memo.has(memoKey)) return memo.get(memoKey); // Return cached result if available

        for (let i = 1; i <= maxChoosableInteger; i++) {
            const bitMask = 1 << (i - 1); // Create a bitmask for the current number

            if ((usedNumbers & bitMask) === 0) { // Check if the number has not been used
                // Mark the number as used and check if the opponent can win with this choice
                if (!canWin(usedNumbers | bitMask, currentTotal + i)) {
                    memo.set(memoKey, true); // Cache the result before returning
                    return true; // Current player wins if opponent cannot win
                }
            }
        }

        memo.set(memoKey, false); // Cache the result before returning
        return false; // Current player loses if all choices lead to opponent's win
    };

    return canWin(0, 0); // Start with no numbers used and a total of 0
};
