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
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private int MOD = 1_000_000_007;
    private int[][][] memo;
    private int b;
    private String decrement(String num) {
        char[] arr = num.toCharArray();
        int n = arr.length;
        int i = n - 1;
        while (i >= 0) {
            if (arr[i] > '0') {
                arr[i]--;
                break;
            } else {
                arr[i] = '9';
                i--;
            }
        }
        if (i == -1 && arr[0] == '0') {
            return new String(arr, 1, n - 1);
        }
        return new String(arr);
    }
    private int dfs(String num, int index, int prevDigit, boolean isTight) {
        if (index == num.length()) {
            return 1;
        }
        if (memo[index][prevDigit][isTight ? 1 : 0] != -1) {
            return memo[index][prevDigit][isTight ? 1 : 0];
        }
        int limit = isTight ? (num.charAt(index) - '0') : (b - 1);
        int total = 0;
        for (int digit = prevDigit; digit <= limit; digit++) {
            total = (total + dfs(num, index + 1, digit, isTight && (digit == limit))) % MOD;
        }
        memo[index][prevDigit][isTight ? 1 : 0] = total;
        return total;
    }
    private int countUpTo(String num, int base) {
        this.b = base;
        int n = num.length();
        memo = new int[n][b + 1][2];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j <= b; j++) {
                memo[i][j][0] = -1;
                memo[i][j][1] = -1;
            }
        }
        return dfs(num, 0, 0, true);
    }
    public int countNumbers(String l, String r, int b) {
        return (countUpTo(r, b) - countUpTo(decrement(l), b) + 1_000_000_007) % 1_000_000_007;          
    }
}
