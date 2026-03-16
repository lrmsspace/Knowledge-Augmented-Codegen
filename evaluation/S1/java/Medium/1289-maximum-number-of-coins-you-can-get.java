// Source: https://leetcode.com/problems/maximum-number-of-coins-you-can-get/   |   Difficulty: Medium
//
// Problem Description:
// There are 3n piles of coins of varying size, you and your friends will take piles of coins as follows:
//
//
// 	In each step, you will choose any 3 piles of coins (not necessarily consecutive).
// 	Of your choice, Alice will pick the pile with the maximum number of coins.
// 	You will pick the next pile with the maximum number of coins.
// 	Your friend Bob will pick the last pile.
// 	Repeat until there are no more piles of coins.
//
//
// Given an array of integers piles where piles[i] is the number of coins in the ith pile.
//
// Return the maximum number of coins that you can have.
//
// Example:
// Input: piles = [2,4,1,2,7,8]
// Output: 9
// Explanation: Choose the triplet (2, 7, 8), Alice Pick the pile with 8 coins, you the pile with 7 coins and Bob the last one.
// Choose the triplet (1, 2, 4), Alice Pick the pile with 4 coins, you the pile with 2 coins and Bob the last one.
// The maximum number of coins which you can have are: 7 + 2 = 9.
// On the other hand if we choose this arrangement (1, 2, 8), (2, 4, 7) you only get 2 + 4 = 6 coins which is not optimal.
//
// Constraints:
// 3 <= piles.length <= 105
// 	piles.length % 3 == 0
// 	1 <= piles[i] <= 104
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort, divide-and-conquer, recursion)
//   • When to use: Use when a stable sort with guaranteed O(N log N) time complexity is required, even if O(N) auxiliary space is acceptable. It is suitable for sorting linked lists efficiently.
//   • Idea: Mergesort is a divide-and-conquer algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and uses O(N) auxiliary space.
//   • Invariants: Before merging, the left subarray `a[lo..mid]` and right subarray `a[mid+1..hi]` are individually sorted.; After each recursive call `sort(a, aux, sub_lo, sub_hi)`, the subarray `a[sub_lo..sub_hi]` is sorted.
//   • Tips: Utilize an auxiliary array for the merging step to simplify implementation and ensure stability.; Mergesort is a stable sorting algorithm, preserving the relative order of equal elements.
//   • Pitfalls: The primary disadvantage is the requirement for O(N) extra space for the auxiliary array.; Implementing an in-place merge without significant extra space is complex and often less efficient.
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    private void mergeSort(int[] piles, int left, int right) {
        if (left >= right) {
            return;
        }
        int mid = left + (right - left) / 2;
        mergeSort(piles, left, mid);
        mergeSort(piles, mid + 1, right);
        
        // Merge step
        int[] temp = new int[right - left + 1];
        int i = left, j = mid + 1, k = 0;
        
        while (i <= mid && j <= right) {
            if (piles[i] <= piles[j]) {
                temp[k++] = piles[i++];
            } else {
                temp[k++] = piles[j++];
            }
        }
        
        while (i <= mid) {
            temp[k++] = piles[i++];
        }
        
        while (j <= right) {
            temp[k++] = piles[j++];
        }
        
        // Copy back to original array
        System.arraycopy(temp, 0, piles, left, temp.length);
    }
    public int maxCoins(int[] piles) {
        // Sort the piles in ascending order
        mergeSort(piles, 0, piles.length - 1);

        int totalCoins = 0;
        int n = piles.length / 3;

        // Pick the second largest pile from each triplet
        for (int i = 0; i < n; i++) {
            totalCoins += piles[piles.length - 2 - (i * 2)];
        }

        return totalCoins;          
    }
}
