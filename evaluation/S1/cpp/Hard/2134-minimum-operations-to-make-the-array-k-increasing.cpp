// Source: https://leetcode.com/problems/minimum-operations-to-make-the-array-k-increasing/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed array arr consisting of n positive integers, and a positive integer k.
//
// The array arr is called K-increasing if arr[i-k] <= arr[i] holds for every index i, where k <= i <= n-1.
//
//
// 	For example, arr = [4, 1, 5, 2, 6, 2] is K-increasing for k = 2 because:
//
// 	
// 		arr[0] <= arr[2] (4 <= 5)
// 		arr[1] <= arr[3] (1 <= 2)
// 		arr[2] <= arr[4] (5 <= 6)
// 		arr[3] <= arr[5] (2 <= 2)
// 	
// 	
// 	However, the same arr is not K-increasing for k = 1 (because arr[0] > arr[1]) or k = 3 (because arr[0] > arr[3]).
//
//
// In one operation, you can choose an index i and change arr[i] into any positive integer.
//
// Return the minimum number of operations required to make the array K-increasing for the given k.
//
// Example:
// Input: arr = [5,4,3,2,1], k = 1
// Output: 4
// Explanation:
// For k = 1, the resultant array has to be non-decreasing.
// Some of the K-increasing arrays that can be formed are [5,6,7,8,9], [1,1,1,1,1], [2,2,3,4,4]. All of them require 4 operations.
// It is suboptimal to change the array to, for example, [6,7,8,9,10] because it would take 5 operations.
// It can be shown that we cannot make the array K-increasing in less than 4 operations.
//
// Constraints:
// 1 <= arr.length <= 105
// 	1 <= arr[i], k <= arr.length
//
// Helpful references (internal KB):
// - Longest Increasing Subsequence (array, dp-1d, binary-search)
//   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order. It is often applied to optimization problems involving ordered subsets.
//   • Idea: The Longest Increasing Subsequence (LIS) problem finds the longest subsequence of a given sequence where all elements are sorted in increasing order. It can be solved in O(N log N) time using dynamic programming with binary search optimization, or O(N^2) using basic DP.
//   • Invariants: The 'tails' array always stores the smallest ending element for all increasing subsequences of a given length.; The 'tails' array remains sorted in strictly increasing order throughout the algorithm's execution.
//   • Tips: The O(N log N) approach uses a 'tails' array to store the smallest tail of all increasing subsequences of length 'i+1'.; Binary search is crucial for efficiently finding the correct position for the current element in the 'tails' array.
//   • Pitfalls: Confusing subsequence with contiguous subarray or substring.; Incorrectly updating or searching in the 'tails' array, leading to wrong lengths or values.
// - Calculating the determinant using Kraut method in O(N^3) (matrix, enumeration)
//   • When to use: Use this method to efficiently calculate the determinant of a square matrix, especially when an LU decomposition is also beneficial for other linear algebra tasks like solving systems of equations.
//   • Idea: The Kraut method, a specific form of LU decomposition, factorizes a square matrix A into a lower triangular matrix L (with ones on the diagonal) and an upper triangular matrix U. The determinant of A is then computed as the product of all diagonal elements of U, achieving an O(N^3) time complexity.
//   • Invariants: After processing column k-1, the k-1th column of L and k-1th row of U are correctly determined.; The submatrix A[0...k-1][0...k-1] is equivalent to L[0...k-1][0...k-1] * U[0...k-1][0...k-1].
//   • Tips: Ensure the matrix is invertible for a unique LU decomposition without pivoting.; The diagonal elements of the L matrix are typically set to 1 for uniqueness in Kraut's method.
//   • Pitfalls: Division by zero can occur if a pivot element is zero, indicating a singular matrix or requiring pivoting strategies.; Numerical instability may arise with ill-conditioned matrices when using floating-point arithmetic.
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int kIncreasing(vector<int>& arr, int k) {
        int n = arr.size();
        int operations = 0;

        for (int start = 0; start < k; ++start) {
            vector<int> subseq;
            for (int i = start; i < n; i += k) {
                subseq.push_back(arr[i]);
            }

            // Find length of LIS in subseq
            vector<int> lis;
            for (int num : subseq) {
                auto it = lower_bound(lis.begin(), lis.end(), num);
                if (it == lis.end()) {
                    lis.push_back(num);
                } else {
                    *it = num;
                }
            }

            operations += (subseq.size() - lis.size());
        }

        return operations;          
    }
};
