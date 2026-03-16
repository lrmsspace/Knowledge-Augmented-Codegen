// Source: https://leetcode.com/problems/partition-array-such-that-maximum-difference-is-k/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array nums and an integer k. You may partition nums into one or more subsequences such that each element in nums appears in exactly one of the subsequences.
//
// Return the minimum number of subsequences needed such that the difference between the maximum and minimum values in each subsequence is at most k.
//
// A subsequence is a sequence that can be derived from another sequence by deleting some or no elements without changing the order of the remaining elements.
//
// Example:
// Input: nums = [3,6,1,2,5], k = 2
// Output: 2
// Explanation:
// We can partition nums into the two subsequences [3,1,2] and [6,5].
// The difference between the maximum and minimum value in the first subsequence is 3 - 1 = 2.
// The difference between the maximum and minimum value in the second subsequence is 6 - 5 = 1.
// Since two subsequences were created, we return 2. It can be shown that 2 is the minimum number of subsequences needed.
//
// Constraints:
// 1 <= nums.length <= 105
// 	0 <= nums[i] <= 105
// 	0 <= k <= 105
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Manhattan Distance (array, number, enumeration, max-window)
//   • When to use: When calculating distances on a grid where movement is restricted to cardinal directions, or when optimizing expressions involving sums of absolute differences of coordinates.
//   • Idea: Manhattan distance, or L1 distance, measures the distance between two points as the sum of the absolute differences of their Cartesian coordinates. It is commonly used to find optimal paths on a grid or to transform coordinate systems for specific optimizations, often with O(N) or O(N log N) complexity for common problems like farthest pair.
//   • Invariants: For any two points P1(x1, y1) and P2(x2, y2), the Manhattan distance is |x1-x2| + |y1-y2|.; The maximum Manhattan distance between any two points is found by considering the maximum of (max(x+y) - min(x+y)) and (max(x-y) - min(x-y)) over all points.
//   • Tips: For 2D points (x, y), Manhattan distance can be transformed by rotating coordinates: (x', y') = (x+y, x-y).; After coordinate rotation, the Manhattan distance problem often simplifies to finding min/max values of the transformed coordinates.
//   • Pitfalls: Confusing Manhattan distance with Euclidean distance (L2 distance) or Chebyshev distance (L-infinity).; Incorrectly applying coordinate rotation for problems not involving sums of absolute differences.
// - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
//   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
//   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
//   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
//   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int partitionArray(vector<int>& nums, int k) {
        sort(nums.begin(), nums.end());
        int count = 1;
        int minVal = nums[0];

        for (int i = 1; i < nums.size(); ++i) {
            if (nums[i] - minVal > k) {
                ++count;
                minVal = nums[i];
            }
        }

        return count;           
    }
};
