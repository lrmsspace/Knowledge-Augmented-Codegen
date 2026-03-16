// Source: https://leetcode.com/problems/maximum-total-beauty-of-the-gardens/   |   Difficulty: Hard
//
// Problem Description:
// Alice is a caretaker of n gardens and she wants to plant flowers to maximize the total beauty of all her gardens.
//
// You are given a 0-indexed integer array flowers of size n, where flowers[i] is the number of flowers already planted in the ith garden. Flowers that are already planted cannot be removed. You are then given another integer newFlowers, which is the maximum number of flowers that Alice can additionally plant. You are also given the integers target, full, and partial.
//
// A garden is considered complete if it has at least target flowers. The total beauty of the gardens is then determined as the sum of the following:
//
//
// 	The number of complete gardens multiplied by full.
// 	The minimum number of flowers in any of the incomplete gardens multiplied by partial. If there are no incomplete gardens, then this value will be 0.
//
//
// Return the maximum total beauty that Alice can obtain after planting at most newFlowers flowers.
//
// Example:
// Input: flowers = [1,3,1,1], newFlowers = 7, target = 6, full = 12, partial = 1
// Output: 14
// Explanation: Alice can plant
// - 2 flowers in the 0th garden
// - 3 flowers in the 1st garden
// - 1 flower in the 2nd garden
// - 1 flower in the 3rd garden
// The gardens will then be [3,6,2,2]. She planted a total of 2 + 3 + 1 + 1 = 7 flowers.
// There is 1 garden that is complete.
// The minimum number of flowers in the incomplete gardens is 2.
// Thus, the total beauty is 1 * 12 + 2 * 1 = 12 + 2 = 14.
// No other way of planting flowers can obtain a total beauty higher than 14.
//
// Constraints:
// 1 <= flowers.length <= 105
// 	1 <= flowers[i], target <= 105
// 	1 <= newFlowers <= 1010
// 	1 <= full, partial <= 105
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long maximumBeauty(vector<int>& flowers, long long newFlowers, int target, int full, int partial) {
        int n = flowers.size();
        long long result = 0;
        sort(flowers.begin(), flowers.end());
        vector<long long> prefixSum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefixSum[i + 1] = prefixSum[i] + flowers[i];
        }
        for (int completeGardens = 0; completeGardens <= n; ++completeGardens) {
            if (completeGardens > 0) {
                newFlowers -= max(0, (long long)target * completeGardens - prefixSum[n] + prefixSum[n - completeGardens]);
            }
            if (newFlowers < 0) {
                break;
            }
            result = max(result, (long long)completeGardens * full);
            int left = 0, right = target - 1;
            while (left <= right) {
                int mid = left + (right - left) / 2;
                int idx = upper_bound(flowers.begin(), flowers.end() - completeGardens, mid) - flowers.begin();
                long long neededFlowers = (long long)mid * idx - prefixSum[idx];
                if (neededFlowers <= newFlowers) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
            result = max(result, (long long)completeGardens * full + right * partial);
        }
        return result;
    }
};
