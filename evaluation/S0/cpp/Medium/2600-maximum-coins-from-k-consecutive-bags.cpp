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
public:
    long long maximumCoins(vector<vector<int>>& coins, int k) {
        long long maxCoins = 0;
        long long currentCoins = 0;
        int left = 0;
        int n = coins.size();

        for (int right = 0; right < n; ++right) {
            int start = coins[right][0];
            int end = coins[right][1];
            int coinCount = coins[right][2];

            currentCoins += (long long)(end - start + 1) * coinCount;

            while (start - coins[left][1] >= k) {
                currentCoins -= (long long)(coins[left][1] - coins[left][0] + 1) * coins[left][2];
                left++;
            }

            long long totalBags = end - start + 1;
            if (left <= right) {
                totalBags += start - coins[left][1] - 1;
            }

            if (totalBags > k) {
                long long excessBags = totalBags - k;
                if (left <= right) {
                    long long leftSegmentBags = start - coins[left][1] - 1;
                    if (excessBags <= leftSegmentBags) {
                        currentCoins -= excessBags * coins[left][2];
                    } else {
                        currentCoins -= leftSegmentBags * coins[left][2];
                        excessBags -= leftSegmentBags;
                        currentCoins -= excessBags * coinCount;
                    }
                } else {
                    currentCoins -= excessBags * coinCount;
                }
            }

            maxCoins = max(maxCoins, currentCoins);
        }

        return maxCoins;            
    }
};
