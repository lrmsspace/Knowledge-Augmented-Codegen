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
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - String Hashing (string, number, hashing, prefix-sum)
//   • When to use: Use string hashing to efficiently compare strings, find duplicate strings, or perform fast substring searches and pattern matching in O(1) time after initial O(N) preprocessing.
//   • Idea: String hashing maps a string to a numerical value using a polynomial function, enabling O(1) comparison of strings or substrings after O(N) preprocessing.
//   • Invariants: prefix_hash[i] stores the polynomial hash of the substring s[0...i-1].; p_power[k] stores p^k mod m for efficient calculation.
//   • Tips: Use two different hash functions with distinct prime `p` and `m` values to minimize collision probability.; Precompute powers of `p` and prefix hashes to enable O(1) substring hash calculation.
//   • Pitfalls: Hash collisions can lead to incorrect results; always consider their possibility.; Integer overflow if modulo operations are not applied correctly at each step of calculation.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* evaluate(char* s, char*** knowledge, int knowledgeSize, int* knowledgeColSize) {
    // Create a hash map to store the key-value pairs from knowledge
    char* hashMap[knowledgeSize][2];
    for (int i = 0; i < knowledgeSize; i++) {
        hashMap[i][0] = knowledge[i][0]; // key
        hashMap[i][1] = knowledge[i][1]; // value
    }

    // Create a result string buffer
    char* result = (char*)malloc(sizeof(char) * (strlen(s) + 1));
    int resIndex = 0;

    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == '(') {
            // Extract the key inside the brackets
            char key[11]; // max key length is 10 + null terminator
            int keyIndex = 0;
            i++; // move past '('

            while (s[i] != ')' && s[i] != '\0') {
                key[keyIndex++] = s[i++];
            }
            key[keyIndex] = '\0'; // null terminate the key

            // Search for the key in the hash map
            char* value = "?"; // default value if key is not found
            for (int j = 0; j < knowledgeSize; j++) {
                if (strcmp(hashMap[j][0], key) == 0) {
                    value = hashMap[j][1];
                    break;
                }
            }

            // Append the value to the result
            for (int k = 0; value[k] != '\0'; k++) {
                result[resIndex++] = value[k];
            }
        } else {
            // Append regular characters to the result
            result[resIndex++] = s[i];
        }
    }
    result[resIndex] = '\0'; // null terminate the result

    return result;      
}
