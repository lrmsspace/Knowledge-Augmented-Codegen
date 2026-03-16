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

long long maximumCoins(int** coins, int coinsSize, int* coinsColSize, int k) {
    long long maxCoins = 0;
    long long currentCoins = 0;
    int left = 0;
    int right = 0;
    int n = coinsSize;

    while (right < n) {
        int start = coins[right][0];
        int end = start + k - 1;

        while (left < n && coins[left][1] < start) {
            left++;
        }

        currentCoins = 0;
        for (int i = left; i <= right; i++) {
            int l = coins[i][0];
            int r = coins[i][1];
            int c = coins[i][2];

            if (r < start || l > end) {
                continue;
            }

            int overlapStart = l > start ? l : start;
            int overlapEnd = r < end ? r : end;
            currentCoins += (overlapEnd - overlapStart + 1) * c;
        }

        if (currentCoins > maxCoins) {
            maxCoins = currentCoins;
        }

        right++;
    }

    return maxCoins;        
}
