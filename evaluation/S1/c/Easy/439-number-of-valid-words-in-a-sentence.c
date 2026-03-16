// Source: https://leetcode.com/problems/number-of-valid-words-in-a-sentence/   |   Difficulty: Easy
//
// Problem Description:
// A sentence consists of lowercase letters ('a' to 'z'), digits ('0' to '9'), hyphens ('-'), punctuation marks ('!', '.', and ','), and spaces (' ') only. Each sentence can be broken down into one or more tokens separated by one or more spaces ' '.
//
// A token is a valid word if all three of the following are true:
//
//
// 	It only contains lowercase letters, hyphens, and/or punctuation (no digits).
// 	There is at most one hyphen '-'. If present, it must be surrounded by lowercase characters ("a-b" is valid, but "-ab" and "ab-" are not valid).
// 	There is at most one punctuation mark. If present, it must be at the end of the token ("ab,", "cd!", and "." are valid, but "a!b" and "c.," are not valid).
//
//
// Examples of valid words include "a-b.", "afad", "ba-c", "a!", and "!".
//
// Given a string sentence, return the number of valid words in sentence.
//
// Example:
// Input: sentence = "cat and  dog"
// Output: 3
// Explanation: The valid words in the sentence are "cat", "and", and "dog".
//
// Constraints:
// 1 <= sentence.length <= 1000
// 	sentence only contains lowercase English letters, digits, ' ', '-', '!', '.', and ','.
// 	There will be at least 1 token.
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - Balanced bracket sequences (number, counting)
//   • When to use: Use this when verifying if a sequence of delimiters is correctly nested and balanced. It is also applicable for counting or generating all possible valid sequences of a given length.
//   • Idea: This algorithm involves checking if a sequence of opening and closing delimiters is properly matched and nested, or enumerating such sequences. Validation typically uses a stack in O(N) time, while generation often involves backtracking with O(Catalan(N)) complexity.
//   • Invariants: The stack contains only opening delimiters that are yet to be matched.; The balance counter (open - close) is never negative at any point during traversal.
//   • Tips: Use a stack to track unmatched opening delimiters for validation.; Maintain a balance counter (increment for open, decrement for close) for a simpler check.
//   • Pitfalls: Forgetting to check if the stack is empty after processing the entire sequence.; Allowing a closing delimiter when no matching opening delimiter is available (empty stack or mismatch).
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countValidWords(char* sentence) {
    int count = 0;
    char* token = strtok(sentence, " ");
    while (token != NULL) {
        int len = strlen(token);
        int hyphen_count = 0;
        int punctuation_count = 0;
        int is_valid = 1;

        for (int i = 0; i < len; i++) {
            char c = token[i];
            if (isdigit(c)) {
                is_valid = 0;
                break;
            } else if (c == '-') {
                hyphen_count++;
                if (hyphen_count > 1 || i == 0 || i == len - 1 || !islower(token[i - 1]) || !islower(token[i + 1])) {
                    is_valid = 0;
                    break;
                }
            } else if (c == '!' || c == '.' || c == ',') {
                punctuation_count++;
                if (punctuation_count > 1 || i != len - 1) {
                    is_valid = 0;
                    break;
                }
            } else if (!islower(c)) {
                is_valid = 0;
                break;
            }
        }

        if (is_valid) {
            count++;
        }

        token = strtok(NULL, " ");
    }

    return count;       
}
