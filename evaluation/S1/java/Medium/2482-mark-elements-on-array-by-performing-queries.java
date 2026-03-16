// Source: https://leetcode.com/problems/mark-elements-on-array-by-performing-queries/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array nums of size n consisting of positive integers.
//
// You are also given a 2D array queries of size m where queries[i] = [indexi, ki].
//
// Initially all elements of the array are unmarked.
//
// You need to apply m queries on the array in order, where on the ith query you do the following:
//
//
// 	Mark the element at index indexi if it is not already marked.
// 	Then mark ki unmarked elements in the array with the smallest values. If multiple such elements exist, mark the ones with the smallest indices. And if less than ki unmarked elements exist, then mark all of them.
//
//
// Return an array answer of size m where answer[i] is the sum of unmarked elements in the array after the ith query.
//
// Example:
// Input: nums = [1,2,2,1,2,3,1], queries = [[1,2],[3,3],[4,2]]
//
// Output: [8,3,0]
//
// Explanation:
//
// We do the following queries on the array:
//
//
// 	Mark the element at index 1, and 2 of the smallest unmarked elements with the smallest indices if they exist, the marked elements now are nums = [1,2,2,1,2,3,1]. The sum of unmarked elements is 2 + 2 + 3 + 1 = 8.
// 	Mark the element at index 3, since it is already marked we skip it. Then we mark 3 of the smallest unmarked elements with the smallest indices, the marked elements now are nums = [1,2,2,1,2,3,1]. The sum of unmarked elements is 3.
// 	Mark the element at index 4, since it is already marked we skip it. Then we mark 2 of the smallest unmarked elements with the smallest indices if they exist, the marked elements now are nums = [1,2,2,1,2,3,1]. The sum of unmarked elements is 0.
//
// Constraints:
// n == nums.length
// 	m == queries.length
// 	1 <= m <= n <= 105
// 	1 <= nums[i] <= 105
// 	queries[i].length == 2
// 	0 <= indexi, ki <= n - 1
//
// Helpful references (internal KB):
// - Priority Queues (heap, stack, heap-select)
//   • When to use: Use when you need to efficiently retrieve the element with the highest (or lowest) priority from a collection, especially when elements are added or removed frequently.
//   • Idea: A priority queue is a data structure that allows efficient retrieval of the element with the highest or lowest priority, and efficient insertion of new elements. Operations typically run in logarithmic time, O(log N).
//   • Invariants: The priority queue maintains the heap property: parent nodes are always greater than/equal to (or less than/equal to) their children.; For a K-selection problem, the priority queue contains at most K elements, representing the K largest/smallest seen so far.
//   • Tips: Use a min-priority queue to find the K largest elements by keeping at most K elements.; Use a max-priority queue to find the K smallest elements by keeping at most K elements.
//   • Pitfalls: Confusing min-priority queue with max-priority queue for the desired extremum.; Inefficient underlying implementation leading to O(N) operations instead of O(log N).
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
// - Non-negative Integers without Consecutive Ones (number, enumeration, simulation)
//   • When to use: Use when counting numbers up to a given limit that satisfy a specific bit pattern constraint, particularly when the limit is small enough for direct iteration and checking.
//   • Idea: This approach iterates through every non-negative integer from 0 up to the given limit num. For each integer, it simulates checking its binary representation to determine if it contains any two consecutive '1's.
//   • Invariants: count stores the number of integers k (where 0 <= k < i) that do not have consecutive ones.; All integers j such that 0 <= j < i have been processed.
//   • Tips: Use bitwise operations like (i & (i >> 1)) to efficiently detect consecutive ones.; Remember to include 0 in the count as it satisfies the condition (no consecutive ones).
//   • Pitfalls: Performance degradation for large num due to linear scan and per-number bit check.; Incorrectly handling the upper bound of the iteration (e.g., i < num instead of i <= num).
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long[] unmarkedSumArray(int[] nums, int[][] queries) {
        int n = nums.length;
        int m = queries.length;

        // Create an array of indices sorted by the values in nums
        Integer[] indices = new Integer[n];
        for (int i = 0; i < n; i++) {
            indices[i] = i;
        }
        java.util.Arrays.sort(indices, (a, b) -> Integer.compare(nums[a], nums[b]));

        long totalSum = 0;
        for (int num : nums) {
            totalSum += num;
        }

        long[] result = new long[m];
        boolean[] marked = new boolean[n];
        int currentIndex = 0;

        for (int i = 0; i < m; i++) {
            int indexToMark = queries[i][0];
            int k = queries[i][1];

            // Mark the specified index if not already marked
            if (!marked[indexToMark]) {
                marked[indexToMark] = true;
                totalSum -= nums[indexToMark];
            }

            // Mark k smallest unmarked elements
            while (k > 0 && currentIndex < n) {
                int idx = indices[currentIndex];
                if (!marked[idx]) {
                    marked[idx] = true;
                    totalSum -= nums[idx];
                    k--;
                }
                currentIndex++;
            }

            result[i] = totalSum;
        }

        return result;          
    }
}
