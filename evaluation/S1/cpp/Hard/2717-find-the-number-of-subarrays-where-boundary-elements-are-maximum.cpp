// Source: https://leetcode.com/problems/find-the-number-of-subarrays-where-boundary-elements-are-maximum/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of positive integers nums.
//
// Return the number of subarrays of nums, where the first and the last elements of the subarray are equal to the largest element in the subarray.
//
// Example:
// Input: nums = [1,4,3,3,2]
//
// Output: 6
//
// Explanation:
//
// There are 6 subarrays which have the first and the last elements equal to the largest element of the subarray:
//
//
// 	subarray [1,4,3,3,2], with its largest element 1. The first element is 1 and the last element is also 1.
// 	subarray [1,4,3,3,2], with its largest element 4. The first element is 4 and the last element is also 4.
// 	subarray [1,4,3,3,2], with its largest element 3. The first element is 3 and the last element is also 3.
// 	subarray [1,4,3,3,2], with its largest element 3. The first element is 3 and the last element is also 3.
// 	subarray [1,4,3,3,2], with its largest element 2. The first element is 2 and the last element is also 2.
// 	subarray [1,4,3,3,2], with its largest element 3. The first element is 3 and the last element is also 3.
//
//
// Hence, we return 6.
//
// Constraints:
// 1 <= nums.length <= 105
// 	1 <= nums[i] <= 109
//
// Helpful references (internal KB):
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, stack, simulation, monotonic-stack)
//   • When to use: This technique is used to answer Range Minimum Queries efficiently on a static array by transforming them into Lowest Common Ancestor queries on a Cartesian Tree.
//   • Idea: This approach solves Range Minimum Query problems by constructing a Cartesian Tree from the input array, where the root of any subtree is its minimum element. RMQ for a given range then reduces to finding the Lowest Common Ancestor of the range's endpoints in this tree, allowing O(N) construction and O(1) query time after O(N) preprocessing.
//   • Invariants: For any node `u` in the Cartesian Tree, `value(u)` is the minimum among all values in the subtree rooted at `u`.; For any node `u`, all nodes in its left subtree have indices smaller than `index(u)`, and all nodes in its right subtree have indices larger than `index(u)`.
//   • Tips: A Cartesian Tree is a binary tree where each node's value is less than its children's values, and an in-order traversal yields the original array.; Utilize a monotonic stack to construct the Cartesian Tree in linear O(N) time.
//   • Pitfalls: Correctly implementing the monotonic stack for Cartesian Tree construction can be challenging.; Edge cases, such as an empty stack or handling the last elements during tree building, must be managed carefully.
// - Segment Tree (tree, array, segment-tree, merge-sort, binary-search)
//   • When to use: Use when processing range queries or updates on an array, or when efficient searching and sorting of data are required. It's also applicable for problems that can be broken down into smaller, independent subproblems.
//   • Idea: This card describes techniques for efficiently handling range queries and updates on arrays, as well as searching and sorting elements. These methods typically achieve logarithmic time complexity for operations.
//   • Invariants: Each node in the segment tree represents a specific range of the original array.; The target element, if present, is always within the current binary search interval [low, high].
//   • Tips: Segment trees are powerful for static arrays with dynamic queries.; Merge sort's divide-and-conquer approach can be adapted for counting inversions.
//   • Pitfalls: Off-by-one errors in binary search bounds.; Incorrect segment tree node merging logic.
// - Range Minimum Query (array, ds, divide-and-conquer)
//   • When to use: Use when you need to find the minimum element within specified ranges of an array efficiently, especially for many queries after initial setup.
//   • Idea: A Range Minimum Query (RMQ) problem asks to find the minimum value in a specified range [L, R] of an array. It can be solved with various data structures, often achieving O(1) or O(log N) query time after O(N log N) or O(N) precomputation.
//   • Invariants: For any query range [L, R], the returned value is the minimum of elements A[i] where L <= i <= R.; The precomputed data structure correctly stores minimums for all relevant sub-intervals.
//   • Tips: For static arrays, Sparse Table offers O(1) query time after O(N log N) precomputation.; For dynamic arrays (with updates), Segment Tree provides O(log N) query and update times.
//   • Pitfalls: Incorrectly handling edge cases for range boundaries (L, R).; High memory usage for Sparse Table if N is very large (N log N space).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    long long numberOfSubarrays(vector<int>& nums) {
        const int n = nums.size();
        long long result = 0;
        vector<int> stack;
        vector<int> left(n), right(n);

        // Find the next greater element to the left
        for (int i = 0; i < n; ++i) {
            while (!stack.empty() && nums[stack.back()] < nums[i]) {
                stack.pop_back();
            }
            left[i] = stack.empty() ? -1 : stack.back();
            stack.push_back(i);
        }

        stack.clear();

        // Find the next greater element to the right
        for (int i = n - 1; i >= 0; --i) {
            while (!stack.empty() && nums[stack.back()] <= nums[i]) {
                stack.pop_back();
            }
            right[i] = stack.empty() ? n : stack.back();
            stack.push_back(i);
        }

        // Calculate the number of valid subarrays
        for (int i = 0; i < n; ++i) {
            long long leftCount = i - left[i];
            long long rightCount = right[i] - i;
            result += leftCount * rightCount;
        }

        return result;          
    }
};
