// Source: https://leetcode.com/problems/can-make-arithmetic-progression-from-sequence/   |   Difficulty: Easy
//
// Problem Description:
// A sequence of numbers is called an arithmetic progression if the difference between any two consecutive elements is the same.
//
// Given an array of numbers arr, return true if the array can be rearranged to form an arithmetic progression. Otherwise, return false.
//
// Example:
// Input: arr = [3,5,1]
// Output: true
// Explanation: We can reorder the elements as [1,3,5] or [5,3,1] with differences 2 and -2 respectively, between each consecutive elements.
//
// Constraints:
// 2 <= arr.length <= 1000
// 	-106 <= arr[i] <= 106
//
// Helpful references (internal KB):
// - Shell Sort (array, shell-sort)
//   • When to use: Use when an in-place comparison sort is needed for medium-sized arrays, offering better performance than simple quadratic sorts. It is particularly effective when the data is already partially sorted.
//   • Idea: Shell Sort is an in-place comparison sort that improves upon insertion sort by allowing the exchange of items that are far apart. It sorts elements at a certain 'gap' distance, then progressively reduces the gap, leading to an O(N log N) to O(N^2) time complexity depending on the gap sequence.
//   • Invariants: For any k in [0, gap-1], the subsequence arr[k], arr[k+gap], arr[k+2*gap], ... is sorted up to the current element being processed by the inner insertion sort.; The gap value is always a positive integer and strictly decreases in each outer loop iteration.
//   • Tips: Choose an effective gap sequence (e.g., Knuth's, Sedgewick's) for optimal performance.; It is an in-place sorting algorithm, requiring O(1) auxiliary space.
//   • Pitfalls: Performance heavily depends on the chosen gap sequence; a poor sequence can lead to O(N^2) complexity.; It is not a stable sort, meaning the relative order of equal elements is not preserved.
// - Search the subarray with the maximum/minimum sum (array, binary-search-answer)
//   • When to use: Use when the problem asks for the minimum or maximum value that satisfies a monotonic condition.
//   • Idea: This technique finds a target value within a range by repeatedly dividing the search interval in half, based on a monotonic condition. It typically achieves O(log N) time complexity for a search space of size N.
//   • Invariants: The optimal answer always lies within the current search range [low, high].; All values less than 'low' (for min search) or greater than 'high' (for max search) are known to be non-optimal.
//   • Tips: Clearly define the search space [low, high] for the answer.; Implement a `check` function that determines if a given `mid` value is a feasible solution.
//   • Pitfalls: Incorrectly defining the search range [low, high] for the answer.; Errors in the `check` function leading to incorrect monotonicity or logic.
// - Burnside's lemma / Pólya enumeration theorem (array, number, enumeration, simulation)
//   • When to use: Use when counting the number of distinct configurations or arrangements of objects under a set of symmetry operations, where configurations are considered identical if one can be transformed into another by a group action.
//   • Idea: Burnside's Lemma and Pólya Enumeration Theorem are combinatorial tools used to count the number of distinct objects under a group of symmetries. Both typically involve iterating through group elements and analyzing permutation cycle structures, often resulting in polynomial time complexity depending on group size and element analysis.
//   • Invariants: The set of group elements considered remains consistent throughout the summation.; Each group element's cycle decomposition is correctly identified.
//   • Tips: Identify the group of symmetry operations acting on the objects.; For each group element, determine its permutation cycle structure.
//   • Pitfalls: Incorrectly identifying the full set of distinct group operations.; Errors in determining the cycle structure of permutations.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public boolean canMakeArithmeticProgression(int[] arr) {
        Arrays.sort(arr);
        int diff = arr[1] - arr[0];
        for (int i = 2; i < arr.length; i++) {
            if (arr[i] - arr[i - 1] != diff) {
                return false;
            }
        }
        return true;            
    }
}
