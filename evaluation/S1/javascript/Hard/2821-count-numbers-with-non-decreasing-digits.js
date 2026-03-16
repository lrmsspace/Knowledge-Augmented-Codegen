// Source: https://leetcode.com/problems/count-numbers-with-non-decreasing-digits/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers, l and r, represented as strings, and an integer b. Return the count of integers in the inclusive range [l, r] whose digits are in non-decreasing order when represented in base b.
//
// An integer is considered to have non-decreasing digits if, when read from left to right (from the most significant digit to the least significant digit), each digit is greater than or equal to the previous one.
//
// Since the answer may be too large, return it modulo 109 + 7.
//
// Example:
// Input: l = "23", r = "28", b = 8
//
// Output: 3
//
// Explanation:
//
//
// 	The numbers from 23 to 28 in base 8 are: 27, 30, 31, 32, 33, and 34.
// 	Out of these, 27, 33, and 34 have non-decreasing digits. Hence, the output is 3.
//
// Constraints:
// 1 <= l.length <= r.length <= 100
// 	2 <= b <= 10
// 	l and r consist only of digits.
// 	The value represented by l is less than or equal to the value represented by r.
// 	l and r do not contain leading zeros.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
// - String Sorts (array, string, recursion)
//   • When to use: Use this algorithm to sort a collection of strings lexicographically, especially when string lengths vary or are large, and the character set is limited.
//   • Idea: This algorithm sorts an array of strings lexicographically by recursively applying a counting sort-like distribution based on characters from most significant to least significant digit. It typically achieves O(N*L + R*L) time complexity, where N is the number of strings, L is the average string length, and R is the radix size.
//   • Invariants: All strings in the current `a[lo...hi]` sub-array share a common prefix of length `d`.; After the distribution pass for character `d`, `aux` contains strings from `a[lo...hi]` stably sorted by their `d`-th character.
//   • Tips: Use an auxiliary array for stable distribution during each pass to maintain relative order.; Implement a cutoff to insertion sort for small sub-arrays to improve performance due to lower overhead.
//   • Pitfalls: Can have high overhead for small N or short strings compared to comparison sorts.; Potentially memory intensive due to the auxiliary array and recursion stack depth proportional to max string length.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string} l
 * @param {string} r
 * @param {number} b
 * @return {number}
 */
var countNumbers = function(l, r, b) {
    const mod = 1e9 + 7;
    
    const countUpTo = (num) => {
        const digits = num.split('').map(Number);
        const n = digits.length;
        const memo = new Map();
        
        const dfs = (pos, prevDigit, tight) => {
            if (pos === n) return 1;
            const key = `${pos},${prevDigit},${tight}`;
            if (memo.has(key)) return memo.get(key);
            
            let limit = tight ? digits[pos] : b - 1;
            let total = 0;
            for (let d = prevDigit; d <= limit; d++) {
                total = (total + dfs(pos + 1, d, tight && d === limit)) % mod;
            }
            
            memo.set(key, total);
            return total;
        };
        
        return dfs(0, 0, true);
    };
    
    const countR = countUpTo(r);
    const countL = countUpTo(l);
    
    // Check if l itself is non-decreasing
    let isNonDecreasingL = true;
    for (let i = 1; i < l.length; i++) {
        if (l[i] < l[i - 1]) {
            isNonDecreasingL = false;
            break;
        }
    }
    
    return (countR - countL + (isNonDecreasingL ? 1 : 0) + mod) % mod;
};
