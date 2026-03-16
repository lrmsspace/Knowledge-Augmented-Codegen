// Source: https://leetcode.com/problems/recover-the-original-array/   |   Difficulty: Hard
//
// Problem Description:
// Alice had a 0-indexed array arr consisting of n positive integers. She chose an arbitrary positive integer k and created two new 0-indexed integer arrays lower and higher in the following manner:
//
//
// 	lower[i] = arr[i] - k, for every index i where 0 <= i < n
// 	higher[i] = arr[i] + k, for every index i where 0 <= i < n
//
//
// Unfortunately, Alice lost all three arrays. However, she remembers the integers that were present in the arrays lower and higher, but not the array each integer belonged to. Help Alice and recover the original array.
//
// Given an array nums consisting of 2n integers, where exactly n of the integers were present in lower and the remaining in higher, return the original array arr. In case the answer is not unique, return any valid array.
//
// Note: The test cases are generated such that there exists at least one valid array arr.
//
// Example:
// Input: nums = [2,10,6,4,8,12]
// Output: [3,7,11]
// Explanation:
// If arr = [3,7,11] and k = 1, we get lower = [2,6,10] and higher = [4,8,12].
// Combining lower and higher gives us [2,6,10,4,8,12], which is a permutation of nums.
// Another valid possibility is that arr = [5,7,9] and k = 3. In that case, lower = [2,4,6] and higher = [8,10,12].
//
// Constraints:
// 2 * n == nums.length
// 	1 <= n <= 1000
// 	1 <= nums[i] <= 109
// 	The test cases are generated such that there exists at least one valid array arr.
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - Hash Tables (array, number, string, hashing)
//   • When to use: Use when you need to store and retrieve key-value pairs efficiently by transforming keys into array indices, managing potential collisions.
//   • Idea: Hash tables map keys to array indices using a hash function, enabling average O(1) time complexity for insertions, deletions, and lookups by efficiently managing potential collisions.
//   • Invariants: The hash function always produces an index within the valid array bounds [0, M-1].; For any two equal keys, their hash values remain identical.
//   • Tips: Design hash functions for uniform key distribution across the array.; Ensure hash functions are deterministic and efficient to compute.
//   • Pitfalls: Using a hash function that does not uniformly distribute keys, leading to many collisions.; Failing to implement a proper collision resolution strategy.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int[] recoverArray(int[] nums) {
        java.util.Arrays.sort(nums);
        int n = nums.length;
        for (int i = 1; i < n; i++) {
            int diff = nums[i] - nums[0];
            if (diff <= 0 || diff % 2 != 0) {
                continue;
            }
            int k = diff / 2;
            java.util.Map<Integer, Integer> countMap = new java.util.HashMap<>();
            for (int num : nums) {
                countMap.put(num, countMap.getOrDefault(num, 0) + 1);
            }
            int[] original = new int[n / 2];
            boolean valid = true;
            for (int j = 0, idx = 0; j < n; j++) {
                if (countMap.getOrDefault(nums[j], 0) == 0) {
                    continue;
                }
                countMap.put(nums[j], countMap.get(nums[j]) - 1);
                int higherNum = nums[j] + 2 * k;
                if (countMap.getOrDefault(higherNum, 0) == 0) {
                    valid = false;
                    break;
                }
                countMap.put(higherNum, countMap.get(higherNum) - 1);
                original[idx++] = nums[j] + k;
            }
            if (valid) {
                return original;
            }
        }
        return new int[0];          
    }
}
