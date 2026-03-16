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
// - Longest increasing subsequence (array, dp-1d, segment-tree, coordinate-compress)
//   • When to use: Use when you need to find the longest possible subsequence of a given sequence such that elements in the subsequence are in strictly increasing order, preserving their original relative order.
//   • Idea: This algorithm finds the longest subsequence where elements are in strictly increasing order. It can be solved with dynamic programming in O(N^2) time or optimized to O(N log N) using binary search or a segment tree.
//   • Invariants: The 'tails' array (or DP array) is always sorted in increasing order.; For any index 'i', 'tails[i]' stores the smallest possible ending element of an increasing subsequence of length 'i+1'.
//   • Tips: The O(N log N) approach maintains an array where dp[i] stores the smallest ending element of an increasing subsequence of length i+1.; Binary search is used to find the correct position for the current element in the dp array.
//   • Pitfalls: Confusing subsequence with subarray, which requires contiguous elements.; Incorrectly handling duplicates for strictly increasing versus non-decreasing requirements.
// - Solve RMQ (Range Minimum Query) by finding LCA (Lowest Common Ancestor) (array, tree, lca)
//   • When to use: Use this technique for efficiently answering multiple Range Minimum Queries on a static array, especially when an asymptotically optimal O(1) query time solution is required.
//   • Idea: This algorithm solves the static Range Minimum Query problem by first constructing a Cartesian tree from the input array, then reducing RMQ queries to Lowest Common Ancestor queries on this tree. It achieves an optimal O(N) preprocessing time and O(1) query time.
//   • Invariants: For any node `u` in the Cartesian tree, `value(u)` is the minimum among all values in the original array segment represented by `u`'s subtree.; The in-order traversal of the Cartesian tree nodes' original array indices yields the original array `A`'s indices in increasing order.
//   • Tips: Construct the Cartesian tree efficiently in O(N) time, typically using a stack-based approach.; The value of the LCA of two nodes in the Cartesian tree corresponds to the minimum in the original array range between their indices.
//   • Pitfalls: Incorrectly building the Cartesian tree, especially when handling duplicate values or edge cases like empty arrays.; The Farach-Colton and Bender LCA algorithm is complex to implement and often requires significant effort.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long numberOfSubarrays(int* nums, int numsSize) {
    long long count = 0;
    for (int i = 0; i < numsSize; i++) {
        int left = i, right = i;
        while (left >= 0 && nums[left] <= nums[i]) {
            left--;
        }
        while (right < numsSize && nums[right] <= nums[i]) {
            right++;
        }
        count += (long long)(i - left) * (right - i);
    }
    return count;       
}
