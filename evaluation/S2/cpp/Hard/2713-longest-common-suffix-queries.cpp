// Source: https://leetcode.com/problems/longest-common-suffix-queries/   |   Difficulty: Hard
//
// Problem Description:
// You are given two arrays of strings wordsContainer and wordsQuery.
//
// For each wordsQuery[i], you need to find a string from wordsContainer that has the longest common suffix with wordsQuery[i]. If there are two or more strings in wordsContainer that share the longest common suffix, find the string that is the smallest in length. If there are two or more such strings that have the same smallest length, find the one that occurred earlier in wordsContainer.
//
// Return an array of integers ans, where ans[i] is the index of the string in wordsContainer that has the longest common suffix with wordsQuery[i].
//
// Example:
// Input: wordsContainer = ["abcd","bcd","xbcd"], wordsQuery = ["cd","bcd","xyz"]
//
// Output: [1,1,1]
//
// Explanation:
//
// Let's look at each wordsQuery[i] separately:
//
//
// 	For wordsQuery[0] = "cd", strings from wordsContainer that share the longest common suffix "cd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
// 	For wordsQuery[1] = "bcd", strings from wordsContainer that share the longest common suffix "bcd" are at indices 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
// 	For wordsQuery[2] = "xyz", there is no string from wordsContainer that shares a common suffix. Hence the longest common suffix is "", that is shared with strings at index 0, 1, and 2. Among these, the answer is the string at index 1 because it has the shortest length of 3.
//
// Constraints:
// 1 <= wordsContainer.length, wordsQuery.length <= 104
// 	1 <= wordsContainer[i].length <= 5 * 103
// 	1 <= wordsQuery[i].length <= 5 * 103
// 	wordsContainer[i] consists only of lowercase English letters.
// 	wordsQuery[i] consists only of lowercase English letters.
// 	Sum of wordsContainer[i].length is at most 5 * 105.
// 	Sum of wordsQuery[i].length is at most 5 * 105.
//
// Helpful references (internal KB):
// - Suffix array (array, string, suffix-array, binary-search)
//   • When to use: Use suffix arrays for efficient string processing tasks like finding all occurrences of a pattern, locating the longest common substring, or performing various substring queries. It provides a sorted index of all suffixes.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing their starting indices in lexicographical order. It enables various string operations to be performed efficiently, often with O(N log N) or O(N) time complexity for construction and O(M log N) or O(M) for queries.
//   • Invariants: The suffix array A always contains N elements, where N is the length of the original string.; For any valid index i, A[i] stores a starting position within the original string S.
//   • Tips: Append a unique sentinel character (e.g., '$') to the string to ensure all suffixes are distinct.; Combine with a Longest Common Prefix (LCP) array for enhanced functionality, such as counting distinct substrings.
//   • Pitfalls: Naive construction by sorting all suffixes directly is inefficient (O(N^2 log N) or worse).; Implementing advanced construction algorithms from scratch can be complex and error-prone.
// - Aho-Corasick algorithm (trie, graph, dfs, trie-match)
//   • When to use: Use when searching for all occurrences of a fixed set of multiple patterns within a larger text efficiently. It is ideal for problems requiring simultaneous matching of a dictionary of strings.
//   • Idea: The Aho-Corasick algorithm constructs a finite automaton from a dictionary of patterns, enabling efficient simultaneous searching for all pattern occurrences within a given text. It operates in O(N + M + K) time, where N is text length, M is total pattern length, and K is total matches.
//   • Invariants: Every node in the trie represents a prefix of at least one pattern.; A suffix link from node 'u' points to the node representing the longest proper suffix of 'u' that is also a prefix of some pattern.
//   • Tips: Build the trie for all patterns first, then compute suffix links.; Use BFS to construct suffix links level by level for efficiency.
//   • Pitfalls: Incorrectly building suffix links, especially for the root's children or when no direct transition exists.; High memory consumption if using arrays for transitions with a very large alphabet.
// - Substring Search (string, array, two-pointers, simulation)
//   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
//   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
//   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
//   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> stringIndices(vector<string>& wordsContainer, vector<string>& wordsQuery) {
        int n = wordsContainer.size(), m = wordsQuery.size();
        vector<int> ans(m, -1);
        unordered_map<string, pair<int, int>> suffixMap; // suffix -> (index, length)

        // Build the suffix map from wordsContainer
        for (int i = 0; i < n; ++i) {
            const string& word = wordsContainer[i];
            int len = word.length();
            for (int j = 0; j <= len; ++j) {
                string suffix = word.substr(len - j);
                if (suffixMap.find(suffix) == suffixMap.end() || 
                    suffixMap[suffix].second > len || 
                    (suffixMap[suffix].second == len && suffixMap[suffix].first > i)) {
                    suffixMap[suffix] = {i, len};
                }
            }
        }

        // Process each query
        for (int i = 0; i < m; ++i) {
            const string& query = wordsQuery[i];
            int len = query.length();
            for (int j = 0; j <= len; ++j) {
                string suffix = query.substr(len - j);
                if (suffixMap.find(suffix) != suffixMap.end()) {
                    ans[i] = suffixMap[suffix].first;
                    break;
                }
            }
        }

        return ans;         
    }
};
