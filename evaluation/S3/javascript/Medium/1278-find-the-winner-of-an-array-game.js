// Source: https://leetcode.com/problems/find-the-winner-of-an-array-game/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array arr of distinct integers and an integer k.
//
// A game will be played between the first two elements of the array (i.e. arr[0] and arr[1]). In each round of the game, we compare arr[0] with arr[1], the larger integer wins and remains at position 0, and the smaller integer moves to the end of the array. The game ends when an integer wins k consecutive rounds.
//
// Return the integer which will win the game.
//
// It is guaranteed that there will be a winner of the game.
//
// Example:
// Input: arr = [2,1,3,5,4,6,7], k = 2
// Output: 5
// Explanation: Let's see the rounds of the game:
// Round |       arr       | winner | win_count
//   1   | [2,1,3,5,4,6,7] | 2      | 1
//   2   | [2,3,5,4,6,7,1] | 3      | 1
//   3   | [3,5,4,6,7,1,2] | 5      | 1
//   4   | [5,4,6,7,1,2,3] | 5      | 2
// So we can see that 4 rounds will be played and 5 is the winner because it wins 2 consecutive games.
//
// Constraints:
// 2 <= arr.length <= 105
// 	1 <= arr[i] <= 106
// 	arr contains distinct integers.
// 	1 <= k <= 109
//
// Helpful references (internal KB):
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
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
 * @param {number[]} arr
 * @param {number} k
 * @return {number}
 */
var getWinner = function(arr, k) {
    let winner = arr[0];
    let winCount = 0;
    
    for (let i = 1; i < arr.length; i++) {
        if (winner > arr[i]) {
            winCount++;
        } else {
            winner = arr[i];
            winCount = 1;
        }
        
        if (winCount === k) {
            return winner;
        }
    }
    
    return winner; // If no one wins k times, the largest number will be the winner
};
