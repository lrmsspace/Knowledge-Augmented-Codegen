// Source: https://leetcode.com/problems/sort-the-students-by-their-kth-score/   |   Difficulty: Medium
//
// Problem Description:
// There is a class with m students and n exams. You are given a 0-indexed m x n integer matrix score, where each row represents one student and score[i][j] denotes the score the ith student got in the jth exam. The matrix score contains distinct integers only.
//
// You are also given an integer k. Sort the students (i.e., the rows of the matrix) by their scores in the kth (0-indexed) exam from the highest to the lowest.
//
// Return the matrix after sorting it.
//
// Example:
// Input: score = [[10,6,9,1],[7,5,11,2],[4,8,3,15]], k = 2
// Output: [[7,5,11,2],[10,6,9,1],[4,8,3,15]]
// Explanation: In the above diagram, S denotes the student, while E denotes the exam.
// - The student with index 1 scored 11 in exam 2, which is the highest score, so they got first place.
// - The student with index 0 scored 9 in exam 2, which is the second highest score, so they got second place.
// - The student with index 2 scored 3 in exam 2, which is the lowest score, so they got third place.
//
// Constraints:
// m == score.length
// 	n == score[i].length
// 	1 <= m, n <= 250
// 	1 <= score[i][j] <= 105
// 	score consists of distinct integers.
// 	0 <= k < n
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - kth-largest-element-in-an-array (array, quickselect, randomized)
//   • When to use: Use when you need to efficiently find the k-th smallest or largest element in an unsorted array without fully sorting it, especially when average-case linear time complexity is acceptable and in-place modification is desired.
//   • Idea: QuickSelect is a divide-and-conquer algorithm that partitions an array around a pivot and recursively searches for the k-th element in the relevant partition. It offers an average-case O(N) time complexity and O(1) space.
//   • Invariants: The pivot element is always placed at its correct sorted position within the current sub-array.; All elements to the left of the pivot are less than or equal to it, and all elements to its right are greater than or equal to it.
//   • Tips: Randomly select pivots to ensure average-case O(N) performance and avoid worst-case scenarios.; Adjust the target index k based on whether you're seeking the k-th smallest or k-th largest element.
//   • Pitfalls: Poor pivot selection can lead to a worst-case O(N^2) time complexity, though rare with randomization.; Off-by-one errors are common when mapping k-th largest/smallest to 0-indexed array positions.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[][]} score
 * @param {number} k
 * @return {number[][]}
 */
var sortTheStudents = function(score, k) {
    score.sort((a, b) => b[k] - a[k]);
    return score;
};
