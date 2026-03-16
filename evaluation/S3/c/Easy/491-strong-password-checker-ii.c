// Source: https://leetcode.com/problems/strong-password-checker-ii/   |   Difficulty: Easy
//
// Problem Description:
// A password is said to be strong if it satisfies all the following criteria:
//
//
// 	It has at least 8 characters.
// 	It contains at least one lowercase letter.
// 	It contains at least one uppercase letter.
// 	It contains at least one digit.
// 	It contains at least one special character. The special characters are the characters in the following string: "!@#$%^&*()-+".
// 	It does not contain 2 of the same character in adjacent positions (i.e., "aab" violates this condition, but "aba" does not).
//
//
// Given a string password, return true if it is a strong password. Otherwise, return false.
//
// Example:
// Input: password = "IloveLe3tcode!"
// Output: true
// Explanation: The password meets all the requirements. Therefore, we return true.
//
// Constraints:
// 1 <= password.length <= 100
// 	password consists of letters, digits, and special characters: "!@#$%^&*()-+".
//
// Helpful references (internal KB):
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Balanced bracket sequences (number, counting)
//   • When to use: Use this when verifying if a sequence of delimiters is correctly nested and balanced. It is also applicable for counting or generating all possible valid sequences of a given length.
//   • Idea: This algorithm involves checking if a sequence of opening and closing delimiters is properly matched and nested, or enumerating such sequences. Validation typically uses a stack in O(N) time, while generation often involves backtracking with O(Catalan(N)) complexity.
//   • Invariants: The stack contains only opening delimiters that are yet to be matched.; The balance counter (open - close) is never negative at any point during traversal.
//   • Tips: Use a stack to track unmatched opening delimiters for validation.; Maintain a balance counter (increment for open, decrement for close) for a simpler check.
//   • Pitfalls: Forgetting to check if the stack is empty after processing the entire sequence.; Allowing a closing delimiter when no matching opening delimiter is available (empty stack or mismatch).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

bool strongPasswordCheckerII(char* password) {
    int len = 0;
    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;
    char prevChar = '\0';

    while (password[len] != '\0') {
        char c = password[len];

        if (c >= 'a' && c <= 'z') {
            hasLower = true;
        } else if (c >= 'A' && c <= 'Z') {
            hasUpper = true;
        } else if (c >= '0' && c <= '9') {
            hasDigit = true;
        } else if (strchr("!@#$%^&*()-+", c) != NULL) {
            hasSpecial = true;
        }

        if (c == prevChar) {
            return false; // Adjacent characters are the same
        }
        prevChar = c;
        len++;
    }

    return len >= 8 && hasLower && hasUpper && hasDigit && hasSpecial;      
}
