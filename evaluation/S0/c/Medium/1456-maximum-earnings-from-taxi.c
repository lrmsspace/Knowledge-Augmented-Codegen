// Source: https://leetcode.com/problems/maximum-earnings-from-taxi/   |   Difficulty: Medium
//
// Problem Description:
// There are n points on a road you are driving your taxi on. The n points on the road are labeled from 1 to n in the direction you are going, and you want to drive from point 1 to point n to make money by picking up passengers. You cannot change the direction of the taxi.
//
// The passengers are represented by a 0-indexed 2D integer array rides, where rides[i] = [starti, endi, tipi] denotes the ith passenger requesting a ride from point starti to point endi who is willing to give a tipi dollar tip.
//
// For each passenger i you pick up, you earn endi - starti + tipi dollars. You may only drive at most one passenger at a time.
//
// Given n and rides, return the maximum number of dollars you can earn by picking up the passengers optimally.
//
// Note: You may drop off a passenger and pick up a different passenger at the same point.
//
// Example:
// Input: n = 5, rides = [[2,5,4],[1,5,1]]
// Output: 7
// Explanation: We can pick up passenger 0 to earn 5 - 2 + 4 = 7 dollars.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= rides.length <= 3 * 104
// 	rides[i].length == 3
// 	1 <= starti < endi <= n
// 	1 <= tipi <= 105
//

long long maxTaxiEarnings(int n, int** rides, int ridesSize, int* ridesColSize) {
    // Sort rides based on starting point
    qsort(rides, ridesSize, sizeof(int*), [](const void* a, const void* b) {
        return (*(int**)a)[0] - (*(int**)b)[0];
    });

    long long* dp = (long long*)calloc(n + 1, sizeof(long long));
    int rideIndex = 0;

    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1]; // Carry forward the previous maximum earnings

        // Process all rides that start at point i
        while (rideIndex < ridesSize && rides[rideIndex][0] == i) {
            int start = rides[rideIndex][0];
            int end = rides[rideIndex][1];
            int tip = rides[rideIndex][2];

            long long earnings = (long long)(end - start + tip);
            dp[end] = fmax(dp[end], dp[start] + earnings);

            rideIndex++;
        }
    }

    long long maxEarnings = 0;
    for (int i = 1; i <= n; i++) {
        maxEarnings = fmax(maxEarnings, dp[i]);
    }

    free(dp);
    return maxEarnings;     
}
