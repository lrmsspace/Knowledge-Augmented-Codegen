// Source: https://leetcode.com/problems/split-array-into-fibonacci-sequence/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string of digits num, such as "123456579". We can split it into a Fibonacci-like sequence [123, 456, 579].
//
// Formally, a Fibonacci-like sequence is a list f of non-negative integers such that:
//
//
// 	0 <= f[i] < 231, (that is, each integer fits in a 32-bit signed integer type),
// 	f.length >= 3, and
// 	f[i] + f[i + 1] == f[i + 2] for all 0 <= i < f.length - 2.
//
//
// Note that when splitting the string into pieces, each piece must not have extra leading zeroes, except if the piece is the number 0 itself.
//
// Return any Fibonacci-like sequence split from num, or return [] if it cannot be done.
//
// Example:
// Input: num = "1101111"
// Output: [11,0,11,11]
// Explanation: The output [110, 1, 111] would also be accepted.
//
// Constraints:
// 1 <= num.length <= 200
// 	num contains only digits.
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} num
 * @return {number[]}
 */
var splitIntoFibonacci = function(num) {
        const res = [];     
    const n = num.length;
    
    const backtrack = (index) => {
        if (index === n && res.length >= 3) {
            return true; // Found a valid Fibonacci-like sequence
        }
        for (let i = index; i < n; i++) {
            const numStr = num.substring(index, i + 1);
            // Skip numbers with leading zeros (except for "0")
            if (numStr.length > 1 && numStr[0] === '0') {
                break;
            }
            const val = parseInt(numStr);
            // If the value is too large to be part of a Fibonacci sequence, break early
            if (val > 2147483647) {
                break;
            }
            // If we have at least 2 numbers in the sequence, check if the current number is the sum of the last two
            if (res.length >= 2 && val !== res[res.length - 1] + res[res.length - 2]) {
                continue;
            }
            res.push(val);
            if (backtrack(i + 1)) {
                return true;
            }
            res.pop(); // Backtrack
        }
        return false;
    };
    backtrack(0);
    return res;
    
};
