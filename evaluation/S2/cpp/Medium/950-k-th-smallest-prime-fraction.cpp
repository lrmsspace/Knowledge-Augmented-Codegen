// Source: https://leetcode.com/problems/k-th-smallest-prime-fraction/   |   Difficulty: Medium
//
// Problem Description:
// You are given a sorted integer array arr containing 1 and prime numbers, where all the integers of arr are unique. You are also given an integer k.
//
// For every i and j where 0 <= i < j < arr.length, we consider the fraction arr[i] / arr[j].
//
// Return the kth smallest fraction considered. Return your answer as an array of integers of size 2, where answer[0] == arr[i] and answer[1] == arr[j].
//
// Example:
// Input: arr = [1,2,3,5], k = 3
// Output: [2,5]
// Explanation: The fractions to be considered in sorted order are:
// 1/5, 1/3, 2/5, 1/2, 3/5, and 2/3.
// The third fraction is 2/5.
//
// Constraints:
// 2 <= arr.length <= 1000
// 	1 <= arr[i] <= 3 * 104
// 	arr[0] == 1
// 	arr[i] is a prime number for i > 0.
// 	All the numbers of arr are unique and sorted in strictly increasing order.
// 	1 <= k <= arr.length * (arr.length - 1) / 2
//
//
//  
// Follow up: Can you solve the problem with better than O(n2) complexity?
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - The Stern-Brocot tree and Farey sequences (number, tree, binary-search, simulation)
//   • When to use: Use when you need to represent all positive irreducible fractions in a structured tree or efficiently search for a specific fraction. It's also useful for generating Farey sequences or understanding rational number properties.
//   • Idea: The Stern-Brocot tree is an infinite binary tree containing every positive irreducible fraction exactly once, ordered by value. Searching for a fraction or generating parts of the tree typically involves a logarithmic number of steps relative to the sum of the numerator and denominator, making it efficient for O(log(x+y)) operations.
//   • Invariants: For any node m/n, all fractions in its left subtree are strictly less than m/n.; For any node m/n, all fractions in its right subtree are strictly greater than m/n.
//   • Tips: The mediant of a/b and c/d is (a+c)/(b+d), which is always irreducible if a/b and c/d are.; All fractions in the Stern-Brocot tree are inherently irreducible.
//   • Pitfalls: Integer overflow when calculating mediants if numerators or denominators are very large.; Incorrectly handling the initial 'infinite' fractions (0/1 and 1/0) as boundary conditions.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) {
        int n = arr.size();
        auto compare = [&](const pair<int, int>& a, const pair<int, int>& b) {
            return arr[a.first] * arr[b.second] > arr[b.first] * arr[a.second];
        };
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compare)> min_heap(compare);
        
        for (int j = 1; j < n; ++j) {
            min_heap.emplace(0, j);
        }
        
        for (int i = 0; i < k - 1; ++i) {
            auto [p, q] = min_heap.top();
            min_heap.pop();
            if (p + 1 < q) {
                min_heap.emplace(p + 1, q);
            }
        }
        
        auto [p, q] = min_heap.top();
        return {arr[p], arr[q]};            
    }
};
