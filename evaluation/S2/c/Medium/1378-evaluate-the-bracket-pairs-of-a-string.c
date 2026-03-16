// Source: https://leetcode.com/problems/evaluate-the-bracket-pairs-of-a-string/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string s that contains some bracket pairs, with each pair containing a non-empty key.
//
//
// 	For example, in the string "(name)is(age)yearsold", there are two bracket pairs that contain the keys "name" and "age".
//
//
// You know the values of a wide range of keys. This is represented by a 2D string array knowledge where each knowledge[i] = [keyi, valuei] indicates that key keyi has a value of valuei.
//
// You are tasked to evaluate all of the bracket pairs. When you evaluate a bracket pair that contains some key keyi, you will:
//
//
// 	Replace keyi and the bracket pair with the key's corresponding valuei.
// 	If you do not know the value of the key, you will replace keyi and the bracket pair with a question mark "?" (without the quotation marks).
//
//
// Each key will appear at most once in your knowledge. There will not be any nested brackets in s.
//
// Return the resulting string after evaluating all of the bracket pairs.
//
// Example:
// Input: s = "(name)is(age)yearsold", knowledge = [["name","bob"],["age","two"]]
// Output: "bobistwoyearsold"
// Explanation:
// The key "name" has a value of "bob", so replace "(name)" with "bob".
// The key "age" has a value of "two", so replace "(age)" with "two".
//
// Constraints:
// 1 <= s.length <= 105
// 	0 <= knowledge.length <= 105
// 	knowledge[i].length == 2
// 	1 <= keyi.length, valuei.length <= 10
// 	s consists of lowercase English letters and round brackets '(' and ')'.
// 	Every open bracket '(' in s will have a corresponding close bracket ')'.
// 	The key in each bracket pair of s will be non-empty.
// 	There will not be any nested bracket pairs in s.
// 	keyi and valuei consist of lowercase English letters.
// 	Each keyi in knowledge is unique.
//
// Helpful references (internal KB):
// - Substring Search (string, array, kmp, simulation)
//   • When to use: Use when efficiently finding all occurrences or the first occurrence of a pattern within a larger text, especially when the pattern might have repeating or overlapping prefixes.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm is an efficient string-searching algorithm that avoids re-scanning characters in the text by pre-processing the pattern to build a 'longest proper prefix suffix' (LPS) array. It achieves optimal O(N + M) time complexity, where N is the text length and M is the pattern length.
//   • Invariants: The `j` pointer always indicates the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `text[0...i-1]`.; The `lps[j]` value stores the length of the longest proper prefix of `pattern[0...j-1]` that is also a suffix of `pattern[0...j-1]`.
//   • Tips: Pre-compute the LPS array (also known as failure function or border array) for the pattern.; The LPS array helps determine the next best match position after a mismatch, avoiding redundant comparisons.
//   • Pitfalls: Incorrectly building the LPS array can lead to wrong matches or infinite loops.; Off-by-one errors when indexing the pattern or text are common.
// - Expression parsing (stack, simulation)
//   • When to use: Use this algorithm to evaluate an arithmetic expression given in infix notation, respecting operator precedence and parentheses. It is suitable for expressions with binary, left-associative operators.
//   • Idea: This algorithm evaluates an infix arithmetic expression using two stacks: one for operands and one for operators. It processes the expression from left to right, applying operator precedence and associativity rules to achieve an O(N) time complexity.
//   • Invariants: The operand stack always contains valid numerical values or intermediate results.; The operator stack maintains operators such that operators with higher or equal precedence are processed before lower precedence ones.
//   • Tips: Clearly define operator precedence and associativity rules for all operators.; Use a separate stack for operands (numbers) and operators (including parentheses).
//   • Pitfalls: Misinterpreting operator precedence or associativity rules can lead to incorrect results.; Failure to handle mismatched or unbalanced parentheses can cause runtime errors.
// - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
//   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
//   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
//   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
//   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* evaluate(char* s, char*** knowledge, int knowledgeSize, int* knowledgeColSize) {
    // Step 1: Build a hash map from the knowledge array for O(1) lookups
    // We'll use a simple array of structs to store key-value pairs since C doesn't have built-in hash maps.
    typedef struct {
        char* key;
        char* value;
    } KeyValuePair;

    KeyValuePair* map = (KeyValuePair*)malloc(knowledgeSize * sizeof(KeyValuePair));
    for (int i = 0; i < knowledgeSize; i++) {
        map[i].key = knowledge[i][0];
        map[i].value = knowledge[i][1];
    }

    // Step 2: Process the string s and replace bracket pairs with corresponding values
    int len = strlen(s);
    char* result = (char*)malloc((len + 1) * sizeof(char)); // Allocate enough memory for the result
    int resIndex = 0;

    for (int i = 0; i < len; i++) {
        if (s[i] == '(') {
            // Find the closing bracket
            int j = i + 1;
            while (j < len && s[j] != ')') {
                j++;
            }
            if (j < len) { // Found a closing bracket
                // Extract the key between the brackets
                char key[11]; // Max key length is 10 + null terminator
                int keyIndex = 0;
                for (int k = i + 1; k < j; k++) {
                    key[keyIndex++] = s[k];
                }
                key[keyIndex] = '\0'; // Null-terminate the key

                // Look up the key in the map
                char* value = "?"; // Default to "?" if not found
                for (int k = 0; k < knowledgeSize; k++) {
                    if (strcmp(map[k].key, key) == 0) {
                        value = map[k].value;
                        break;
                    }
                }

                // Append the value to the result
                int valueLen = strlen(value);
                strncpy(result + resIndex, value, valueLen);
                resIndex += valueLen;

                i = j; // Move past the closing bracket
            }
        } else {
            result[resIndex++] = s[i]; // Copy regular characters
        }
    }
    result[resIndex] = '\0';        
    free(map);
    return result;
}
