// Source: https://leetcode.com/problems/find-the-closest-palindrome/   |   Difficulty: Hard
//
// Problem Description:
// Given a string n representing an integer, return the closest integer (not including itself), which is a palindrome. If there is a tie, return the smaller one.
//
// The closest is defined as the absolute difference minimized between two integers.
//
// Example:
// Input: n = "123"
// Output: "121"
//
// Constraints:
// 1 <= n.length <= 18
// 	n consists of only digits.
// 	n does not have leading zeros.
// 	n is representing an integer in the range [1, 1018 - 1].
//
// Helpful references (internal KB):
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
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

char* nearestPalindromic(char* n) {
    long long num = atoll(n);
    int len = strlen(n);
    long long candidates[5];
    int idx = 0;

    // Edge cases: 10..01 and 9..9
    candidates[idx++] = (long long)pow(10, len - 1) - 1; // 9..9
    candidates[idx++] = (long long)pow(10, len) + 1;     // 10..01

    // Get the prefix
    long long prefix = atoll(n) / (long long)pow(10, (len + 1) / 2);

    // Generate candidates by modifying the prefix
    for (int i = -1; i <= 1; i++) {
        long long newPrefix = prefix + i;
        char newPrefixStr[20];
        sprintf(newPrefixStr, "%lld", newPrefix);
        int newLen = strlen(newPrefixStr);

        // Build the palindrome
        char palinStr[40];
        strcpy(palinStr, newPrefixStr);
        for (int j = (len % 2 == 0 ? newLen - 1 : newLen - 2); j >= 0; j--) {
            palinStr[strlen(palinStr)] = newPrefixStr[j];
            palinStr[strlen(palinStr) + 1] = '\0';
        }
        candidates[idx++] = atoll(palinStr);
    }

    // Find the closest palindrome
    long long closest = -1;
    for (int i = 0; i < idx; i++) {
        if (candidates[i] != num) {
            if (closest == -1 ||
                llabs(candidates[i] - num) < llabs(closest - num) ||
                (llabs(candidates[i] - num) == llabs(closest - num) && candidates[i] < closest)) {
                closest = candidates[i];
            }
        }
    }

    // Convert closest to string
    char* result = (char*)malloc(20 * sizeof(char));
    sprintf(result, "%lld", closest);
    return result;      
}
