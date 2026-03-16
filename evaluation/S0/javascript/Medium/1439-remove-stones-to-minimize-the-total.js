// Source: https://leetcode.com/problems/remove-stones-to-minimize-the-total/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array piles, where piles[i] represents the number of stones in the ith pile, and an integer k. You should apply the following operation exactly k times:
//
//
// 	Choose any piles[i] and remove floor(piles[i] / 2) stones from it.
//
//
// Notice that you can apply the operation on the same pile more than once.
//
// Return the minimum possible total number of stones remaining after applying the k operations.
//
// floor(x) is the largest integer that is smaller than or equal to x (i.e., rounds x down).
//
// Example:
// Input: piles = [5,4,9], k = 2
// Output: 12
// Explanation: Steps of a possible scenario are:
// - Apply the operation on pile 2. The resulting piles are [5,4,5].
// - Apply the operation on pile 0. The resulting piles are [3,4,5].
// The total number of stones in [3,4,5] is 12.
//
// Constraints:
// 1 <= piles.length <= 105
// 	1 <= piles[i] <= 104
// 	1 <= k <= 105
//

/**
 * @param {number[]} piles
 * @param {number} k
 * @return {number}
 */
var minStoneSum = function(piles, k) {
    const maxHeap = [];
    for (const pile of piles) {
        maxHeap.push(-pile);
    }
    // Convert array into a heap
    for (let i = Math.floor(maxHeap.length / 2) - 1; i >= 0; i--) {
        heapify(maxHeap, i);
    }

    for (let i = 0; i < k; i++) {
        let largest = -maxHeap[0];
        let reduced = largest - Math.floor(largest / 2);
        maxHeap[0] = -reduced;
        heapify(maxHeap, 0);
    }

    let total = 0;
    for (const val of maxHeap) {
        total += -val;
    }
    return total;
};

function heapify(arr, i) {
    const n = arr.length;
    let largest = i;
    const left = 2 * i + 1;
    const right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    if (largest !== i) {
        [arr[i], arr[largest]] = [arr[largest], arr[i]];
        heapify(arr, largest);
    }
}