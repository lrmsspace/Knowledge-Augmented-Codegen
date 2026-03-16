// Source: https://leetcode.com/problems/count-the-repetitions/   |   Difficulty: Hard
//
// Problem Description:
// We define str = [s, n] as the string str which consists of the string s concatenated n times.
//
//
// 	For example, str == ["abc", 3] =="abcabcabc".
//
//
// We define that string s1 can be obtained from string s2 if we can remove some characters from s2 such that it becomes s1.
//
//
// 	For example, s1 = "abc" can be obtained from s2 = "abdbec" based on our definition by removing the bolded underlined characters.
//
//
// You are given two strings s1 and s2 and two integers n1 and n2. You have the two strings str1 = [s1, n1] and str2 = [s2, n2].
//
// Return the maximum integer m such that str = [str2, m] can be obtained from str1.
//
// Example:
// Input: s1 = "acb", n1 = 4, s2 = "ab", n2 = 2
// Output: 2
//
// Constraints:
// 1 <= s1.length, s2.length <= 100
// 	s1 and s2 consist of lowercase English letters.
// 	1 <= n1, n2 <= 106
//
// Helpful references (internal KB):
// - Substring Search (string, array, two-pointers, simulation)
//   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
//   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
//   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
//   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
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
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int len1 = s1.size(), len2 = s2.size();
        vector<int> next(len2, 0);
        for (int i = 1, j = 0; i < len2; i++) {
            while (j > 0 && s2[i] != s2[j]) j = next[j - 1];
            if (s2[i] == s2[j]) j++;
            next[i] = j;
        }
        vector<int> count(len2, 0), index(len2, 0);
        for (int i = 0, j = 0; i < len1 * n1; i++) {
            while (j > 0 && s1[i % len1] != s2[j]) j = next[j - 1];
            if (s1[i % len1] == s2[j]) j++;
            if (j == len2) {
                count[j - 1]++;
                j = next[j - 1];
            }
            index[i % len1] = j;
        }
        int res = count[len2 - 1] / n2;
        for (int i = 0; i < len1; i++) {
            int preCount = count[index[i]];
            int cycleCount = count[len2 - 1] - preCount;
            if (cycleCount == 0) continue;
            int cycleLength = len1 * n1 - i;
            int cycles = (len1 * n1 - i) / cycleLength;
            int totalCount = preCount + cycleCount * cycles;
            res = max(res, totalCount / n2);
        }
        return res;         
    }
};
