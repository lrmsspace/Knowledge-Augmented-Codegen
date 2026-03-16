// Source: https://leetcode.com/problems/verbal-arithmetic-puzzle/   |   Difficulty: Hard
//
// Problem Description:
// Given an equation, represented by words on the left side and the result on the right side.
//
// You need to check if the equation is solvable under the following rules:
//
//
// 	Each character is decoded as one digit (0 - 9).
// 	No two characters can map to the same digit.
// 	Each words[i] and result are decoded as one number without leading zeros.
// 	Sum of numbers on the left side (words) will equal to the number on the right side (result).
//
//
// Return true if the equation is solvable, otherwise return false.
//
// Example:
// Input: words = ["SEND","MORE"], result = "MONEY"
// Output: true
// Explanation: Map 'S'-> 9, 'E'->5, 'N'->6, 'D'->7, 'M'->1, 'O'->0, 'R'->8, 'Y'->'2'
// Such that: "SEND" + "MORE" = "MONEY" ,  9567 + 1085 = 10652
//
// Constraints:
// 2 <= words.length <= 5
// 	1 <= words[i].length, result.length <= 7
// 	words[i], result contain only uppercase English letters.
// 	The number of different characters used in the expression is at most 10.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, recursion, backtracking)
//   • When to use: Use when counting numbers within a range that satisfy a specific digit-based or bit-based pattern constraint, especially when the constraint involves adjacent digits or bits.
//   • Idea: This algorithm recursively generates binary numbers bit by bit, ensuring no two consecutive ones are formed. It prunes branches that exceed a given upper limit or violate the consecutive one constraint, effectively counting valid numbers up to N in O(log N) time.
//   • Invariants: The `sum` generated so far never exceeds the target `num`.; The `prev` boolean accurately reflects whether the last bit added was a '1'.
//   • Tips: Generate numbers bit by bit, typically from LSB or MSB, to build up valid sequences.; Maintain state about the previously placed bit to enforce the 'no consecutive ones' rule.
//   • Pitfalls: Failing to correctly handle the base cases for the recursive function.; Incorrectly managing the 'previous bit' state, leading to invalid sequences.
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
    private boolean backtrack(String[] words, String result, int[] charToDigit, boolean[] usedDigits, boolean[] leadingChars, int index, int carry, int pos) {
        if (pos == result.length()) {
            return carry == 0;
        }

        int sum = carry;
        for (String word : words) {
            int wordLen = word.length();
            if (wordLen > pos) {
                char c = word.charAt(wordLen - 1 - pos);
                int digit = charToDigit[c - 'A'];
                if (digit == -1) {
                    continue;
                }
                sum += digit;
            }
        }

        char resultChar = result.charAt(result.length() - 1 - pos);
        int expectedDigit = sum % 10;
        int newCarry = sum / 10;

        int mappedDigit = charToDigit[resultChar - 'A'];
        if (mappedDigit != -1) {
            if (mappedDigit != expectedDigit) {
                return false;
            }
            return backtrack(words, result, charToDigit, usedDigits, leadingChars, index, newCarry, pos + 1);
        } else {
            for (int d = 0; d <= 9; d++) {
                if (usedDigits[d]) {
                    continue;
                }
                if (d == 0 && leadingChars[resultChar - 'A']) {
                    continue;
                }

                charToDigit[resultChar - 'A'] = d;
                usedDigits[d] = true;

                if (backtrack(words, result, charToDigit, usedDigits, leadingChars, index, newCarry, pos + 1)) {
                    return true;
                }

                charToDigit[resultChar - 'A'] = -1;
                usedDigits[d] = false;
            }
        }
        return false;
    }
    public boolean isSolvable(String[] words, String result) {
        int n = words.length;
        int[] charToDigit = new int[26];
        boolean[] usedDigits = new boolean[10];
        boolean[] leadingChars = new boolean[26];
        Arrays.fill(charToDigit, -1);

        for (String word : words) {
            leadingChars[word.charAt(0) - 'A'] = true;
        }
        leadingChars[result.charAt(0) - 'A'] = true;

        return backtrack(words, result, charToDigit, usedDigits, leadingChars, 0, 0, 0);            
    }
}
