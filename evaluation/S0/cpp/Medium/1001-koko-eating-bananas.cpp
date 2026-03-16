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

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        int left = 1, right = *max_element(piles.begin(), piles.end());
        int result = right;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            long long hoursNeeded = 0;

            for (int pile : piles) {
                hoursNeeded += (pile + mid - 1) / mid; // Equivalent to ceil(pile / mid)
            }

            if (hoursNeeded <= h) {
                result = mid; // Found a valid speed, try for a smaller one
                right = mid - 1;
            } else {
                left = mid + 1; // Need a larger speed
            }
        }

        return result;        
    }
};
