// Source: https://leetcode.com/problems/minimum-changes-to-make-k-semi-palindromes/   |   Difficulty: Hard
//
// Problem Description:
// Given a string s and an integer k, partition s into k substrings such that the letter changes needed to make each substring a semi-palindrome are minimized.
//
// Return the minimum number of letter changes required.
//
// A semi-palindrome is a special type of string that can be divided into palindromes based on a repeating pattern. To check if a string is a semi-palindrome:​
//
//
// 	Choose a positive divisor d of the string's length. d can range from 1 up to, but not including, the string's length. For a string of length 1, it does not have a valid divisor as per this definition, since the only divisor is its length, which is not allowed.
// 	For a given divisor d, divide the string into groups where each group contains characters from the string that follow a repeating pattern of length d. Specifically, the first group consists of characters at positions 1, 1 + d, 1 + 2d, and so on; the second group includes characters at positions 2, 2 + d, 2 + 2d, etc.
// 	The string is considered a semi-palindrome if each of these groups forms a palindrome.
//
//
// Consider the string "abcabc":
//
//
// 	The length of "abcabc" is 6. Valid divisors are 1, 2, and 3.
// 	For d = 1: The entire string "abcabc" forms one group. Not a palindrome.
// 	For d = 2:
// 	
// 		Group 1 (positions 1, 3, 5): "acb"
// 		Group 2 (positions 2, 4, 6): "bac"
// 		Neither group forms a palindrome.
// 	
// 	
// 	For d = 3:
// 	
// 		Group 1 (positions 1, 4): "aa"
// 		Group 2 (positions 2, 5): "bb"
// 		Group 3 (positions 3, 6): "cc"
// 		All groups form palindromes. Therefore, "abcabc" is a semi-palindrome.
//
// Example:
// Input:   s = "abcac", k = 2 
//
// Output:   1 
//
// Explanation:  Divide s into "ab" and "cac". "cac" is already semi-palindrome. Change "ab" to "aa", it becomes semi-palindrome with d = 1.
//
// Constraints:
// 2 <= s.length <= 200
// 	1 <= k <= s.length / 2
// 	s contains only lowercase English letters.
//
// Helpful references (internal KB):
// - Manacher's Algorithm - Finding all sub-p (string, array, simulation, enumeration)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring within a given string efficiently. It is particularly useful for achieving linear time complexity for this task.
//   • Idea: Manacher's algorithm finds all maximal palindromic substrings centered at each position in a string by leveraging symmetry and previously computed results. It achieves an optimal O(N) time complexity.
//   • Invariants: d_odd[i] stores the radius of the longest odd-length palindrome centered at i.; The (l, r) interval always defines the rightmost palindrome found so far.
//   • Tips: Preprocess the string with delimiters to unify odd and even length palindromes.; Maintain the current rightmost boundary `r` of the largest palindrome found.
//   • Pitfalls: Forgetting to update the `(l, r)` boundaries after processing each center.; Incorrectly calculating mirror positions or handling boundary cases for `i > r`.
// - Manacher's Algorithm - Finding all sub-p (string, array, two-pointers, simulation)
//   • When to use: When you need to find all palindromic substrings or the longest palindromic substring in a given string efficiently. It is particularly useful for achieving linear time complexity by leveraging symmetry.
//   • Idea: Manacher's algorithm finds all palindromic substrings in a string by expanding around centers and utilizing symmetry to avoid redundant comparisons. It achieves a linear time complexity of O(N) by maintaining the rightmost boundary of the longest palindrome found so far.
//   • Invariants: For any index k < i, d[k] correctly stores the radius of the longest palindrome centered at k.; The pair (l, r) always represents the exclusive boundaries of the palindrome that extends furthest to the right among all processed centers.
//   • Tips: Pre-process the string with delimiters (e.g., '#') to uniformly handle both odd and even length palindromes.; Leverage symmetry: for a center 'i' within the current rightmost palindrome, its mirror 'j' provides a lower bound for the palindrome length at 'i'.
//   • Pitfalls: Incorrectly handling boundary conditions when the mirror palindrome extends beyond the current rightmost palindrome.; Forgetting to update the 'l' and 'r' boundaries after finding a new palindrome that extends further to the right.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        vector<vector<int>> freq(k, vector<int>(26, 0));
        
        for (int i = 0; i < n; ++i) {
            freq[i % k][s[i] - 'a']++;
        }
        
        int changes = 0;
        for (int i = 0; i < k; ++i) {
            int maxFreq = 0;
            for (int j = 0; j < 26; ++j) {
                maxFreq = max(maxFreq, freq[i][j]);
            }
            changes += (n / k + (i < n % k ? 1 : 0)) - maxFreq;
        }
        
        return changes;         
    }
};
