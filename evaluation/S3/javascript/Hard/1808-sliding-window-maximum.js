// Source: https://leetcode.com/problems/sliding-window-maximum/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.
//
// Return the max sliding window.
//
// Example:
// Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
// Output: [3,3,5,5,6,7]
// Explanation: 
// Window position                Max
// ---------------               -----
// [1  3  -1] -3  5  3  6  7       3
//  1 [3  -1  -3] 5  3  6  7       3
//  1  3 [-1  -3  5] 3  6  7       5
//  1  3  -1 [-3  5  3] 6  7       5
//  1  3  -1  -3 [5  3  6] 7       6
//  1  3  -1  -3  5 [3  6  7]      7
//
// Constraints:
// 1 <= nums.length <= 105
// 	-104 <= nums[i] <= 104
// 	1 <= k <= nums.length
//
// Helpful references (internal KB):
// - Minimum stack / Minimum queue (queue, deque, monotonic-queue)
//   • When to use: Use this technique when you need to perform standard queue or stack operations while also querying the minimum (or maximum) element in O(1) time. It is ideal for problems involving sliding windows or dynamic collections where min/max queries are frequent.
//   • Idea: This technique augments a queue or stack with an auxiliary data structure, typically a deque, to maintain elements in monotonic order. This allows for O(1) retrieval of the minimum (or maximum) element, with standard operations achieving amortized O(1) time complexity.
//   • Invariants: The auxiliary deque stores elements in non-decreasing order from front to back.; The element at the front of the auxiliary deque is the minimum of all elements currently in the main queue/stack.
//   • Tips: Utilize a deque for the auxiliary structure to efficiently add and remove from both ends.; For a minimum queue, maintain the auxiliary deque in non-decreasing order from front to back.
//   • Pitfalls: Incorrectly handling removals when the element to be removed from the main structure is not the current minimum.; Forgetting to remove elements from the auxiliary deque when they are no longer relevant (e.g., out of window bounds).
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @param {number} k
 * @return {number[]}
 */
var maxSlidingWindow = function(nums, k) {
    const deque = []; // Will store indices of elements in the current window
    const result = [];
        
    for (let i = 0; i < nums.length; i++) {
        // Remove indices that are out of the current window
        while (deque.length > 0 && deque[0] <= i - k) {
            deque.shift();
        }
        
        // Remove indices whose corresponding values are less than the current value
        while (deque.length > 0 && nums[deque[deque.length - 1]] < nums[i]) {
            deque.pop();
        }
        
        // Add the current index to the deque
        deque.push(i);
        
        // If we have processed at least k elements, add the maximum to result
        if (i >= k - 1) {
            result.push(nums[deque[0]]);
        }
    }
    
    return result;
};
    
    