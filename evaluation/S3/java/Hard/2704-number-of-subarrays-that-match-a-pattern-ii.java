// Source: https://leetcode.com/problems/number-of-subarrays-that-match-a-pattern-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array nums of size n, and a 0-indexed integer array pattern of size m consisting of integers -1, 0, and 1.
//
// A subarray nums[i..j] of size m + 1 is said to match the pattern if the following conditions hold for each element pattern[k]:
//
//
// 	nums[i + k + 1] > nums[i + k] if pattern[k] == 1.
// 	nums[i + k + 1] == nums[i + k] if pattern[k] == 0.
// 	nums[i + k + 1] < nums[i + k] if pattern[k] == -1.
//
//
// Return the count of subarrays in nums that match the pattern.
//
// Example:
// Input: nums = [1,2,3,4,5,6], pattern = [1,1]
// Output: 4
// Explanation: The pattern [1,1] indicates that we are looking for strictly increasing subarrays of size 3. In the array nums, the subarrays [1,2,3], [2,3,4], [3,4,5], and [4,5,6] match this pattern.
// Hence, there are 4 subarrays in nums that match the pattern.
//
// Constraints:
// 2 <= n == nums.length <= 106
// 	1 <= nums[i] <= 109
// 	1 <= m == pattern.length < n
// 	-1 <= pattern[i] <= 1
//
// Helpful references (internal KB):
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// - Generating all K-combinations (bitset, enumeration)
//   • When to use: When all subsets of a fixed size K need to be generated, either in lexicographical order or such that successive combinations differ by exactly one element.
//   • Idea: This algorithm enumerates all K-combinations from a set, either in lexicographical order or using a Gray code approach where adjacent combinations differ by a single element. It typically runs in O(N choose K) time, generating each combination in O(K) or O(1) amortized time.
//   • Invariants: Each generated combination contains exactly K distinct elements.; All elements within a combination are unique and from the original set.
//   • Tips: For lexicographical generation, find the rightmost element that can be incremented without exceeding its maximum possible value.; After incrementing an element, set all subsequent elements to their minimum valid values.
//   • Pitfalls: Incorrectly handling boundary conditions for the rightmost element or its maximum value.; Off-by-one errors when assigning subsequent elements after an increment.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int countMatchingSubarrays(int[] nums, int[] pattern) {
        int n = nums.length, m = pattern.length;
        int count = 0;

        for (int i = 0; i <= n - m - 1; i++) {
            boolean matches = true;
            for (int k = 0; k < m; k++) {
                if (pattern[k] == 1 && nums[i + k + 1] <= nums[i + k]) {
                    matches = false;
                    break;
                } else if (pattern[k] == 0 && nums[i + k + 1] != nums[i + k]) {
                    matches = false;
                    break;
                } else if (pattern[k] == -1 && nums[i + k + 1] >= nums[i + k]) {
                    matches = false;
                    break;
                }
            }
            if (matches) {
                count++;
            }
        }

        return count;           
    }
}
