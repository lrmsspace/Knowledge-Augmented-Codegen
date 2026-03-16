// Source: https://leetcode.com/problems/string-compression-ii/   |   Difficulty: Hard
//
// Problem Description:
// Run-length encoding is a string compression method that works by replacing consecutive identical characters (repeated 2 or more times) with the concatenation of the character and the number marking the count of the characters (length of the run). For example, to compress the string "aabccc" we replace "aa" by "a2" and replace "ccc" by "c3". Thus the compressed string becomes "a2bc3".
//
// Notice that in this problem, we are not adding '1' after single characters.
//
// Given a string s and an integer k. You need to delete at most k characters from s such that the run-length encoded version of s has minimum length.
//
// Find the minimum length of the run-length encoded version of s after deleting at most k characters.
//
// Example:
// Input: s = "aaabcccd", k = 2
// Output: 4
// Explanation: Compressing s without deleting anything will give us "a3bc3d" of length 6. Deleting any of the characters 'a' or 'c' would at most decrease the length of the compressed string to 5, for instance delete 2 'a' then we will have s = "abcccd" which compressed is abc3d. Therefore, the optimal way is to delete 'b' and 'd', then the compressed version of s will be "a3c3" of length 4.
//
// Constraints:
// 1 <= s.length <= 100
// 	0 <= k <= s.length
// 	s contains only lowercase English letters.
//
// Helpful references (internal KB):
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Data Compression (trie, array, trie-match, greedy, simulation)
//   • When to use: When needing to reduce the size of data by encoding frequently occurring patterns or symbols with shorter representations, especially for lossless compression of text or binary streams.
//   • Idea: Data compression algorithms like Huffman coding and LZW reduce data size by assigning variable-length codes based on frequency or by replacing repeated patterns with shorter references. Huffman coding typically involves O(N log N) for building the tree and O(N) for encoding/decoding, while LZW can be O(N) for both, where N is the input size.
//   • Invariants: The encoding process consistently maps input symbols or sequences to their assigned codes.; The decoding process reconstructs the original data by traversing the encoding structure using the compressed bitstream.
//   • Tips: Use a min-priority queue to efficiently build the Huffman tree from character frequencies.; Represent Huffman codes as bit strings for efficient storage and transmission.
//   • Pitfalls: Incorrectly handling edge cases like empty input or single-character input.; Off-by-one errors when reading/writing bit streams.
// - Number of paths of fixed length / Shortest paths of fixed length (graph, simulation, counting, floyd-warshall)
//   • When to use: Use this approach when you need to count the number of paths or find the shortest path between two nodes in a graph, specifically constrained to an exact number of edges or at most a certain number of edges.
//   • Idea: This technique leverages matrix exponentiation on an adjacency matrix to find paths of a fixed length k. For problems involving paths of length up to k, the graph is modified by duplicating vertices and adding specific edges.
//   • Invariants: After p matrix multiplications, M^p[i][j] represents the count/shortest path length between i and j using exactly p edges.; The modified graph for 'at most k' paths ensures a path of length m <= k in the original graph corresponds to a path of length k+1 in the new graph.
//   • Tips: For exactly K edges, compute the K-th power of the adjacency matrix.; For at most K edges, duplicate each vertex v to v' and add edges (v, v') and (v', v') with appropriate weights (1 for counting, 0 for shortest path).
//   • Pitfalls: Naive matrix multiplication is O(N^3), leading to high complexity for large N.; Incorrectly handling edge weights (e.g., for shortest paths) can lead to wrong results.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int getLengthOfOptimalCompression(char* s, int k) {
    int n = strlen(s);
    int dp[n + 1][k + 1];
    memset(dp, 0x3f, sizeof(dp));
    dp[0][0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            int same = 0, diff = 0;
            for (int l = i; l >= 1; --l) {
                if (s[l - 1] == s[i - 1]) {
                    ++same;
                } else {
                    ++diff;
                }
                if (diff > j) {
                    break;
                }
                dp[i][j] = fmin(dp[i][j], dp[l - 1][j - diff] + 1 + (same >= 100 ? 3 : same >= 10 ? 2 : same >= 2 ? 1 : 0));
            }
        }
    }

    return dp[n][k];        
}
