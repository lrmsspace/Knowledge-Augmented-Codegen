// Source: https://leetcode.com/problems/strong-password-checker/   |   Difficulty: Hard
//
// Problem Description:
// A password is considered strong if the below conditions are all met:
//
//
// 	It has at least 6 characters and at most 20 characters.
// 	It contains at least one lowercase letter, at least one uppercase letter, and at least one digit.
// 	It does not contain three repeating characters in a row (i.e., "Baaabb0" is weak, but "Baaba0" is strong).
//
//
// Given a string password, return the minimum number of steps required to make password strong. if password is already strong, return 0.
//
// In one step, you can:
//
//
// 	Insert one character to password,
// 	Delete one character from password, or
// 	Replace one character of password with another character.
//
// Example:
// Input: password = "a"
// Output: 5
//
// Constraints:
// 1 <= password.length <= 50
// 	password consists of letters, digits, dot '.' or exclamation mark '!'.
//
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Linear Diophantine Equation (number, greedy)
//   • When to use: Use when a problem can be solved by making the locally optimal choice at each step, hoping this leads to a globally optimal solution. This strategy is often simpler and faster than dynamic programming.
//   • Idea: The greedy algorithm makes the best choice at each stage with the hope of finding a global optimum, without reconsidering previous choices. Its time complexity is typically O(N log N) or O(N).
//   • Invariants: At each step, the chosen element is the best available according to the greedy criterion.; The partial solution constructed so far remains optimal for the subproblem considered.
//   • Tips: Prove correctness by exchange argument or induction.; Sort input data if it helps identify the greedy choice.
//   • Pitfalls: Failing to prove the greedy choice property.; Making a locally optimal choice that prevents a global optimum.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int strongPasswordChecker(String password) {
        int n = password.length();
        boolean hasLower = false, hasUpper = false, hasDigit = false;
        char[] arr = password.toCharArray();
        int[] repeats = new int[n];

        for (int i = 0; i < n; i++) {
            char c = arr[i];
            if (Character.isLowerCase(c)) hasLower = true;
            else if (Character.isUpperCase(c)) hasUpper = true;
            else if (Character.isDigit(c)) hasDigit = true;

            if (i >= 2 && arr[i] == arr[i - 1] && arr[i] == arr[i - 2]) {
                repeats[i] = repeats[i - 1] + 1;
            }
        }

        int missingTypes = 0;
        if (!hasLower) missingTypes++;
        if (!hasUpper) missingTypes++;
        if (!hasDigit) missingTypes++;

        if (n < 6) {
            return Math.max(missingTypes, 6 - n);
        } else {
            int totalReplacements = 0;
            int[] modCounts = new int[3];

            for (int i = 0; i < n; i++) {
                if (repeats[i] > 0) {
                    totalReplacements += (repeats[i] / 3);
                    modCounts[repeats[i] % 3]++;
                }
            }

            if (n <= 20) {
                return Math.max(missingTypes, totalReplacements);
            } else {
                int deletionsNeeded = n - 20;
                int deletions = deletionsNeeded;

                for (int i = 0; i < 3; i++) {
                    if (deletions <= 0) break;
                    int numMod = modCounts[i];
                    int deleteForMod = i + 1;

                    if (i == 2) {
                        int canDelete = deletions / deleteForMod;
                        totalReplacements -= Math.min(canDelete, numMod);
                        deletions -= canDelete * deleteForMod;
                    } else {
                        int canDelete = Math.min(numMod, deletions / deleteForMod);
                        totalReplacements -= canDelete;
                        deletions -= canDelete * deleteForMod;
                    }
                }

                return deletionsNeeded + Math.max(missingTypes, totalReplacements);         
            }
        }
    }
}
