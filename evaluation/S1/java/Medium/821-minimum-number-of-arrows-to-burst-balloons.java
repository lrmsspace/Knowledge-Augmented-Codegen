// Source: https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/   |   Difficulty: Medium
//
// Problem Description:
// There are some spherical balloons taped onto a flat wall that represents the XY-plane. The balloons are represented as a 2D integer array points where points[i] = [xstart, xend] denotes a balloon whose horizontal diameter stretches between xstart and xend. You do not know the exact y-coordinates of the balloons.
//
// Arrows can be shot up directly vertically (in the positive y-direction) from different points along the x-axis. A balloon with xstart and xend is burst by an arrow shot at x if xstart <= x <= xend. There is no limit to the number of arrows that can be shot. A shot arrow keeps traveling up infinitely, bursting any balloons in its path.
//
// Given the array points, return the minimum number of arrows that must be shot to burst all balloons.
//
// Example:
// Input: points = [[10,16],[2,8],[1,6],[7,12]]
// Output: 2
// Explanation: The balloons can be burst by 2 arrows:
// - Shoot an arrow at x = 6, bursting the balloons [2,8] and [1,6].
// - Shoot an arrow at x = 11, bursting the balloons [10,16] and [7,12].
//
// Constraints:
// 1 <= points.length <= 105
// 	points[i].length == 2
// 	-231 <= xstart < xend <= 231 - 1
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, especially for large datasets or external sorting where data might not fit in memory.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and requires O(N) auxiliary space.
//   • Invariants: The elements `index[lo...k-1]` are sorted and contain the smallest `k-lo` elements from the original `aux[lo...mid]` and `aux[mid+1...hi]` segments.; Pointer `i` always indicates the next element to consider from the left sorted sub-array (`aux[lo...mid]`).
//   • Tips: Implement the merge step carefully to ensure stability.; Consider an iterative bottom-up approach to avoid recursion overhead.
//   • Pitfalls: High auxiliary space complexity (O(N)) can be a concern for memory-constrained systems.; Recursive calls can lead to stack overflow for very large inputs without tail call optimization.
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
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
    private void mergeSort(int[][] points, int left, int right) {
        if (left >= right) {
            return;
        }
        int mid = left + (right - left) / 2;
        mergeSort(points, left, mid);
        mergeSort(points, mid + 1, right);
        
        // Merge step
        int[][] temp = new int[right - left + 1][2];
        int i = left, j = mid + 1, k = 0;
        
        while (i <= mid && j <= right) {
            if (points[i][1] <= points[j][1]) {
                temp[k++] = points[i++];
            } else {
                temp[k++] = points[j++];
            }
        }
        
        while (i <= mid) {
            temp[k++] = points[i++];
        }
        
        while (j <= right) {
            temp[k++] = points[j++];
        }
        
        // Copy back to original array
        for (int p = 0; p < temp.length; p++) {
            points[left + p] = temp[p];
        }
    }
    public int findMinArrowShots(int[][] points) {
        if (points.length == 0) {
            return 0;
        }

        // Sort the balloons by their ending x-coordinate
        mergeSort(points, 0, points.length - 1);

        int arrows = 1; // At least one arrow is needed
        int currentEnd = points[0][1]; // End of the first balloon

        for (int i = 1; i < points.length; i++) {
            // If the current balloon starts after the end of the last burst balloon
            if (points[i][0] > currentEnd) {
                arrows++; // Need a new arrow
                currentEnd = points[i][1]; // Update the end to the current balloon's end
            }
        }

        return arrows;          
    }
}
