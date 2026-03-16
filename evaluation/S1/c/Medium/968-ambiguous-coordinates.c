// Source: https://leetcode.com/problems/ambiguous-coordinates/   |   Difficulty: Medium
//
// Problem Description:
// We had some 2-dimensional coordinates, like "(1, 3)" or "(2, 0.5)". Then, we removed all commas, decimal points, and spaces and ended up with the string s.
//
//
// 	For example, "(1, 3)" becomes s = "(13)" and "(2, 0.5)" becomes s = "(205)".
//
//
// Return a list of strings representing all possibilities for what our original coordinates could have been.
//
// Our original representation never had extraneous zeroes, so we never started with numbers like "00", "0.0", "0.00", "1.0", "001", "00.01", or any other number that can be represented with fewer digits. Also, a decimal point within a number never occurs without at least one digit occurring before it, so we never started with numbers like ".1".
//
// The final answer list can be returned in any order. All coordinates in the final answer have exactly one space between them (occurring after the comma.)
//
// Example:
// Input: s = "(123)"
// Output: ["(1, 2.3)","(1, 23)","(1.2, 3)","(12, 3)"]
//
// Constraints:
// 4 <= s.length <= 12
// 	s[0] == '(' and s[s.length - 1] == ')'.
// 	The rest of s are digits.
//
// Helpful references (internal KB):
// - Balanced Ternary (number, string, enumeration, simulation)
//   • When to use: Use when a number system is required that can represent both positive and negative integers symmetrically without an explicit sign bit, or for specific arithmetic properties.
//   • Idea: Balanced ternary is a non-standard positional numeral system using digits -1 (Z), 0, and 1. The conversion from decimal typically involves an intermediate standard ternary representation, then iteratively adjusting digits from least significant to most significant with carry operations, achieving O(log N) time complexity.
//   • Invariants: All digits to the right of the current processing position are already in valid balanced ternary form (Z, 0, or 1).; The sum of the value represented by the processed digits and the value represented by the remaining digits (including current carry) equals the original number.
//   • Tips: First convert the decimal number to standard ternary (base 3).; Process digits from right to left (least significant to most significant).
//   • Pitfalls: Forgetting to propagate carries correctly, especially when a '2' or '3' appears.; Incorrectly handling the sign of 'Z' (-1) during back-conversion to decimal.
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
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** ambiguousCoordinates(char* s, int* returnSize) {
    int len = strlen(s);
    char **results = NULL;
    int resultSize = 0;
    int capacity = 0;

    void generateNumbers(char *str, int start, int end, char ***out, int *outSize, int *outCap) {
        int length = end - start + 1;
        if (length == 1 || str[start] != '0') {
            if (*outSize >= *outCap) {
                int newCap = (*outCap == 0) ? 16 : (*outCap) * 2;
                *out = realloc(*out, newCap * sizeof(char*));
                *outCap = newCap;
            }
            char *num = (char*)malloc((length + 1) * sizeof(char));
            strncpy(num, str + start, length);
            num[length] = '\0';
            (*out)[(*outSize)++] = num;
        }
        for (int i = start + 1; i <= end; i++) {
            if (str[start] == '0' && i - start > 1) break;
            if (str[end] == '0') continue;
            if (*outSize >= *outCap) {
                int newCap = (*outCap == 0) ? 16 : (*outCap) * 2;
                *out = realloc(*out, newCap * sizeof(char*));
                *outCap = newCap;
            }
            char *num = (char*)malloc((length + 2) * sizeof(char));
            strncpy(num, str + start, i - start);
            num[i - start] = '.';
            strncpy(num + i - start + 1, str + i, end - i + 1);
            num[length + 1] = '\0';
            (*out)[(*outSize)++] = num;
        }
    }

    for (int i = 2; i < len - 1; i++) {
        char **leftNums = NULL;
        int leftSize = 0, leftCap = 0;
        generateNumbers(s, 1, i - 1, &leftNums, &leftSize, &leftCap);

        char **rightNums = NULL;
        int rightSize = 0, rightCap = 0;
        generateNumbers(s, i, len - 2, &rightNums, &rightSize, &rightCap);
        for (int j = 0; j < leftSize; j++) {
            for (int k = 0; k < rightSize; k++) {
                if (resultSize >= capacity) {
                    int newCap = (capacity == 0) ? 16 : capacity * 2;
                    results = realloc(results, newCap * sizeof(char*));
                    capacity = newCap;
                }
                int totalLen = strlen(leftNums[j]) + strlen(rightNums[k]) + 4;
                char *coord = (char*)malloc(totalLen * sizeof(char));
                snprintf(coord, totalLen, "(%s, %s)", leftNums[j], rightNums[k]);
                results[resultSize++] = coord;
            }
        }
        for (int j = 0; j < leftSize; j++) {
            free(leftNums[j]);
        }
        free(leftNums);
        for (int j = 0; j < rightSize; j++) {
            free(rightNums[j]);
        }
        free(rightNums);
    }
    *returnSize = resultSize;
    return results;
}
