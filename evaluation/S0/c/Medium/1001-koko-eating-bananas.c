// Source: https://leetcode.com/problems/koko-eating-bananas/   |   Difficulty: Medium
//
// Problem Description:
// Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.
//
// Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.
//
// Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.
//
// Return the minimum integer k such that she can eat all the bananas within h hours.
//
// Example:
// Input: piles = [3,6,7,11], h = 8
// Output: 4
//
// Constraints:
// 1 <= piles.length <= 104
// 	piles.length <= h <= 109
// 	1 <= piles[i] <= 109
//

int minEatingSpeed(int* piles, int pilesSize, int h) {
    int left = 1, right = 0;
    for (int i = 0; i < pilesSize; i++) {
        if (piles[i] > right) {
            right = piles[i];
        }
    }

    while (left < right) {
        int mid = left + (right - left) / 2;
        long hours = 0;
        for (int i = 0; i < pilesSize; i++) {
            hours += (piles[i] + mid - 1) / mid; // Ceiling division
        }
        if (hours > h) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;        
}
