// Source: https://leetcode.com/problems/take-gifts-from-the-richest-pile/   |   Difficulty: Easy
//
// Problem Description:
// You are given an integer array gifts denoting the number of gifts in various piles. Every second, you do the following:
//
//
// 	Choose the pile with the maximum number of gifts.
// 	If there is more than one pile with the maximum number of gifts, choose any.
// 	Reduce the number of gifts in the pile to the floor of the square root of the original number of gifts in the pile.
//
//
// Return the number of gifts remaining after k seconds.
//
// Example:
// Input: gifts = [25,64,9,4,100], k = 4
// Output: 29
// Explanation: 
// The gifts are taken in the following way:
// - In the first second, the last pile is chosen and 10 gifts are left behind.
// - Then the second pile is chosen and 8 gifts are left behind.
// - After that the first pile is chosen and 5 gifts are left behind.
// - Finally, the last pile is chosen again and 3 gifts are left behind.
// The final remaining gifts are [5,8,9,4,3], so the total number of gifts remaining is 29.
//
// Constraints:
// 1 <= gifts.length <= 103
// 	1 <= gifts[i] <= 109
// 	1 <= k <= 103
//

/**
 * @param {number[]} gifts
 * @param {number} k
 * @return {number}
 */
var pickGifts = function(gifts, k) {
    const maxHeap = new MaxPriorityQueue();
    for (const gift of gifts) {
        maxHeap.enqueue(gift);
    }
    for (let i = 0; i < k; i++) {
        const maxGift = maxHeap.dequeue().element;
        maxHeap.enqueue(Math.floor(Math.sqrt(maxGift)));
    }
    let totalGifts = 0;
    while (!maxHeap.isEmpty()) {
        totalGifts += maxHeap.dequeue().element;
    }
    return totalGifts;
};