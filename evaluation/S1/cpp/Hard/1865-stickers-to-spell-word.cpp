// Source: https://leetcode.com/problems/stickers-to-spell-word/   |   Difficulty: Hard
//
// Problem Description:
// We are given n different types of stickers. Each sticker has a lowercase English word on it.
//
// You would like to spell out the given string target by cutting individual letters from your collection of stickers and rearranging them. You can use each sticker more than once if you want, and you have infinite quantities of each sticker.
//
// Return the minimum number of stickers that you need to spell out target. If the task is impossible, return -1.
//
// Note: In all test cases, all words were chosen randomly from the 1000 most common US English words, and target was chosen as a concatenation of two random words.
//
// Example:
// Input: stickers = ["with","example","science"], target = "thehat"
// Output: 3
// Explanation:
// We can use 2 "with" stickers, and 1 "example" sticker.
// After cutting and rearrange the letters of those stickers, we can form the target "thehat".
// Also, this is the minimum number of stickers necessary to form the target string.
//
// Constraints:
// n == stickers.length
// 	1 <= n <= 50
// 	1 <= stickers[i].length <= 10
// 	1 <= target.length <= 15
// 	stickers[i] and target consist of lowercase English letters.
//
// Helpful references (internal KB):
// - Introduction to Dynamic Programming (array, tree, recursion, dp-1d)
//   • When to use: Use when a problem has overlapping subproblems and optimal substructure, and a natural recursive solution is inefficient due to redundant computations. It's ideal for transforming exponential recursive solutions into polynomial time.
//   • Idea: Top-down dynamic programming, or memoization, optimizes recursive solutions by storing the results of expensive function calls and returning the cached result when the same inputs occur again. This technique typically reduces time complexity from exponential to polynomial, often O(N) or O(N*M).
//   • Invariants: memo[state] contains the computed result for 'state' if memo[state] is not the sentinel value.; If memo[state] is the sentinel value, the result for 'state' has not yet been computed.
//   • Tips: Initialize the memoization table with a sentinel value (e.g., -1, null) to distinguish uncomputed states from valid zero/false results.; Use arrays for lookup tables when the state space is contiguous and small for optimal cache performance.
//   • Pitfalls: Forgetting to initialize the memoization table, leading to incorrect results or infinite loops.; Incorrectly identifying or handling base cases in the recursive function.
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Counting labeled graphs (number, recursion, counting, dp-1d)
//   • When to use: When the problem requires enumerating distinct labeled graphs with specific properties, such as connectivity, on a given number of vertices. It is suitable for combinatorial counting problems involving graph structures.
//   • Idea: This technique determines the number of connected labeled graphs by subtracting the count of disconnected graphs from the total. It typically employs a recursive or dynamic programming approach, often involving combinatorial terms like binomial coefficients, with a polynomial time complexity.
//   • Invariants: The total number of labeled graphs $G_n$ for $n$ vertices is always $2^{n(n-1)/2}$.; For any $n$, the sum of connected and disconnected labeled graphs equals the total number of labeled graphs.
//   • Tips: Start with the total number of labeled graphs $G_n = 2^{n(n-1)/2}$.; Use complementary counting: total graphs minus disconnected graphs.
//   • Pitfalls: Forgetting to divide by $n$ when converting from rooted to unrooted disconnected graphs.; Incorrectly handling base cases for recursive definitions or DP states.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        const int n = stickers.size();
        const int m = target.size();
        const int FULL_MASK = (1 << m) - 1;

        // Preprocess stickers to count character frequencies
        vector<vector<int>> stickerCounts(n, vector<int>(26, 0));
        for (int i = 0; i < n; ++i) {
            for (char c : stickers[i]) {
                stickerCounts[i][c - 'a']++;
            }
        }

        // Memoization table
        vector<int> memo(1 << m, -1);
        memo[0] = 0; // Base case: 0 stickers needed to form empty target

        function<int(int)> dp = [&](int mask) -> int {
            if (memo[mask] != -1) return memo[mask];

            int ans = INT_MAX;
            for (int i = 0; i < n; ++i) {
                // Try using sticker i
                int newMask = mask;
                vector<int> targetCount(26, 0);
                for (int j = 0; j < m; ++j) {
                    if ((mask & (1 << j)) == 0) {
                        targetCount[target[j] - 'a']++;
                    }
                }

                // Apply sticker i
                for (int c = 0; c < 26; ++c) {
                    if (stickerCounts[i][c] > 0) {
                        int use = min(stickerCounts[i][c], targetCount[c]);
                        for (int j = 0; j < m; ++j) {
                            if (target[j] - 'a' == c && use > 0 && (newMask & (1 << j)) == 0) {
                                newMask |= (1 << j);
                                use--;
                            }
                        }
                    }
                }

                if (newMask != mask) {
                    int subProblem = dp(newMask);
                    if (subProblem != -1) {
                        ans = min(ans, 1 + subProblem);
                    }
                }
            }

            memo[mask] = (ans == INT_MAX) ? -1 : ans;
            return memo[mask];
        };

        return dp(0);           
    }
};
