// Source: https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s. In one step you can insert any character at any index of the string.
//
// Return the minimum number of steps to make s palindrome.
//
// A Palindrome String is one that reads the same backward as well as forward.
//
// Example:
// Input: s = "zzazz"
// Output: 0
// Explanation: The string "zzazz" is already palindrome we do not need any insertions.
//
// Constraints:
// 1 <= s.length <= 500
// 	s consists of lowercase English letters.
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
// - Suffix Automaton (graph, string, counting)
//   • When to use: Use when processing all suffixes or substrings of a string, especially for tasks requiring counting distinct substrings or efficient pattern matching. It is particularly useful for incremental string construction.
//   • Idea: The Suffix Automaton is a directed acyclic graph that represents all distinct substrings of a given string. It has a linear number of states and transitions, allowing for efficient string processing in O(N) time complexity for construction.
//   • Invariants: The automaton correctly represents all distinct substrings of the string processed up to the current character.; Each state corresponds to an equivalence class of substrings sharing the same end positions.
//   • Tips: Mark terminal states by traversing suffix links from the state representing the full string.; The `last` pointer always tracks the state for the entire string processed.
//   • Pitfalls: Incorrectly handling the three cases for adding a new character can lead to an invalid automaton.; Forgetting to update the `last` state after each character addition breaks incremental construction.
// - palindrome-partitioning (string, array, backtracking, recursion)
//   • When to use: Use this when you need to find all possible ways to break down a string into parts, where each part must satisfy a specific property. It is suitable for generating all combinations or permutations with constraints.
//   • Idea: This algorithm recursively explores all possible ways to partition a string into substrings, ensuring each substring is a palindrome. It employs a backtracking approach to build valid partitions incrementally, typically resulting in exponential time complexity.
//   • Invariants: At the start of each recursive call, the 'step' list contains a valid palindrome partition for the string segment processed so far.; The current processing index (or remaining string) always points to the unpartitioned suffix of the original input string.
//   • Tips: Utilize a helper function to manage additional state, such as the current partition path and the overall result list.; Pass the remaining string or a start index to recursive calls to define the subproblem for subsequent partitioning.
//   • Pitfalls: Forgetting to create a new copy of the current partition path before adding it to the final result list, leading to incorrect results.; Incorrectly defining the base case for recursion, which can cause infinite loops or missed valid partitions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minInsertions(string s) {
        int n = s.size();
        vector<vector<int>> dp(n, vector<int>(n, 0));

        for (int i = n - 1; i >= 0; --i) {
            for (int j = i + 1; j < n; ++j) {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1];
                } else {
                    dp[i][j] = min(dp[i + 1][j], dp[i][j - 1]) + 1;
                }
            }
        }

        return dp[0][n - 1];            
    }
};
