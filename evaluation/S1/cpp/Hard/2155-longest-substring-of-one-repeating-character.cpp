// Source: https://leetcode.com/problems/longest-substring-of-one-repeating-character/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed string s. You are also given a 0-indexed string queryCharacters of length k and a 0-indexed array of integer indices queryIndices of length k, both of which are used to describe k queries.
//
// The ith query updates the character in s at index queryIndices[i] to the character queryCharacters[i].
//
// Return an array lengths of length k where lengths[i] is the length of the longest substring of s consisting of only one repeating character after the ith query is performed.
//
// Example:
// Input: s = "babacc", queryCharacters = "bcb", queryIndices = [1,3,3]
// Output: [3,3,4]
// Explanation: 
// - 1st query updates s = "bbbacc". The longest substring consisting of one repeating character is "bbb" with length 3.
// - 2nd query updates s = "bbbccc". 
//   The longest substring consisting of one repeating character can be "bbb" or "ccc" with length 3.
// - 3rd query updates s = "bbbbcc". The longest substring consisting of one repeating character is "bbbb" with length 4.
// Thus, we return [3,3,4].
//
// Constraints:
// 1 <= s.length <= 105
// 	s consists of lowercase English letters.
// 	k == queryCharacters.length == queryIndices.length
// 	1 <= k <= 105
// 	queryCharacters consists of lowercase English letters.
// 	0 <= queryIndices[i] < s.length
//
// Helpful references (internal KB):
// - Longest increasing subsequence (array, dp-1d, counting, segment-tree)
//   • When to use: Use when seeking the longest possible sequence of elements from a given array such that each element is greater than the preceding one, preserving their original relative order.
//   • Idea: The Longest Increasing Subsequence (LIS) problem identifies the longest possible subsequence where elements are in strictly increasing order, preserving their original relative positions. It can be solved efficiently in O(N log N) time using dynamic programming with binary search or a segment tree.
//   • Invariants: The `tails` array elements are always strictly increasing.; For any index `k`, `tails[k]` holds the smallest possible ending element of an increasing subsequence of length `k+1`.
//   • Tips: Use a `tails` array to store the smallest ending element for LIS of each length.; Employ binary search on the `tails` array to update or extend subsequences.
//   • Pitfalls: Confusing subsequence (relative order) with contiguous subarray.; Incorrectly implementing strict vs. non-strict increasing conditions.
// - Suffix Automaton (graph, string, simulation)
//   • When to use: Use to efficiently represent all suffixes of a string in a compressed form, ideal for various string problems like pattern matching or counting distinct substrings.
//   • Idea: A suffix automaton is a minimal Deterministic Finite Automaton (DFA) that accepts all suffixes of a given string, offering O(N) time construction and O(N) memory complexity.
//   • Invariants: Every state in the automaton represents a set of substrings of the original string.; Each state's longest path from the initial state corresponds to its longest string.
//   • Tips: Understand the definition of states and transitions, and their relationship to substrings.; Leverage its linear time and space complexity for efficient string processing on large inputs.
//   • Pitfalls: The construction algorithm can be complex and challenging to implement correctly.; Debugging state transitions, suffix links, and their properties requires careful attention.
// - Deleting from a data structure in_log_n (ds, segment-tree, dfs, recursion)
//   • When to use: Use when processing a sequence of additions, deletions, and queries offline, where elements have specific time intervals of existence. It efficiently handles dynamic data structure operations by leveraging a segment tree over time.
//   • Idea: This technique uses a segment tree over the timeline of queries to manage elements with varying lifespans. Queries are processed offline via DFS, adding elements upon entering a node and undoing additions upon exiting, achieving O(T(n) log n) deletion complexity.
//   • Invariants: When entering a segment tree node, all elements associated with that node's time range are added to the active data structure.; When exiting a segment tree node, all elements added upon entry are removed, restoring the data structure to its state before entering.
//   • Tips: Ensure the base data structure supports efficient addition and undo operations.; Carefully manage element additions and removals during DFS traversal.
//   • Pitfalls: Forgetting to undo changes when backtracking from a segment tree node.; Incorrectly mapping element lifespans to segment tree nodes.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        int n = s.size();
        vector<int> left(n), right(n);
        for (int i = 0, j = 0; i < n; i = j) {
            while (j < n && s[j] == s[i]) j++;
            for (int k = i; k < j; k++) {
                left[k] = i;
                right[k] = j - 1;
            }
        }

        struct Node {
            int l, r;
            int maxLen;
            Node* leftChild;
            Node* rightChild;

            Node(int l, int r) : l(l), r(r), maxLen(r - l + 1), leftChild(nullptr), rightChild(nullptr) {}

            void updateMaxLen() {
                maxLen = max(leftChild ? leftChild->maxLen : 0,
                             rightChild ? rightChild->maxLen : 0);
            }
        };

        function<Node*(int, int)> buildTree = [&](int l, int r) {
            Node* node = new Node(l, r);
            if (l < r) {
                int mid = (l + r) / 2;
                node->leftChild = buildTree(l, mid);
                node->rightChild = buildTree(mid + 1, r);
                node->updateMaxLen();
            }
            return node;
        };

        function<void(Node*, int, int)> updateTree = [&](Node* node, int pos, int len) {
            if (node->l == node->r) {
                node->maxLen = len;
                return;
            }
            int mid = (node->l + node->r) / 2;
            if (pos <= mid) {
                updateTree(node->leftChild, pos, len);
            } else {
                updateTree(node->rightChild, pos, len);
            }
            node->updateMaxLen();
        };

        Node* root = buildTree(0, n - 1);
        vector<int> result;

        for (int q = 0; q < queryCharacters.size(); q++) {
            int idx = queryIndices[q];
            char newChar = queryCharacters[q];
            if (s[idx] == newChar) {
                result.push_back(root->maxLen);
                continue;
            }

            s[idx] = newChar;

            int l = idx, r = idx;
            if (idx > 0 && s[idx - 1] == newChar) {
                l = left[idx - 1];
            }
            if (idx < n - 1 && s[idx + 1] == newChar) {
                r = right[idx + 1];
            }
            for (int i = l; i <= r; i++) {
                left[i] = l;
                right[i] = r;
            }
            updateTree(root, l, r - l + 1);
            result.push_back(root->maxLen);
        }
        return result;
    }
};
