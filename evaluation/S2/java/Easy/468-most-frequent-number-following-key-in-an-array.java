// Source: https://leetcode.com/problems/most-frequent-number-following-key-in-an-array/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array nums. You are also given an integer key, which is present in nums.
//
// For every unique integer target in nums, count the number of times target immediately follows an occurrence of key in nums. In other words, count the number of indices i such that:
//
//
// 	0 <= i <= nums.length - 2,
// 	nums[i] == key and,
// 	nums[i + 1] == target.
//
//
// Return the target with the maximum count. The test cases will be generated such that the target with maximum count is unique.
//
// Example:
// Input: nums = [1,100,200,1,100], key = 1
// Output: 100
// Explanation: For target = 100, there are 2 occurrences at indices 1 and 4 which follow an occurrence of key.
// No other integers follow an occurrence of key, so we return 100.
//
// Constraints:
// 2 <= nums.length <= 1000
// 	1 <= nums[i] <= 1000
// 	The test cases will be generated such that the answer is unique.
//
// Helpful references (internal KB):
// - MEX (minimal excluded) of a sequence (array, enumeration)
//   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
//   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
//   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
//   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
//   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
// - Substring Search (string, array, two-pointers, simulation)
//   • When to use: Use KMP to efficiently find all occurrences of a pattern string within a larger text. It is particularly useful when the pattern might appear multiple times or when avoiding redundant text scans is crucial for performance.
//   • Idea: The Knuth-Morris-Pratt (KMP) algorithm efficiently finds all occurrences of a pattern string within a text string by pre-processing the pattern to avoid re-scanning characters in the text. It achieves a time complexity of O(N + M), where N is text length and M is pattern length.
//   • Invariants: The `next` array is correctly pre-computed such that `next[k]` indicates the longest proper prefix of `pattern[0...k-1]` that is also a suffix of `pattern[0...k-1]`.; During the search phase, `text[i-j ... i-1]` always matches `pattern[0 ... j-1]` if `j > 0`.
//   • Tips: Pre-compute the 'next' array (also known as LPS or failure array) for the pattern.; The 'next' array stores the length of the longest proper prefix of the pattern that is also a suffix of the pattern up to that index.
//   • Pitfalls: Incorrectly building the 'next' (LPS) array, especially handling the base cases or transitions.; Off-by-one errors in array indexing for either the text or pattern pointers.
// - kth-largest-element-in-an-array (array, quickselect, randomized)
//   • When to use: Use when you need to efficiently find the k-th smallest or largest element in an unsorted array without fully sorting it, especially when average-case linear time complexity is acceptable and in-place modification is desired.
//   • Idea: QuickSelect is a divide-and-conquer algorithm that partitions an array around a pivot and recursively searches for the k-th element in the relevant partition. It offers an average-case O(N) time complexity and O(1) space.
//   • Invariants: The pivot element is always placed at its correct sorted position within the current sub-array.; All elements to the left of the pivot are less than or equal to it, and all elements to its right are greater than or equal to it.
//   • Tips: Randomly select pivots to ensure average-case O(N) performance and avoid worst-case scenarios.; Adjust the target index k based on whether you're seeking the k-th smallest or k-th largest element.
//   • Pitfalls: Poor pivot selection can lead to a worst-case O(N^2) time complexity, though rare with randomization.; Off-by-one errors are common when mapping k-th largest/smallest to 0-indexed array positions.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int mostFrequent(int[] nums, int key) {
        Map<Integer, Integer> countMap = new HashMap<>();
        int maxCount = 0;
        int result = -1;

        for (int i = 0; i < nums.length - 1; i++) {
            if (nums[i] == key) {
                int target = nums[i + 1];
                int count = countMap.getOrDefault(target, 0) + 1;
                countMap.put(target, count);

                if (count > maxCount) {
                    maxCount = count;
                    result = target;
                }
            }
        }

        return result;          
    }
}
