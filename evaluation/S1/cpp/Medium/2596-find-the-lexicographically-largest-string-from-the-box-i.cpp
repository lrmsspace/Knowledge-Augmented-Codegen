// Source: https://leetcode.com/problems/find-the-lexicographically-largest-string-from-the-box-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a string word, and an integer numFriends.
//
// Alice is organizing a game for her numFriends friends. There are multiple rounds in the game, where in each round:
//
//
// 	word is split into numFriends non-empty strings, such that no previous round has had the exact same split.
// 	All the split words are put into a box.
//
//
// Find the lexicographically largest string from the box after all the rounds are finished.
//
// Example:
// Input: word = "dbca", numFriends = 2
//
// Output: "dbc"
//
// Explanation: 
//
// All possible splits are:
//
//
// 	"d" and "bca".
// 	"db" and "ca".
// 	"dbc" and "a".
//
// Constraints:
// 1 <= word.length <= 5 * 103
// 	word consists only of lowercase English letters.
// 	1 <= numFriends <= word.length
//
// Helpful references (internal KB):
// - Suffix array (array, tree, string, suffix-array, tree-dp, lca)
//   • When to use: Use when needing to perform fast substring searches, pattern matching, or other string operations on a fixed text, especially when space efficiency is critical compared to suffix trees.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing only their starting indices. It is often paired with an LCP (Longest Common Prefix) array to enable efficient string algorithms, typically achieving O(N log N) or O(N) construction and O(M + log N) or O(M) search complexity.
//   • Invariants: The suffix array `A` stores indices such that `S[A[i]:]` is lexicographically smaller than `S[A[i+1]:]` for all valid `i`.; The `lcp[i]` value represents the length of the longest common prefix between `S[A[i-1]:]` and `S[A[i]:]`.
//   • Tips: Pair with an LCP array to significantly speed up pattern searching and other string queries.; Consider Enhanced Suffix Arrays (ESA) for improved space and time efficiency over suffix trees, especially for large datasets.
//   • Pitfalls: Naive pattern searching without LCP information can be O(M log N), which might be too slow for long patterns.; Construction can be complex to implement efficiently in linear time.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
// - Lyndon factorization (string, greedy, two-pointers)
//   • When to use: Use this algorithm to decompose a string into a unique sequence of Lyndon words, which are lexicographically smallest among their cyclic shifts. It is also applicable for finding the smallest cyclic shift of a string.
//   • Idea: The Duval algorithm greedily factorizes a string into a sequence of Lyndon words by maintaining three pointers to manage processed, pre-simple, and untouched parts. It achieves this in O(N) time complexity.
//   • Invariants: The prefix s[0...i-1] always contains a valid Lyndon factorization.; The substring s[i...j-1] is always a pre-simple string.
//   • Tips: Thoroughly understand the definitions of 'simple string' and 'pre-simple string' to correctly apply the comparison logic.; The three pointers (i, j, k) are crucial; 'i' marks the start of the current pre-simple string, 'j' the start of the untouched part, and 'k' for comparison within the pre-simple string.
//   • Pitfalls: Incorrectly resetting the 'k' pointer when s[j] > s[k], which should point back to the beginning of the simple word within s2.; Misinterpreting the length of the simple string (j - k) when a factorization step occurs.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    string answerString(string word, int numFriends) {
        int n = word.size();
        if (numFriends >= n) return string(1, *max_element(word.begin(), word.end()));

        // Duval's algorithm for Lyndon factorization
        string res;
        int i = 0;
        while (i < n) {
            int j = i + 1, k = i;
            while (j < n && word[k] <= word[j]) {
                if (word[k] < word[j]) k = i;
                else k++;
                j++;
            }
            while (i <= k) {
                res += word.substr(i, j - k);
                i += j - k;
            }
        }

        return res;         
    }
};
