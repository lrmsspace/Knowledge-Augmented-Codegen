// Source: https://leetcode.com/problems/minimum-number-game/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 0-indexed integer array nums of even length and there is also an empty array arr. Alice and Bob decided to play a game where in every round Alice and Bob will do one move. The rules of the game are as follows:
//
//
// 	Every round, first Alice will remove the minimum element from nums, and then Bob does the same.
// 	Now, first Bob will append the removed element in the array arr, and then Alice does the same.
// 	The game continues until nums becomes empty.
//
//
// Return the resulting array arr.
//
// Example:
// Input: nums = [5,4,2,3]
// Output: [3,2,5,4]
// Explanation: In round one, first Alice removes 2 and then Bob removes 3. Then in arr firstly Bob appends 3 and then Alice appends 2. So arr = [3,2].
// At the begining of round two, nums = [5,4]. Now, first Alice removes 4 and then Bob removes 5. Then both append in arr which becomes [3,2,5,4].
//
// Constraints:
// 2 <= nums.length <= 100
// 	1 <= nums[i] <= 100
// 	nums.length % 2 == 0
//
// Helpful references (internal KB):
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> numberGame(vector<int>& nums) {
        vector<int> arr;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++) {
            if (i % 2 == 0) {
                arr.push_back(nums[i + 1]);
            } else {
                arr.push_back(nums[i - 1]);
            }
        }
        return arr;         
    }
};
