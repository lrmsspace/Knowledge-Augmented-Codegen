// Source: https://leetcode.com/problems/final-array-state-after-k-multiplication-operations-i/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums, an integer k, and an integer multiplier.
//
// You need to perform k operations on nums. In each operation:
//
//
// 	Find the minimum value x in nums. If there are multiple occurrences of the minimum value, select the one that appears first.
// 	Replace the selected minimum value x with x * multiplier.
//
//
// Return an integer array denoting the final state of nums after performing all k operations.
//
// Example:
// Input: nums = [2,1,3,5,6], k = 5, multiplier = 2
//
// Output: [8,4,6,5,6]
//
// Explanation:
//
//
// 	
// 		
// 			Operation
// 			Result
// 		
// 		
// 			After operation 1
// 			[2, 2, 3, 5, 6]
// 		
// 		
// 			After operation 2
// 			[4, 2, 3, 5, 6]
// 		
// 		
// 			After operation 3
// 			[4, 4, 3, 5, 6]
// 		
// 		
// 			After operation 4
// 			[4, 4, 6, 5, 6]
// 		
// 		
// 			After operation 5
// 			[8, 4, 6, 5, 6]
//
// Constraints:
// 1 <= nums.length <= 100
// 	1 <= nums[i] <= 100
// 	1 <= k <= 10
// 	1 <= multiplier <= 5
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Modular Multiplicative Inverse (array, number, prefix-sum, mod-exp)
//   • When to use: Use when needing to compute modular inverses for multiple numbers in an array or a range, especially when efficiency is critical, by leveraging prefix and suffix products to reduce inverse computations.
//   • Idea: This technique efficiently computes modular inverses for multiple numbers by transforming individual inverse calculations into a product of prefix, suffix, and a single overall inverse. It achieves O(N + log M) complexity for an array or O(M) for a range.
//   • Invariants: For 0 <= i < N, prefix_products[i] holds (arr[0] * ... * arr[i-1]) % m.; For 0 <= i < N, suffix_products[i] holds (arr[i+1] * ... * arr[N-1]) % m.
//   • Tips: Precompute prefix products and suffix products of the array elements modulo m.; Calculate the modular inverse of the total product of all elements once using modular exponentiation.
//   • Pitfalls: Ensure all numbers for which an inverse is sought are coprime to the modulus m.; Watch for off-by-one errors when calculating prefix and suffix product indices.
// - Prüfer code (tree, array, simulation, two-pointers)
//   • When to use: When needing to encode a labeled tree into a unique sequence of N-2 numbers, particularly when an efficient linear-time construction is required.
//   • Idea: The Prüfer code algorithm converts a labeled tree with N vertices into a unique sequence of N-2 numbers by iteratively removing the smallest-numbered leaf and recording its neighbor. This process can be optimized to run in O(N) time.
//   • Invariants: After 'k' iterations, 'k' leaves have been removed and 'k' numbers have been added to the Prüfer code.; The current tree always contains 'N - k' vertices and 'N - k - 1' edges.
//   • Tips: Use a degree array to efficiently track vertex degrees.; Maintain a pointer to the current smallest leaf candidate for linear time.
//   • Pitfalls: Incorrectly identifying the smallest-numbered leaf after removals.; Not updating degrees correctly, leading to wrong leaf identification.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> getFinalState(vector<int>& nums, int k, int multiplier) {
        for (int i = 0; i < k; ++i) {
            int minIndex = 0;
            for (int j = 1; j < nums.size(); ++j) {
                if (nums[j] < nums[minIndex]) {
                    minIndex = j;
                }
            }
            nums[minIndex] *= multiplier;
        }
        return nums;            
    }
};
