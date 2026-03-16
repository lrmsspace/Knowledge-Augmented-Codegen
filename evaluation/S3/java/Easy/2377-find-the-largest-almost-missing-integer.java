// Source: https://leetcode.com/problems/find-the-largest-almost-missing-integer/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array nums and an integer k.
//
// An integer x is almost missing from nums if x appears in exactly one subarray of size k within nums.
//
// Return the largest almost missing integer from nums. If no such integer exists, return -1.
// A subarray is a contiguous sequence of elements within an array.
//
// Example:
// Input: nums = [3,9,2,1,7], k = 3
//
// Output: 7
//
// Explanation:
//
//
// 	1 appears in 2 subarrays of size 3: [9, 2, 1] and [2, 1, 7].
// 	2 appears in 3 subarrays of size 3: [3, 9, 2], [9, 2, 1], [2, 1, 7].
// 	3 appears in 1 subarray of size 3: [3, 9, 2].
// 	7 appears in 1 subarray of size 3: [2, 1, 7].
// 	9 appears in 2 subarrays of size 3: [3, 9, 2], and [9, 2, 1].
//
//
// We return 7 since it is the largest integer that appears in exactly one subarray of size k.
//
// Constraints:
// 1 <= nums.length <= 50
// 	0 <= nums[i] <= 50
// 	1 <= k <= nums.length
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
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
    public int largestInteger(int[] nums, int k) {
        int n = nums.length;
        Map<Integer, Integer> countMap = new HashMap<>();

        // Count occurrences of each integer in subarrays of size k
        for (int i = 0; i <= n - k; i++) {
            Set<Integer> uniqueElements = new HashSet<>();
            for (int j = i; j < i + k; j++) {
                uniqueElements.add(nums[j]);
            }
            for (int num : uniqueElements) {
                countMap.put(num, countMap.getOrDefault(num, 0) + 1);
            }
        }

        int largestAlmostMissing = -1;
        for (Map.Entry<Integer, Integer> entry : countMap.entrySet()) {
            if (entry.getValue() == 1) {
                largestAlmostMissing = Math.max(largestAlmostMissing, entry.getKey());
            }
        }

        return largestAlmostMissing;            
    }
}
