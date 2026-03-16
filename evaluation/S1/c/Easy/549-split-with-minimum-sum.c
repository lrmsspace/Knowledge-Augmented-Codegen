// Source: https://leetcode.com/problems/split-with-minimum-sum/   |   Difficulty: Easy
//
// Problem Description:
// Given a positive integer num, split it into two non-negative integers num1 and num2 such that:
//
//
// 	The concatenation of num1 and num2 is a permutation of num.
//
// 	
// 		In other words, the sum of the number of occurrences of each digit in num1 and num2 is equal to the number of occurrences of that digit in num.
// 	
// 	
// 	num1 and num2 can contain leading zeros.
//
//
// Return the minimum possible sum of num1 and num2.
//
// Notes:
//
//
// 	It is guaranteed that num does not contain any leading zeros.
// 	The order of occurrence of the digits in num1 and num2 may differ from the order of occurrence of num.
//
// Example:
// Input: num = 4325
// Output: 59
// Explanation: We can split 4325 so that num1 is 24 and num2 is 35, giving a sum of 59. We can prove that 59 is indeed the minimal possible sum.
//
// Constraints:
// 10 <= num <= 109
//
// Helpful references (internal KB):
// - String Sorts (array, string, number, radix-sort, recursion, counting-sort)
//   • When to use: Use when sorting a large collection of strings or integers with a limited range of character/digit values. It is particularly efficient for fixed-length keys but can be adapted for variable lengths.
//   • Idea: Radix sort is a non-comparative integer sorting algorithm that sorts data with integer keys by grouping keys by individual digits or characters which share the same significant position and value. It typically achieves O(N*W) time complexity, where N is the number of items and W is the key length.
//   • Invariants: After each pass `d`, the elements are stably sorted according to their digits up to position `d`.; The counting sort subroutine correctly places elements into their sorted positions for the current digit, preserving relative order.
//   • Tips: LSD (Least Significant Digit) is simpler for fixed-length keys.; MSD (Most Significant Digit) is better for variable-length keys or when keys are very long.
//   • Pitfalls: Not efficient for small N or very large W due to constant factors.; Requires extra space for auxiliary array and counting array.
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int splitNum(int num) {
    int digits[10];
    int count = 0;
    while (num > 0) {
        digits[count++] = num % 10;
        num /= 10;
    }

    // Sort digits using counting sort
    int countDigits[10] = {0};
    for (int i = 0; i < count; i++) {
        countDigits[digits[i]]++;
    }

    int sortedDigits[10];
    int index = 0;
    for (int digit = 0; digit <= 9; digit++) {
        while (countDigits[digit] > 0) {
            sortedDigits[index++] = digit;
            countDigits[digit]--;
        }
    }

    // Form two numbers by alternating digits
    long long num1 = 0, num2 = 0;
    for (int i = 0; i < count; i++) {
        if (i % 2 == 0) {
            num1 = num1 * 10 + sortedDigits[i];
        } else {
            num2 = num2 * 10 + sortedDigits[i];
        }
    }

    return (int)(num1 + num2);      
}
