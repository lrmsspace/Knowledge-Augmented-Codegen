// Source: https://leetcode.com/problems/reconstruct-original-digits-from-english/   |   Difficulty: Medium
//
// Problem Description:
// Given a string s containing an out-of-order English representation of digits 0-9, return the digits in ascending order.
//
// Example:
// Input: s = "owoztneoer"
// Output: "012"
//
// Constraints:
// 1 <= s.length <= 105
// 	s[i] is one of the characters ["e","g","f","i","h","o","n","s","r","u","t","w","v","x","z"].
// 	s is guaranteed to be valid.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Fibonacci Numbers (number, greedy, enumeration)
//   • When to use: When you need a unique, non-ambiguous binary representation of positive integers based on Fibonacci numbers, ensuring no two consecutive Fibonacci numbers are used in the sum.
//   • Idea: This algorithm encodes a positive integer into a unique binary string by greedily finding its Zeckendorf representation (sum of non-consecutive Fibonacci numbers). The encoding process typically involves iterating through Fibonacci numbers, resulting in a logarithmic time complexity relative to the input number's magnitude.
//   • Invariants: The remaining value 'n' to be encoded is always non-negative.; The partial binary code constructed so far represents a valid Zeckendorf sum of non-consecutive Fibonacci numbers.
//   • Tips: Precompute Fibonacci numbers up to a certain limit to optimize lookups.; Always start with the largest Fibonacci number less than or equal to the target value.
//   • Pitfalls: Incorrectly handling the base cases for small numbers like 1 or 2.; Forgetting to append the mandatory final '1' bit to the codeword.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} s
 * @return {string}
 */
var originalDigits = function(s) {
	// We can count the frequency of each character in the input string and use that to determine how many of each digit we have. 
	// We can identify certain digits by unique characters: 'z' for 0, 'w' for 2, 'u' for 4, 'x' for 6, and 'g' for 8. 
	// After counting those digits, we can adjust the counts for the remaining digits (1, 3, 5, 7, 9) by considering the characters that are shared among them.
	const charCount = new Array(26).fill(0);
	for (const char of s) {
		charCount[char.charCodeAt(0) - 'a'.charCodeAt(0)]++;
	}

	const digitCount = new Array(10).fill(0);
	digitCount[0] = charCount['z'.charCodeAt(0) - 'a'.charCodeAt(0)];
	digitCount[2] = charCount['w'.charCodeAt(0) - 'a'.charCodeAt(0)];
	digitCount[4] = charCount['u'.charCodeAt(0) - 'a'.charCodeAt(0)];
	digitCount[6] = charCount['x'.charCodeAt(0) - 'a'.charCodeAt(0)];
	digitCount[8] = charCount['g'.charCodeAt(0) - 'a'.charCodeAt(0)];

	digitCount[1] = charCount['o'.charCodeAt(0) - 'a'.charCodeAt(0)] - digitCount[0] - digitCount[2] - digitCount[4];
	digitCount[3] = charCount['h'.charCodeAt(0) - 'a'.charCodeAt(0)] - digitCount[8];
	digitCount[5] = charCount['f'.charCodeAt(0) - 'a'.charCodeAt(0)] - digitCount[4];
	digitCount[7] = charCount['s'.charCodeAt(0) - 'a'.charCodeAt(0)] - digitCount[6];
    digitCount[9] = charCount['i'.charCodeAt(0) - 'a'.charCodeAt(0)] - digitCount[5] - digitCount[6] - digitCount[8];

    let result = '';
    for (let i = 0; i <= 9; i++) {
        result += i.toString().repeat(digitCount[i]);
    }

    return result;
};
