// Source: https://leetcode.com/problems/sort-the-people/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of strings names, and an array heights that consists of distinct positive integers. Both arrays are of length n.
//
// For each index i, names[i] and heights[i] denote the name and height of the ith person.
//
// Return names sorted in descending order by the people's heights.
//
// Example:
// Input: names = ["Mary","John","Emma"], heights = [180,165,170]
// Output: ["Mary","Emma","John"]
// Explanation: Mary is the tallest, followed by Emma and John.
//
// Constraints:
// n == names.length == heights.length
// 	1 <= n <= 103
// 	1 <= names[i].length <= 20
// 	1 <= heights[i] <= 105
// 	names[i] consists of lower and upper case English letters.
// 	All the values of heights are distinct.
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - Priority Queues (array, heap, heap-select)
//   • When to use: Use when an in-place sorting algorithm with O(N log N) worst-case time complexity is required, especially when memory constraints are a concern. It's also applicable for efficiently finding the K largest/smallest elements.
//   • Idea: Heapsort is an in-place comparison-based sorting algorithm that uses a binary heap data structure. It first builds a max-heap from the input array, then repeatedly extracts the maximum element and places it at the end of the array, achieving O(N log N) time complexity.
//   • Invariants: During heap construction, the processed subarray forms a valid heap-ordered complete binary tree.; During sortdown, the elements in `arr[0...i]` form a valid heap, and `arr[i+1...N-1]` contains sorted elements.
//   • Tips: Heap construction can be done in linear time using a bottom-up sink-based approach.; Heapsort is an in-place sorting algorithm, requiring O(1) auxiliary space.
//   • Pitfalls: Heapsort is not a stable sorting algorithm; the relative order of equal elements is not preserved.; Cache performance can be poor due to non-sequential memory access patterns during heap operations.
// - Suffix array (array, tree, string, suffix-array, tree-dp, lca)
//   • When to use: Use when needing to perform fast substring searches, pattern matching, or other string operations on a fixed text, especially when space efficiency is critical compared to suffix trees.
//   • Idea: A suffix array is a sorted array of all suffixes of a given string, storing only their starting indices. It is often paired with an LCP (Longest Common Prefix) array to enable efficient string algorithms, typically achieving O(N log N) or O(N) construction and O(M + log N) or O(M) search complexity.
//   • Invariants: The suffix array `A` stores indices such that `S[A[i]:]` is lexicographically smaller than `S[A[i+1]:]` for all valid `i`.; The `lcp[i]` value represents the length of the longest common prefix between `S[A[i-1]:]` and `S[A[i]:]`.
//   • Tips: Pair with an LCP array to significantly speed up pattern searching and other string queries.; Consider Enhanced Suffix Arrays (ESA) for improved space and time efficiency over suffix trees, especially for large datasets.
//   • Pitfalls: Naive pattern searching without LCP information can be O(M log N), which might be too slow for long patterns.; Construction can be complex to implement efficiently in linear time.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {string[]} names
 * @param {number[]} heights
 * @return {string[]}
 */
var sortPeople = function(names, heights) {
    // Create an array of objects to pair names with heights
    const people = names.map((name, index) => ({ name, height: heights[index] }));
    
    // Sort people by height in descending order
    people.sort((a, b) => b.height - a.height);
    
    // Return the names in sorted order
    return people.map(person => person.name);   
};
