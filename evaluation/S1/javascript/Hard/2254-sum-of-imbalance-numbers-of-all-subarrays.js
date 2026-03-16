// Source: https://leetcode.com/problems/sum-of-imbalance-numbers-of-all-subarrays/   |   Difficulty: Hard
//
// Problem Description:
// The imbalance number of a 0-indexed integer array arr of length n is defined as the number of indices in sarr = sorted(arr) such that:
//
//
// 	0 <= i < n - 1, and
// 	sarr[i+1] - sarr[i] > 1
//
//
// Here, sorted(arr) is the function that returns the sorted version of arr.
//
// Given a 0-indexed integer array nums, return the sum of imbalance numbers of all its subarrays.
//
// A subarray is a contiguous non-empty sequence of elements within an array.
//
// Example:
// Input: nums = [2,3,1,4]
// Output: 3
// Explanation: There are 3 subarrays with non-zero imbalance numbers:
// - Subarray [3, 1] with an imbalance number of 1.
// - Subarray [3, 1, 4] with an imbalance number of 1.
// - Subarray [1, 4] with an imbalance number of 1.
// The imbalance number of all other subarrays is 0. Hence, the sum of imbalance numbers of all the subarrays of nums is 3.
//
// Constraints:
// 1 <= nums.length <= 1000
// 	1 <= nums[i] <= nums.length
//
// Helpful references (internal KB):
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
//
// Notes:
// - Keep the given function signature unchanged.
// - Do not add custom input parsing or console I/O unless the template explicitly requires it; rely on parameters/return value only.
// - Use standard ECMAScript features supported by LeetCode (Node.js runtime); no external packages.
// - Be careful with number precision: JavaScript Number is double; use BigInt only when necessary and keep return type consistent with the problem requirements.
// - If you introduce helper functions, define them in the same file and avoid relying on global mutable state across test cases.

/**
 * @param {number[]} nums
 * @return {number}
 */
var sumImbalanceNumbers = function(nums) {
    let imbalanceSum = 0;
    const n = nums.length;

    for (let i = 0; i < n; i++) {
        const sortedSubarray = [];
        let imbalanceCount = 0;

        for (let j = i; j < n; j++) {
            const num = nums[j];
            const insertPos = findInsertPosition(sortedSubarray, num);
            sortedSubarray.splice(insertPos, 0, num);

            if (insertPos > 0 && sortedSubarray[insertPos - 1] === num - 1) {
                imbalanceCount--;
            }
            if (insertPos < sortedSubarray.length - 1 && sortedSubarray[insertPos + 1] === num + 1) {
                imbalanceCount--;
            }
            if ((insertPos === 0 || sortedSubarray[insertPos - 1] !== num - 1) &&
                (insertPos === sortedSubarray.length - 1 || sortedSubarray[insertPos + 1] !== num + 1)) {
                imbalanceCount++;
            }

            imbalanceSum += imbalanceCount;
        }
    }

    return imbalanceSum;

    function findInsertPosition(arr, target) {
        let left = 0, right = arr.length;
        while (left < right) {
            const mid = Math.floor((left + right) / 2);
            if (arr[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
};
