// Source: https://leetcode.com/problems/find-the-length-of-the-longest-common-prefix/   |   Difficulty: Medium
//
// Problem Description:
// You are given two arrays with positive integers arr1 and arr2.
//
// A prefix of a positive integer is an integer formed by one or more of its digits, starting from its leftmost digit. For example, 123 is a prefix of the integer 12345, while 234 is not.
//
// A common prefix of two integers a and b is an integer c, such that c is a prefix of both a and b. For example, 5655359 and 56554 have common prefixes 565 and 5655 while 1223 and 43456 do not have a common prefix.
//
// You need to find the length of the longest common prefix between all pairs of integers (x, y) such that x belongs to arr1 and y belongs to arr2.
//
// Return the length of the longest common prefix among all pairs. If no common prefix exists among them, return 0.
//
// Example:
// Input: arr1 = [1,10,100], arr2 = [1000]
// Output: 3
// Explanation: There are 3 pairs (arr1[i], arr2[j]):
// - The longest common prefix of (1, 1000) is 1.
// - The longest common prefix of (10, 1000) is 10.
// - The longest common prefix of (100, 1000) is 100.
// The longest common prefix is 100 with a length of 3.
//
// Constraints:
// 1 <= arr1.length, arr2.length <= 5 * 104
// 	1 <= arr1[i], arr2[i] <= 108
//
// Helpful references (internal KB):
// - Tries (trie, tree, trie-match)
//   • When to use: Use when managing a collection of strings and requiring efficient prefix-based operations like search, insertion, deletion, or finding the longest common prefix.
//   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set of strings, where nodes represent characters and paths from the root represent strings. Operations like insertion, search, and deletion typically take O(L) time, where L is the length of the key.
//   • Invariants: Every path from the root to a node represents a unique prefix.; A node's children pointers correspond to the next character in a string.
//   • Tips: Mark nodes as 'end of word' to distinguish prefixes from complete words.; Use an array for children pointers if the alphabet size is small and fixed (e.g., ASCII).
//   • Pitfalls: High memory consumption for large alphabets or very deep tries due to many empty child pointers.; Deletion can be complex, requiring careful handling of nodes that are part of other words.
// - Longest increasing subsequence (array, dp-1d)
//   • When to use: Use when finding the maximum length of a subsequence where elements are strictly increasing. It's suitable for problems requiring ordered selection from a sequence.
//   • Idea: This algorithm finds the longest subsequence of a given sequence such that all elements of the subsequence are sorted in increasing order. The standard DP approach has a time complexity of O(N^2).
//   • Invariants: At the start of iteration `i`, `dp[j]` for `j < i` stores the length of the LIS ending at `arr[j]`.; After processing `arr[i]`, `dp[i]` holds the length of the LIS ending with `arr[i]`.
//   • Tips: Initialize DP array with 1s, as each element is an LIS of length 1.; Iterate through all previous elements to find potential predecessors.
//   • Pitfalls: Forgetting to initialize the DP array correctly.; Incorrectly handling strict versus non-strict increasing conditions.
// - Linear Diophantine Equation (number, interval, enumeration)
//   • When to use: Use when you need to find or count all integer solutions (x, y) for a linear Diophantine equation ax + by = c, especially when solutions are constrained within specific intervals for x and y.
//   • Idea: This method finds all integer solutions to a linear Diophantine equation ax + by = c within given x and y intervals. It first finds a particular solution, then uses properties of the general solution to determine the valid range for x, and enumerates solutions in O(N) time where N is the number of solutions.
//   • Invariants: The current (x, y) pair always satisfies the linear Diophantine equation ax + by = c.; The current x value is an integer and satisfies the effective bounds l_x <= x <= r_x.
//   • Tips: Pre-divide coefficients a, b, c by gcd(a, b) to simplify the equation.; Use the Extended Euclidean Algorithm to find an initial particular solution (x0, y0).
//   • Pitfalls: Failing to check if c is divisible by gcd(a, b) before proceeding, leading to incorrect results.; Incorrectly applying the shifting logic for x and y bounds, resulting in an invalid solution range.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int longestCommonPrefix(vector<int>& arr1, vector<int>& arr2) {
        struct TrieNode {
            TrieNode* children[10];
            TrieNode() {
                for (int i = 0; i < 10; ++i) children[i] = nullptr;
            }
        };

        TrieNode* root = new TrieNode();

        auto insert = [&](int num) {
            TrieNode* node = root;
            vector<int> digits;
            while (num > 0) {
                digits.push_back(num % 10);
                num /= 10;
            }
            for (int i = digits.size() - 1; i >= 0; --i) {
                int d = digits[i];
                if (!node->children[d]) {
                    node->children[d] = new TrieNode();
                }
                node = node->children[d];
            }
        };

        for (int num : arr1) {
            insert(num);
        }

        int maxPrefixLength = 0;

        for (int num : arr2) {
            TrieNode* node = root;
            vector<int> digits;
            while (num > 0) {
                digits.push_back(num % 10);
                num /= 10;
            }
            int currentLength = 0;
            for (int i = digits.size() - 1; i >= 0; --i) {
                int d = digits[i];
                if (node->children[d]) {
                    currentLength++;
                    node = node->children[d];
                } else {
                    break;
                }
            }
            if (currentLength > maxPrefixLength) {
                maxPrefixLength = currentLength;
            }
        }

        // Clean up trie memory
        function<void(TrieNode*)> deleteTrie = [&](TrieNode* node) {
            for (int i = 0; i < 10; ++i) {
                if (node->children[i]) {
                    deleteTrie(node->children[i]);
                }
            }
            delete node;
        };
        deleteTrie(root);

        return maxPrefixLength;         
    }
};
