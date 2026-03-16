// Source: https://leetcode.com/problems/longest-unequal-adjacent-groups-subsequence-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string array words, and an array groups, both arrays having length n.
//
// The hamming distance between two strings of equal length is the number of positions at which the corresponding characters are different.
//
// You need to select the longest subsequence from an array of indices [0, 1, ..., n - 1], such that for the subsequence denoted as [i0, i1, ..., ik-1] having length k, the following holds:
//
//
// 	For adjacent indices in the subsequence, their corresponding groups are unequal, i.e., groups[ij] != groups[ij+1], for each j where 0 < j + 1 < k.
// 	words[ij] and words[ij+1] are equal in length, and the hamming distance between them is 1, where 0 < j + 1 < k, for all indices in the subsequence.
//
//
// Return a string array containing the words corresponding to the indices (in order) in the selected subsequence. If there are multiple answers, return any of them.
//
// Note: strings in words may be unequal in length.
//
// Example:
// Input: words = ["bab","dab","cab"], groups = [1,2,2]
//
// Output: ["bab","cab"]
//
// Explanation: A subsequence that can be selected is [0,2].
//
//
// 	groups[0] != groups[2]
// 	words[0].length == words[2].length, and the hamming distance between them is 1.
//
//
// So, a valid answer is [words[0],words[2]] = ["bab","cab"].
//
// Another subsequence that can be selected is [0,1].
//
//
// 	groups[0] != groups[1]
// 	words[0].length == words[1].length, and the hamming distance between them is 1.
//
//
// So, another valid answer is [words[0],words[1]] = ["bab","dab"].
//
// It can be shown that the length of the longest subsequence of indices that satisfies the conditions is 2.
//
// Constraints:
// 1 <= n == words.length == groups.length <= 1000
// 	1 <= words[i].length <= 10
// 	1 <= groups[i] <= n
// 	words consists of distinct strings.
// 	words[i] consists of lowercase English letters.
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use to efficiently represent all suffixes of a string in a compressed form, ideal for various string problems like pattern matching or counting distinct substrings.
//   • Idea: A suffix automaton is a minimal Deterministic Finite Automaton (DFA) that accepts all suffixes of a given string, offering O(N) time construction and O(N) memory complexity.
//   • Invariants: Every state in the automaton represents a set of substrings of the original string.; Each state's longest path from the initial state corresponds to its longest string.
//   • Tips: Understand the definition of states and transitions, and their relationship to substrings.; Leverage its linear time and space complexity for efficient string processing on large inputs.
//   • Pitfalls: The construction algorithm can be complex and challenging to implement correctly.; Debugging state transitions, suffix links, and their properties requires careful attention.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
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
char** getWordsInLongestSubsequence(char** words, int wordsSize, int* groups, int groupsSize, int* returnSize) {
    int dp[wordsSize];
    int prev[wordsSize];
    for (int i = 0; i < wordsSize; i++) {
        dp[i] = 1;
        prev[i] = -1;
    }

    int maxLen = 1;
    int maxEnd = 0;

    for (int i = 1; i < wordsSize; i++) {
        for (int j = 0; j < i; j++) {
            if (groups[i] != groups[j] &&
                strlen(words[i]) == strlen(words[j])) {
                int hammingDist = 0;
                for (int k = 0; k < strlen(words[i]); k++) {
                    if (words[i][k] != words[j][k]) {
                        hammingDist++;
                    }
                    if (hammingDist > 1) {
                        break;
                    }
                }
                if (hammingDist == 1 && dp[j] + 1 > dp[i]) {
                    dp[i] = dp[j] + 1;
                    prev[i] = j;
                }
            }
        }
        if (dp[i] > maxLen) {
            maxLen = dp[i];
            maxEnd = i;
        }
    }

    char** result = (char**)malloc(maxLen * sizeof(char*));
    int index = maxLen - 1;
    int current = maxEnd;

    while (current != -1) {
        result[index--] = words[current];
        current = prev[current];
    }

    *returnSize = maxLen;
    return result;      
}
