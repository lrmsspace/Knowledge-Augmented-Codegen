// Source: https://leetcode.com/problems/cells-in-a-range-on-an-excel-sheet/   |   Difficulty: Easy
//
// Problem Description:
// A cell (r, c) of an excel sheet is represented as a string "<col><row>" where:
//
//
// 	<col> denotes the column number c of the cell. It is represented by alphabetical letters.
//
// 	
// 		For example, the 1st column is denoted by 'A', the 2nd by 'B', the 3rd by 'C', and so on.
// 	
// 	
// 	<row> is the row number r of the cell. The rth row is represented by the integer r.
//
//
// You are given a string s in the format "<col1><row1>:<col2><row2>", where <col1> represents the column c1, <row1> represents the row r1, <col2> represents the column c2, and <row2> represents the row r2, such that r1 <= r2 and c1 <= c2.
//
// Return the list of cells (x, y) such that r1 <= x <= r2 and c1 <= y <= c2. The cells should be represented as strings in the format mentioned above and be sorted in non-decreasing order first by columns and then by rows.
//
// Example:
// Input: s = "K1:L2"
// Output: ["K1","K2","L1","L2"]
// Explanation:
// The above diagram shows the cells which should be present in the list.
// The red arrows denote the order in which the cells should be presented.
//
// Constraints:
// s.length == 5
// 	'A' <= s[0] <= s[3] <= 'Z'
// 	'1' <= s[1] <= s[4] <= '9'
// 	s consists of uppercase English letters, digits and ':'.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {string[]}
 */
var cellsInRange = function(s) {
    const result = [];
    const col1 = s.charCodeAt(0); // Get ASCII code of the first column
    const row1 = parseInt(s[1]); // Get the first row number
    const col2 = s.charCodeAt(3); // Get ASCII code of the second column
    const row2 = parseInt(s[4]); // Get the second row number   
    for (let col = col1; col <= col2; col++) { // Iterate through columns from col1 to col2
        for (let row = row1; row <= row2; row++) { // Iterate through rows from row1 to row2
            result.push(String.fromCharCode(col) + row); // Construct the cell string and add to result
        }   
    }
    return result; // Return the list of cells in the specified range
};
