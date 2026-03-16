// Source: https://leetcode.com/problems/maximum-coins-from-k-consecutive-bags/   |   Difficulty: Medium
//
// Problem Description:
// There are an infinite amount of bags on a number line, one bag for each coordinate. Some of these bags contain coins.
//
// You are given a 2D array coins, where coins[i] = [li, ri, ci] denotes that every bag from li to ri contains ci coins.
//
// The segments that coins contain are non-overlapping.
//
// You are also given an integer k.
//
// Return the maximum amount of coins you can obtain by collecting k consecutive bags.
//
// Example:
// Input: coins = [[8,10,1],[1,3,2],[5,6,4]], k = 4
//
// Output: 10
//
// Explanation:
//
// Selecting bags at positions [3, 4, 5, 6] gives the maximum number of coins: 2 + 0 + 4 + 4 = 10.
//
// Constraints:
// 1 <= coins.length <= 105
// 	1 <= k <= 109
// 	coins[i] == [li, ri, ci]
// 	1 <= li <= ri <= 109
// 	1 <= ci <= 1000
// 	The given segments are non-overlapping.
//

class Solution {
    public long maximumCoins(int[][] coins, int k) {
        long maxCoins = 0;
        long currentCoins = 0;
        int left = 0;
        int n = coins.length;

        for (int right = 0; right < n; right++) {
            int l = coins[right][0];
            int r = coins[right][1];
            int c = coins[right][2];

            currentCoins += (long) (r - l + 1) * c;

            while (l - coins[left][1] > k - 1) {
                currentCoins -= (long) (coins[left][1] - coins[left][0] + 1) * coins[left][2];
                left++;
            }

            long totalBags = r - coins[left][0] + 1;
            if (totalBags > k) {
                long excessBags = totalBags - k;
                currentCoins -= excessBags * c;
            }

            maxCoins = Math.max(maxCoins, currentCoins);
        }

        return maxCoins;            
    }
}
