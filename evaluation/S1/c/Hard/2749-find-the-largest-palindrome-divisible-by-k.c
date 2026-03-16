// Source: https://leetcode.com/problems/find-the-largest-palindrome-divisible-by-k/   |   Difficulty: Hard
//
// Problem Description:
// You are given two positive integers n and k.
//
// An integer x is called k-palindromic if:
//
//
// 	x is a palindrome.
// 	x is divisible by k.
//
//
// Return the largest integer having n digits (as a string) that is k-palindromic.
//
// Note that the integer must not have leading zeros.
//
// Example:
// Input: n = 3, k = 5
//
// Output: "595"
//
// Explanation:
//
// 595 is the largest k-palindromic integer with 3 digits.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= k <= 9
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

char* largestPalindrome(int n, int k) {
    if (n == 1) {
        /* Single digit case: largest digit divisible by k */
        for (int d = 9; d >= 1; d--) {
            if (d % k == 0) {
                char *res = (char*)malloc(2 * sizeof(char));
                res[0] = '0' + d; res[1] = '\0';
                return res;
            }
        }
        return "-1"; /* No single digit divisible by k */
    }

    /* Construct the largest half palindrome */
    int halfLen = (n + 1) / 2;
    char *half = (char*)malloc((halfLen + 1) * sizeof(char));
    for (int i = 0; i < halfLen; i++) {
        half[i] = '9';
    }
    half[halfLen] = '\0';

    /* Generate palindromes and check divisibility */
    while (1) {
        /* Form the full palindrome */
        char *palindrome = (char*)malloc((n + 1) * sizeof(char));
        strcpy(palindrome, half);
        for (int i = n / 2 - 1; i >= 0; i--) {
            palindrome[n - 1 - i] = palindrome[i];
        }
        palindrome[n] = '\0';

        /* Convert to integer and check divisibility */
        long long num = 0;
        for (int i = 0; i < n; i++) {
            num = num * 10 + (palindrome[i] - '0');
            if (num >= 10000000000000000LL) break; /* Prevent overflow */
        }
        if (num % k == 0) {
            free(half);
            return palindrome;
        }
        free(palindrome);

        /* Decrement the half palindrome */
        int idx = halfLen - 1;
        while (idx >= 0) {
            if (half[idx] > '0') {
                half[idx]--;
                break;
            } else {
                half[idx] = '9';
                idx--;
            }
        }
        if (idx < 0 || half[0] == '0') {
            break; /* No valid palindrome found */
        }
    }

    free(half);
    return "-1"; /* No k-palindromic number found */        
}
