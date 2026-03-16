// Source: https://leetcode.com/problems/find-k-closest-elements/   |   Difficulty: Medium
//
// Problem Description:
// Given a sorted integer array arr, two integers k and x, return the k closest integers to x in the array. The result should also be sorted in ascending order.
//
// An integer a is closer to x than an integer b if:
//
//
// 	|a - x| < |b - x|, or
// 	|a - x| == |b - x| and a < b
//
// Example:
// Input: arr = [1,2,3,4,5], k = 4, x = 3
//
// Output: [1,2,3,4]
//
// Constraints:
// 1 <= k <= arr.length
// 	1 <= arr.length <= 104
// 	arr is sorted in ascending order.
// 	-104 <= arr[i], x <= 104
//
// Helpful references (internal KB):
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
// -  
// Kth order statistic in O(N) (array, quickselect)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without fully sorting the entire data structure. It's particularly useful for large datasets where a full sort is too slow.
//   • Idea: Quickselect is a selection algorithm that finds the Kth smallest element in an unsorted list. It uses a divide-and-conquer approach similar to Quicksort, but only recurses on one side, achieving an average time complexity of O(N).
//   • Invariants: All elements to the left of the pivot are less than or equal to the pivot's value.; All elements to the right of the pivot are greater than or equal to the pivot's value.
//   • Tips: Choose a good pivot strategy, such as a random pivot, to minimize the chance of worst-case performance.; Handle duplicate elements carefully during the partitioning step to ensure correctness.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Deep recursion without tail call optimization can cause stack overflow errors.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public List<Integer> findClosestElements(int[] arr, int k, int x) {
        int low = 0;
        int high = arr.length - k;

        while (low < high) {
            int mid = low + (high - low) / 2;

            if (x - arr[mid] > arr[mid + k] - x) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        List<Integer> result = new ArrayList<>();
        for (int i = low; i < low + k; i++) {
            result.add(arr[i]);
        }

        return result;          
    }
}
