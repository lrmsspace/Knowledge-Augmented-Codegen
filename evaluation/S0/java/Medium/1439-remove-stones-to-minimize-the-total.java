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

class Solution {
    public int minStoneSum(int[] piles, int k) {
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());
        int totalStones = 0;

        // Add all piles to the max-heap and calculate the total stones
        for (int pile : piles) {
            maxHeap.offer(pile);
            totalStones += pile;
        }

        // Perform k operations
        for (int i = 0; i < k; i++) {
            int largestPile = maxHeap.poll();
            int stonesToRemove = largestPile / 2;
            totalStones -= stonesToRemove;
            maxHeap.offer(largestPile - stonesToRemove);
        }

        return totalStones;         
    }
}
