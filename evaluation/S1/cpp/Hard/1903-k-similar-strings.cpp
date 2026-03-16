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
// - Breadth-first search (graph, queue, array, bfs)
//   • When to use: Use when finding the shortest path in an unweighted graph or when exploring all reachable nodes level by level. It is also suitable for problems requiring traversal of all nodes at a specific distance from a source.
//   • Idea: Breadth-first search systematically explores a graph level by level, ensuring that all nodes at distance k are visited before any nodes at distance k+1. It finds the shortest path in terms of number of edges for unweighted graphs in O(V + E) time.
//   • Invariants: All nodes currently in the queue have been discovered and marked, but their adjacent nodes have not yet been fully explored.; For any node v marked as visited, distTo[v] stores the shortest path length from the source s to v.
//   • Tips: Use a queue to manage nodes to visit.; Mark nodes as visited to prevent cycles and redundant processing.
//   • Pitfalls: Forgetting to mark nodes as visited can lead to infinite loops or incorrect paths.; Not handling disconnected graphs correctly.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: When needing to efficiently represent all substrings of a given string and perform various string operations like counting distinct substrings, finding occurrences, or checking for specific patterns. It provides a compact and powerful data structure for complex string problems.
//   • Idea: A Suffix Automaton is a minimal deterministic finite automaton that recognizes all suffixes of a given string. It compactly represents all substrings of the string, with each state corresponding to an endpos-equivalence class, and can be constructed in linear time O(N).
//   • Invariants: Every state corresponds to a unique endpos-equivalence class of substrings.; For any state, all substrings ending at its endpos set are represented by that state or its ancestors via suffix links.
//   • Tips: Focus on the endpos definition for state equivalence.; Understand the incremental construction process.
//   • Pitfalls: The construction algorithm is non-trivial and prone to off-by-one errors.; Misinterpreting the role of suffix links vs. transition links.
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
        queue<pair<string, int>> q;
        unordered_set<string> visited;
        q.push({s1, 0});
        visited.insert(s1);
        while (!q.empty()) {
            auto [curr, steps] = q.front();
            q.pop();
            int i = 0;
            while (i < n && curr[i] == s2[i]) ++i;
            for (int j = i + 1; j < n; ++j) {
                if (curr[j] == s2[i] && curr[j] != s2[j]) {
                    swap(curr[i], curr[j]);
                    if (curr == s2) return steps + 1;
                    if (visited.find(curr) == visited.end()) {
                        visited.insert(curr);
                        q.push({curr, steps + 1});
                    }
                    swap(curr[i], curr[j]);
                }
            }
        }
        return -1;          
    }
};
