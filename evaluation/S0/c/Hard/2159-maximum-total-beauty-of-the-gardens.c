// Source: https://leetcode.com/problems/maximum-total-beauty-of-the-gardens/   |   Difficulty: Hard
//
// Problem Description:
// Alice is a caretaker of n gardens and she wants to plant flowers to maximize the total beauty of all her gardens.
//
// You are given a 0-indexed integer array flowers of size n, where flowers[i] is the number of flowers already planted in the ith garden. Flowers that are already planted cannot be removed. You are then given another integer newFlowers, which is the maximum number of flowers that Alice can additionally plant. You are also given the integers target, full, and partial.
//
// A garden is considered complete if it has at least target flowers. The total beauty of the gardens is then determined as the sum of the following:
//
//
// 	The number of complete gardens multiplied by full.
// 	The minimum number of flowers in any of the incomplete gardens multiplied by partial. If there are no incomplete gardens, then this value will be 0.
//
//
// Return the maximum total beauty that Alice can obtain after planting at most newFlowers flowers.
//
// Example:
// Input: flowers = [1,3,1,1], newFlowers = 7, target = 6, full = 12, partial = 1
// Output: 14
// Explanation: Alice can plant
// - 2 flowers in the 0th garden
// - 3 flowers in the 1st garden
// - 1 flower in the 2nd garden
// - 1 flower in the 3rd garden
// The gardens will then be [3,6,2,2]. She planted a total of 2 + 3 + 1 + 1 = 7 flowers.
// There is 1 garden that is complete.
// The minimum number of flowers in the incomplete gardens is 2.
// Thus, the total beauty is 1 * 12 + 2 * 1 = 12 + 2 = 14.
// No other way of planting flowers can obtain a total beauty higher than 14.
//
// Constraints:
// 1 <= flowers.length <= 105
// 	1 <= flowers[i], target <= 105
// 	1 <= newFlowers <= 1010
// 	1 <= full, partial <= 105
//

long long maximumBeauty(int* flowers, int flowersSize, long long newFlowers, int target, int full, int partial) {
    int i;
    long long res = 0;

    // Count full gardens and cap flowers at target
    int fullGardens = 0;
    for (i = 0; i < flowersSize; ++i) {
        if (flowers[i] >= target) {
            fullGardens++;
            flowers[i] = target;
        }
    }

    // Sort flowers
    qsort(flowers, flowersSize, sizeof(int), cmpInt);

    // Prefix sum of flowers
    long long *prefixSum = (long long*)malloc((flowersSize + 1) * sizeof(long long));
    prefixSum[0] = 0;
    for (i = 0; i < flowersSize; ++i) {
        prefixSum[i + 1] = prefixSum[i] + flowers[i];
    }

    // Try all possible numbers of full gardens from current to max possible
    for (int fullCount = fullGardens; fullCount <= flowersSize; ++fullCount) {
        long long remainingFlowers = newFlowers;

        // Calculate flowers needed to make last 'fullCount' gardens full
        for (i = flowersSize - fullCount; i < flowersSize; ++i) {
            remainingFlowers -= (target - flowers[i]);
            if (remainingFlowers < 0) break;
        }
        if (remainingFlowers < 0) break;

        // Binary search for max min in incomplete gardens
        int left = 0, right = target - 1, bestMin = 0;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            // Find how many gardens need to be raised to 'mid'
            int idx = 0;
            while (idx < flowersSize - fullCount && flowers[idx] < mid) {
                idx++;
            }
            long long needed = (long long)mid * idx - prefixSum[idx];
            if (needed <= remainingFlowers) {
                bestMin = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        // Calculate total beauty
        long long totalBeauty = (long long)fullCount * full + (long long)bestMin * partial;
        if (totalBeauty > res) {
            res = totalBeauty;
        }
    }

    free(prefixSum);
    return res;     
}
