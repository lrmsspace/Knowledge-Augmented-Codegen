// Source: https://leetcode.com/problems/minimum-reverse-operations/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n and an integer p representing an array arr of length n where all elements are set to 0's, except position p which is set to 1. You are also given an integer array banned containing restricted positions. Perform the following operation on arr:
//
//
// 	Reverse a subarray with size k if the single 1 is not set to a position in banned.
//
//
// Return an integer array answer with n results where the ith result is the minimum number of operations needed to bring the single 1 to position i in arr, or -1 if it is impossible.
//
// Example:
// Input: n = 4, p = 0, banned = [1,2], k = 4
//
// Output: [0,-1,-1,1]
//
// Explanation:
//
//
// 	Initially 1 is placed at position 0 so the number of operations we need for position 0 is 0.
// 	We can never place 1 on the banned positions, so the answer for positions 1 and 2 is -1.
// 	Perform the operation of size 4 to reverse the whole array.
// 	After a single operation 1 is at position 3 so the answer for position 3 is 1.
//
// Constraints:
// 1 <= n <= 105
// 	0 <= p <= n - 1
// 	0 <= banned.length <= n - 1
// 	0 <= banned[i] <= n - 1
// 	1 <= k <= n 
// 	banned[i] != p
// 	all values in banned are unique
//
// Helpful references (internal KB):
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
// - Manacher's Algorithm - Finding all sub-p (string, array, enumeration)
//   • When to use: Use when you need to find all palindromic substrings within a given string, or determine the longest palindromic substring, in optimal linear time.
//   • Idea: Manacher's Algorithm efficiently finds the length of the longest palindromic substring centered at each position in a given string, handling both odd and even lengths uniformly via preprocessing. It achieves this in optimal O(N) time complexity.
//   • Invariants: p[i] correctly stores the radius of the longest palindrome centered at i in the transformed string.; The right_boundary always marks the rightmost extent of the largest palindrome found so far.
//   • Tips: Preprocess the string with a unique delimiter to unify odd and even length palindromes.; Leverage the mirror property around the current center to initialize palindrome radii.
//   • Pitfalls: Off-by-one errors when converting `p` array values back to original string indices or lengths.; Incorrectly handling the boundaries of the preprocessed string.
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> minReverseOperations(int n, int p, vector<int>& banned, int k) {
        vector<int> ans(n, -1);
        ans[p] = 0;
        set<int> even, odd;
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                even.insert(i);
            } else {
                odd.insert(i);
            }
        }
        for (int b : banned) {
            if (b % 2 == 0) {
                even.erase(b);
            } else {
                odd.erase(b);
            }
        }

        queue<int> q;
        q.push(p);
        while (!q.empty()) {
            int i = q.front();
            q.pop();
            int left_bound = max(i - k + 1, k - 1 - i);
            int right_bound = min(i + k - 1, n - k + i);
            auto& s = (left_bound % 2 == 0 ? even : odd);
            for (auto it = s.lower_bound(left_bound); it != s.upper_bound(right_bound); ) {
                int j = *it;
                ans[j] = ans[i] + 1;
                q.push(j);
                it = s.erase(it);
            }
        }
        return ans;         
    }
};
