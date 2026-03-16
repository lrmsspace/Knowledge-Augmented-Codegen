// Source: https://leetcode.com/problems/maximize-the-minimum-powered-city/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 0-indexed integer array stations of length n, where stations[i] represents the number of power stations in the ith city.
//
// Each power station can provide power to every city in a fixed range. In other words, if the range is denoted by r, then a power station at city i can provide power to all cities j such that |i - j| <= r and 0 <= i, j <= n - 1.
//
//
// 	Note that |x| denotes absolute value. For example, |7 - 5| = 2 and |3 - 10| = 7.
//
//
// The power of a city is the total number of power stations it is being provided power from.
//
// The government has sanctioned building k more power stations, each of which can be built in any city, and have the same range as the pre-existing ones.
//
// Given the two integers r and k, return the maximum possible minimum power of a city, if the additional power stations are built optimally.
//
// Note that you can build the k power stations in multiple cities.
//
// Example:
// Input: stations = [1,2,4,5,0], r = 1, k = 2
// Output: 5
// Explanation: 
// One of the optimal ways is to install both the power stations at city 1. 
// So stations will become [1,4,4,5,0].
// - City 0 is provided by 1 + 4 = 5 power stations.
// - City 1 is provided by 1 + 4 + 4 = 9 power stations.
// - City 2 is provided by 4 + 4 + 5 = 13 power stations.
// - City 3 is provided by 5 + 4 = 9 power stations.
// - City 4 is provided by 5 + 0 = 5 power stations.
// So the minimum power of a city is 5.
// Since it is not possible to obtain a larger power, we return 5.
//
// Constraints:
// n == stations.length
// 	1 <= n <= 105
// 	0 <= stations[i] <= 105
// 	0 <= r <= n - 1
// 	0 <= k <= 109
//

long long maxPower(int* stations, int stationsSize, int r, int k) {
    long long left = 0, right = 0;
    for (int i = 0; i < stationsSize; ++i) {
        right += stations[i];
    }
    right += k; /* maximum possible power */

    long long result = 0;
    while (left <= right) {
        long long mid = left + (right - left) / 2;

        /* check if we can achieve at least 'mid' power for all cities */
        long long needed = 0;
        long long addStations[stationsSize];
        memset(addStations, 0, sizeof(addStations));
        long long windowSum = 0;

        for (int i = 0; i < stationsSize; ++i) {
            if (i > r) {
                windowSum -= addStations[i - r - 1];
            }
            windowSum += stations[i];

            if (i + r + 1 < stationsSize) {
                /* future city, do nothing now */
            } else {
                /* current city needs to have at least 'mid' power */
                if (windowSum < mid) {
                    long long diff = mid - windowSum;
                    needed += diff;
                    if (needed > k) break; /* early exit if we exceed k */

                    addStations[i + r < stationsSize ? i + r : stationsSize - 1] += diff;
                    windowSum += diff;
                }
            }
        }

        if (needed <= k) {
            result = mid; /* mid is achievable */
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    return result;      
}
