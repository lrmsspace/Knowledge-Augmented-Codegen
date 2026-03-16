// Source: https://leetcode.com/problems/split-message-based-on-limit/   |   Difficulty: Hard
//
// Problem Description:
// You are given a string, message, and a positive integer, limit.
//
// You must split message into one or more parts based on limit. Each resulting part should have the suffix "<a/b>", where "b" is to be replaced with the total number of parts and "a" is to be replaced with the index of the part, starting from 1 and going up to b. Additionally, the length of each resulting part (including its suffix) should be equal to limit, except for the last part whose length can be at most limit.
//
// The resulting parts should be formed such that when their suffixes are removed and they are all concatenated in order, they should be equal to message. Also, the result should contain as few parts as possible.
//
// Return the parts message would be split into as an array of strings. If it is impossible to split message as required, return an empty array.
//
// Example:
// Input: message = "this is really a very awesome message", limit = 9
// Output: ["thi<1/14>","s i<2/14>","s r<3/14>","eal<4/14>","ly <5/14>","a v<6/14>","ery<7/14>"," aw<8/14>","eso<9/14>","me<10/14>"," m<11/14>","es<12/14>","sa<13/14>","ge<14/14>"]
// Explanation:
// The first 9 parts take 3 characters each from the beginning of message.
// The next 5 parts take 2 characters each to finish splitting message. 
// In this example, each part, including the last, has length 9. 
// It can be shown it is not possible to split message into less than 14 parts.
//
// Constraints:
// 1 <= message.length <= 104
// 	message consists only of lowercase English letters and ' '.
// 	1 <= limit <= 104
//
// Helpful references (internal KB):
// - Suffix Array (string, array, merge-sort)
//   • When to use: Use when needing to efficiently query properties of all suffixes or substrings of a given text, especially for pattern matching or finding repeated structures. It is particularly useful for problems requiring lexicographical ordering of all suffixes.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing their starting indices. It enables efficient string operations like pattern searching and finding longest common prefixes, typically constructed in O(N log N) time.
//   • Invariants: After k iterations, suffixes are sorted correctly up to a certain length (e.g., 2^k).; All suffixes of the original string are represented by their starting indices in the array.
//   • Tips: Append a unique sentinel character (e.g., '$') smaller than any other character to the string.; Utilize the LCP array, often built alongside, for advanced string queries and optimizations.
//   • Pitfalls: Naive sorting of suffixes by string comparison leads to an inefficient O(N^2 log N) complexity.; High memory usage for very long strings due to storing all suffixes implicitly or explicitly.
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
// - palindrome-partitioning (string, two-pointers, simulation)
//   • When to use: When a string needs to be decomposed into all possible sets of palindromic substrings. It's suitable for problems requiring exhaustive enumeration of such partitions.
//   • Idea: This algorithm finds all possible ways to partition a given string such that every substring in the partition is a palindrome. It typically uses a recursive exploration approach combined with a two-pointer check for palindrome validation, resulting in an exponential time complexity.
//   • Invariants: At any point, the `step` list contains a valid palindromic partition of the prefix processed so far.; The `s` parameter in the recursive function always represents the unpartitioned suffix of the original string.
//   • Tips: Implement the `isPalindrome` check efficiently using two pointers for O(length) time.; Use a recursive helper function to explore all possible partition points.
//   • Pitfalls: Incorrectly handling substring boundaries, leading to off-by-one errors or incorrect partitions.; Forgetting to backtrack (remove the last added substring) after a recursive call returns.
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
char** splitMessage(char* message, int limit, int* returnSize) {
    int msgLen = strlen(message);
    for (int totalParts = 1; totalParts <= msgLen; totalParts++) {
        int suffixLen = 3 + 2 * (totalParts >= 10 ? (totalParts >= 100 ? (totalParts >= 1000 ? 4 : 3) : 2) : 1);
        int contentLen = limit - suffixLen;
        if (contentLen <= 0) continue;

        int partsNeeded = (msgLen + contentLen - 1) / contentLen;
        if (partsNeeded > totalParts) continue;

        char **result = (char **)malloc(totalParts * sizeof(char *));
        int index = 0;
        for (int partIdx = 1; partIdx <= totalParts; partIdx++) {
            int takeLen = (index + contentLen <= msgLen) ? contentLen : (msgLen - index);
            if (takeLen < 0) takeLen = 0;

            result[partIdx - 1] = (char *)malloc((takeLen + suffixLen + 1) * sizeof(char));
            strncpy(result[partIdx - 1], message + index, takeLen);
            index += takeLen;

            sprintf(result[partIdx - 1] + takeLen, "<%d/%d>", partIdx, totalParts);
        }
        *returnSize = totalParts;
        return result;
    }
    *returnSize = 0;
    return NULL;        
}
