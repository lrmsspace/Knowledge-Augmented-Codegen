// Source: https://leetcode.com/problems/super-palindromes/   |   Difficulty: Hard
//
// Problem Description:
// Let's say a positive integer is a super-palindrome if it is a palindrome, and it is also the square of a palindrome.
//
// Given two positive integers left and right represented as strings, return the number of super-palindromes integers in the inclusive range [left, right].
//
// Example:
// Input: left = "4", right = "1000"
// Output: 4
// Explanation: 4, 9, 121, and 484 are superpalindromes.
// Note that 676 is not a superpalindrome: 26 * 26 = 676, but 26 is not a palindrome.
//
// Constraints:
// 1 <= left.length, right.length <= 18
// 	left and right consist of only digits.
// 	left and right cannot have leading zeros.
// 	left and right represent integers in the range [1, 1018 - 1].
// 	left is less than or equal to right.
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int superpalindromesInRange(char* left, char* right) {
    long long l = atoll(left);
    long long r = atoll(right);
    int count = 0;

    /* Generate palindromic roots and check their squares */
    for (int len = 1; len <= 9; len++) {
        int start = (len == 1) ? 1 : pow(10, (len - 1) / 2);
        int end = pow(10, (len + 1) / 2);
        for (int root = start; root < end; root++) {
            char str[20];
            sprintf(str, "%d", root);
            // Create odd-length palindrome
            char rev[20];
            int slen = strlen(str);
            for (int i = 0; i < slen - 1; i++) {
                rev[i] = str[slen - 2 - i];
            }
            rev[slen - 1] = '\0';
            strcat(str, rev);
            long long palin = atoll(str);
            long long square = palin * palin;
            if (square > r) break;
            if (square >= l) {
                // Check if square is palindrome
                char sqStr[40];
                sprintf(sqStr, "%lld", square);
                int leftIdx = 0, rightIdx = strlen(sqStr) - 1;
                int isPalin = 1;
                while (leftIdx < rightIdx) {
                    if (sqStr[leftIdx++] != sqStr[rightIdx--]) {
                        isPalin = 0;
                        break;
                    }
                }
                if (isPalin) count++;
            }

            // Create even-length palindrome
            sprintf(str, "%d", root);
            for (int i = 0; i < slen; i++) {
                rev[i] = str[slen - 1 - i];
            }
            rev[slen] = '\0';
            strcat(str, rev);
            palin = atoll(str);
            square = palin * palin;
            if (square > r) continue;
            if (square >= l) {
                // Check if square is palindrome
                char sqStr[40];
                sprintf(sqStr, "%lld", square);
                int leftIdx = 0, rightIdx = strlen(sqStr) - 1;
                int isPalin = 1;
                while (leftIdx < rightIdx) {
                    if (sqStr[leftIdx++] != sqStr[rightIdx--]) {
                        isPalin = 0;
                        break;
                    }
                }
                if (isPalin) count++;
            }

        }
    }
    return count;
}
