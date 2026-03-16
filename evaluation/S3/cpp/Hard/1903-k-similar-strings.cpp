// Source: https://leetcode.com/problems/k-similar-strings/   |   Difficulty: Hard
//
// Problem Description:
// Strings s1 and s2 are k-similar (for some non-negative integer k) if we can swap the positions of two letters in s1 exactly k times so that the resulting string equals s2.
//
// Given two anagrams s1 and s2, return the smallest k for which s1 and s2 are k-similar.
//
// Example:
// Input: s1 = "ab", s2 = "ba"
// Output: 1
// Explanation: The two string are 1-similar because we can use one swap to change s1 to s2: "ab" --> "ba".
//
// Constraints:
// 1 <= s1.length <= 20
// 	s2.length == s1.length
// 	s1 and s2 contain only lowercase letters from the set {'a', 'b', 'c', 'd', 'e', 'f'}.
// 	s2 is an anagram of s1.
//
// Helpful references (internal KB):
// - Aho-Corasick Algorithm for Pattern Searching (trie, queue, bitset, aho-corasick, bfs)
//   • When to use: Use when searching for multiple patterns simultaneously within a larger text. It is highly efficient for finding all occurrences of a dictionary of keywords.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a set of patterns, allowing efficient simultaneous searching for all patterns in a text. It typically achieves O(N + M + K) time complexity, where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: All patterns in the dictionary are correctly represented as paths in the trie structure.; For any state `s`, its failure link `fail[s]` points to the longest proper prefix of the string represented by `s` that is also a suffix of `s` and exists in the trie.
//   • Tips: Build the trie first from all patterns, representing each pattern as a path.; Use BFS to construct failure links, pointing to the longest proper prefix of the current state's string that is also a suffix.
//   • Pitfalls: Incorrectly building failure links can lead to wrong matches or infinite loops.; High memory usage if the pattern set is very large or patterns are excessively long.
// - Multi source BFS (queue, graph, multi-source-bfs, bfs)
//   • When to use: Use when you need to find the shortest distance from any of a given set of source nodes to all other reachable nodes in an unweighted graph or grid.
//   • Idea: Multi-source BFS explores a graph or grid by starting from multiple initial nodes simultaneously, finding the shortest path from any of these sources to all other reachable nodes. It operates in O(V + E) time for graphs or O(rows * cols) for grids.
//   • Invariants: All nodes currently in the queue are at the same shortest distance level from any source.; When a node `u` is dequeued, `dist[u]` represents the finalized shortest distance from any source to `u`.
//   • Tips: Initialize distances for all sources to 0 and add them to the queue.; Use a `visited` array or set to prevent redundant processing of nodes.
//   • Pitfalls: Forgetting to mark initial sources as visited before adding to the queue.; Incorrectly initializing distances for non-source nodes (should be infinity or a large value).
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int kSimilarity(string s1, string s2) {
        if (s1 == s2) return 0; 
        int n = s1.size();
        queue<string> q;
        unordered_set<string> visited;
        q.push(s1);
        visited.insert(s1);
        int steps = 0;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                string curr = q.front();
                q.pop();
                if (curr == s2) return steps;
                int j = 0;
                while (curr[j] == s2[j]) ++j; 
                for (int k = j + 1; k < n; ++k) {
                    if (curr[k] == s2[j] && curr[k] != s2[k]) {
                        swap(curr[j], curr[k]);
                        if (!visited.count(curr)) {
                            visited.insert(curr);
                            q.push(curr);
                        }
                        swap(curr[j], curr[k]); 
                    }
                }
            }
            ++steps;
        }
        return -1;
    }
};
