// Source: https://leetcode.com/problems/k-divisible-elements-subarrays/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array nums and two integers k and p, return the number of distinct subarrays, which have at most k elements that are divisible by p.
//
// Two arrays nums1 and nums2 are said to be distinct if:
//
//
// 	They are of different lengths, or
// 	There exists at least one index i where nums1[i] != nums2[i].
//
//
// A subarray is defined as a non-empty contiguous sequence of elements in an array.
//
// Example:
// Input: nums = [2,3,3,2,2], k = 2, p = 2
// Output: 11
// Explanation:
// The elements at indices 0, 3, and 4 are divisible by p = 2.
// The 11 distinct subarrays which have at most k = 2 elements divisible by 2 are:
// [2], [2,3], [2,3,3], [2,3,3,2], [3], [3,3], [3,3,2], [3,3,2,2], [3,2], [3,2,2], and [2,2].
// Note that the subarrays [2] and [3] occur more than once in nums, but they should each be counted only once.
// The subarray [2,3,3,2,2] should not be counted because it has 3 elements that are divisible by 2.
//
// Constraints:
// 1 <= nums.length <= 200
// 	1 <= nums[i], p <= 200
// 	1 <= k <= nums.length
//
//
//  
// Follow up:
//
// Can you solve this problem in O(n2) time complexity?
//
// Helpful references (internal KB):
// - Tries (trie, array, trie-match)
//   • When to use: Use when managing string keys in a symbol table and needing efficient prefix, wildcard, or longest prefix matching operations, offering flexibility beyond binary search trees and speed comparable to hashing.
//   • Idea: A trie (prefix tree) is a tree-like data structure used to store a dynamic set or associative array where keys are typically strings. It allows for efficient retrieval of keys based on their prefixes, achieving O(L) time complexity for operations, where L is the key length.
//   • Invariants: Every path from the root to a node represents a unique prefix.; A node exists only if it is part of at least one stored key.
//   • Tips: Choose an appropriate branching factor (R) based on the alphabet size.; Represent children using arrays for fixed alphabets or hash maps for sparse ones.
//   • Pitfalls: High memory consumption for large alphabets or sparse data.; Deletion of keys can be complex, requiring careful handling of empty branches.
// - Search the subarray with the maximum/minimum sum (array, prefix-sum, max-window)
//   • When to use: When needing to find the maximum or minimum sum of any contiguous subarray within a given array efficiently. It is particularly useful for problems requiring an O(N) solution.
//   • Idea: This algorithm finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array, maintaining a running prefix sum, and tracking the minimum (or maximum) prefix sum encountered so far. It achieves an optimal O(N) time complexity with O(1) auxiliary space.
//   • Invariants: max_global_sum stores the maximum subarray sum found among all subarrays ending at or before the current element.; min_prefix_sum_value correctly tracks the minimum prefix sum encountered up to the previous element's prefix sum.
//   • Tips: Use a running sum variable instead of explicitly storing the entire prefix sum array.; Keep track of the minimum prefix sum encountered up to the current point.
//   • Pitfalls: Incorrectly initializing the minimum prefix sum (e.g., to INT_MAX instead of 0 or s[0]).; Off-by-one errors when calculating subarray sums using prefix sums (s[r] - s[l-1]).
// - Primality tests (number, enumeration, simulation)
//   • When to use: When you need to determine if a single number is prime, especially for numbers where trial division up to its square root is computationally feasible.
//   • Idea: A number is prime if it has no divisors other than 1 and itself. This method checks for primality by attempting to find a non-trivial divisor up to the square root of the given number, running in O(sqrt(N)) time.
//   • Invariants: No integer k in the range [2, current_divisor - 1] has been found to divide n.; The current value current_divisor is a candidate divisor being tested against n.
//   • Tips: Only check numbers between 2 and sqrt(n).; Handle 2 as a special case before iterating.
//   • Pitfalls: O(sqrt(N)) complexity can be too slow for very large numbers.; Incorrectly handling edge cases like 0, 1, or 2.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int countDistinct(int* nums, int numsSize, int k, int p) {
    // Trie node structure
    typedef struct TrieNode {
        struct TrieNode* children[201];
    } TrieNode;

    // Function to create a new trie node
    TrieNode* createNode() {
        TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
        for (int i = 0; i < 201; i++) {
            node->children[i] = NULL;
        }
        return node;
    }

    TrieNode* root = createNode();
    int distinctCount = 0;

    // Iterate over all possible starting points of subarrays
    for (int start = 0; start < numsSize; start++) {
        TrieNode* currentNode = root;
        int divisibleCount = 0;

        // Iterate over all possible ending points of subarrays
        for (int end = start; end < numsSize; end++) {
            if (nums[end] % p == 0) {
                divisibleCount++;
            }
            if (divisibleCount > k) {
                break;
            }

            // Insert the current number into the trie
            if (currentNode->children[nums[end]] == NULL) {
                currentNode->children[nums[end]] = createNode();
                distinctCount++;
            }
            currentNode = currentNode->children[nums[end]];
        }
    }

    // Free the trie nodes
    void freeTrie(TrieNode* node) {
        if (node == NULL) return;
        for (int i = 0; i < 201; i++) {
            freeTrie(node->children[i]);
        }
        free(node);
    }
    freeTrie(root);

    return distinctCount;       
}
