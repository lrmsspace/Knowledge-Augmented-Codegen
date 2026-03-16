// Source: https://leetcode.com/problems/remove-digit-from-number-to-maximize-result/   |   Difficulty: Easy
//
// Problem Description:
// You are given a string number representing a positive integer and a character digit.
//
// Return the resulting string after removing exactly one occurrence of digit from number such that the value of the resulting string in decimal form is maximized. The test cases are generated such that digit occurs at least once in number.
//
// Example:
// Input: number = "123", digit = "3"
// Output: "12"
// Explanation: There is only one '3' in "123". After removing '3', the result is "12".
//
// Constraints:
// 2 <= number.length <= 100
// 	number consists of digits from '1' to '9'.
// 	digit is a digit from '1' to '9'.
// 	digit occurs at least once in number.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp, recursion)
//   • When to use: Used for counting numbers or summing properties of numbers within a given range [A, B] that satisfy certain digit-based conditions.
//   • Idea: Digit DP is a dynamic programming technique to count numbers or calculate sums of properties for numbers in a given range [A, B] by building them digit by digit. It typically operates in O(D * S) time, where D is the number of digits and S is the maximum sum/property value.
//   • Invariants: The `tight` parameter correctly reflects if the current digit choice is restricted by the original number's digit at the current position.; The `sum` parameter accurately accumulates the sum of digits chosen for the prefix constructed so far.
//   • Tips: Convert the upper bound number into a digit array for easier processing.; Define the DP state to include current index, tight constraint, and any relevant accumulated property (e.g., sum, count).
//   • Pitfalls: Incorrectly handling the `tight` constraint, leading to overcounting or undercounting.; Forgetting to memoize or using an insufficient DP table size for state parameters.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
// - kth-largest-element-in-an-array (array, quickselect, randomized)
//   • When to use: Use when you need to efficiently find the k-th smallest or largest element in an unsorted array without fully sorting it, especially when average-case linear time complexity is acceptable and in-place modification is desired.
//   • Idea: QuickSelect is a divide-and-conquer algorithm that partitions an array around a pivot and recursively searches for the k-th element in the relevant partition. It offers an average-case O(N) time complexity and O(1) space.
//   • Invariants: The pivot element is always placed at its correct sorted position within the current sub-array.; All elements to the left of the pivot are less than or equal to it, and all elements to its right are greater than or equal to it.
//   • Tips: Randomly select pivots to ensure average-case O(N) performance and avoid worst-case scenarios.; Adjust the target index k based on whether you're seeking the k-th smallest or k-th largest element.
//   • Pitfalls: Poor pivot selection can lead to a worst-case O(N^2) time complexity, though rare with randomization.; Off-by-one errors are common when mapping k-th largest/smallest to 0-indexed array positions.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public String removeDigit(String number, char digit) {
        String maxNumber = "";
        for (int i = 0; i < number.length(); i++) {
            if (number.charAt(i) == digit) {
                String candidate = number.substring(0, i) + number.substring(i + 1);
                if (candidate.compareTo(maxNumber) > 0) {
                    maxNumber = candidate;
                }
            }
        }
        return maxNumber;           
    }
}
