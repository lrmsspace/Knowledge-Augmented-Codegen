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
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool isSolvable(char** words, int wordsSize, char* result) {
    int charToDigit[26];
    bool usedDigits[10] = {false};
    bool leadingZero[26] = {false};
    int uniqueChars[26];
    int uniqueCount = 0;
    memset(charToDigit, -1, sizeof(charToDigit));

    // Identify unique characters and leading zero constraints
    for (int i = 0; i < wordsSize; i++) {
        int len = strlen(words[i]);
        for (int j = 0; j < len; j++) {
            int idx = words[i][j] - 'A';
            if (charToDigit[idx] == -1) {
                charToDigit[idx] = -2; // Mark as seen
                uniqueChars[uniqueCount++] = idx;
            }
            if (j == 0 && len > 1) {
                leadingZero[idx] = true;
            }
        }
    }
    int resultLen = strlen(result);
    for (int j = 0; j < resultLen; j++) {
        int idx = result[j] - 'A';
        if (charToDigit[idx] == -1) {
            charToDigit[idx] = -2; // Mark as seen
            uniqueChars[uniqueCount++] = idx;
        }
        if (j == 0 && resultLen > 1) {
            leadingZero[idx] = true;
        }
    }

    if (uniqueCount > 10) return false; // More than 10 unique chars

    // Backtracking function to assign digits
    bool backtrack(int pos) {
        if (pos == uniqueCount) {
            // Check if the current assignment satisfies the equation
            long long sumWords = 0;
            for (int i = 0; i < wordsSize; i++) {
                long long num = 0;
                for (int j = 0; words[i][j]; j++) {
                    num = num * 10 + charToDigit[words[i][j] - 'A'];
                }
                sumWords += num;
            }
            long long numResult = 0;
            for (int j = 0; result[j]; j++) {
                numResult = numResult * 10 + charToDigit[result[j] - 'A'];
            }
            return sumWords == numResult;
        }

        int chIdx = uniqueChars[pos];
        for (int digit = 0; digit <= 9; digit++) {
            if (usedDigits[digit]) continue;
            if (digit == 0 && leadingZero[chIdx]) continue;

            // Assign digit
            charToDigit[chIdx] = digit;
            usedDigits[digit] = true;

            if (backtrack(pos + 1)) {
                return true;
            }

            // Backtrack
            charToDigit[chIdx] = -2;
            usedDigits[digit] = false;
        }
        return false;   
    }
    return backtrack(0);
}
