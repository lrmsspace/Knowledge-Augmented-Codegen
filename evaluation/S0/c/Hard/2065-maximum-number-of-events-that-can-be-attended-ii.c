// Source: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array of events where events[i] = [startDayi, endDayi, valuei]. The ith event starts at startDayi and ends at endDayi, and if you attend this event, you will receive a value of valuei. You are also given an integer k which represents the maximum number of events you can attend.
//
// You can only attend one event at a time. If you choose to attend an event, you must attend the entire event. Note that the end day is inclusive: that is, you cannot attend two events where one of them starts and the other ends on the same day.
//
// Return the maximum sum of values that you can receive by attending events.
//
// Example:
// Input: events = [[1,2,4],[3,4,3],[2,3,1]], k = 2
// Output: 7
// Explanation: Choose the green events, 0 and 1 (0-indexed) for a total value of 4 + 3 = 7.
//
// Constraints:
// 1 <= k <= events.length
// 	1 <= k * events.length <= 106
// 	1 <= startDayi <= endDayi <= 109
// 	1 <= valuei <= 106
//

int maxValue(int** events, int eventsSize, int* eventsColSize, int k) {
    // Sort events by end day
    int cmp(const void *a, const void *b) {
        return ((int*)a)[1] - ((int*)b)[1];
    }
    qsort(events, eventsSize, sizeof(int*), cmp);

    // DP array: dp[i][j] = max value attending j events up to i-th event
    int m = eventsSize;
    int maxState = 1 << k;
    int dp[m + 1][maxState];
    memset(dp, 0, sizeof(dp));

    for (int i = 1; i <= m; ++i) {
        int start = events[i - 1][0];
        int end = events[i - 1][1];
        int value = events[i - 1][2];

        // Find the last event that ends before the start of the current event
        int l = 0, r = i - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            if (events[mid][1] < start) {
                l = mid + 1;
            } else {
                r = mid;
            }
        }
        int last = (events[l][1] < start) ? l + 1 : l;

        for (int state = 0; state < maxState; ++state) {
            dp[i][state] = dp[i - 1][state]; // Not attending current event

            for (int j = 0; j < k; ++j) {
                if ((state & (1 << j)) == 0) { // If j-th event slot is free
                    int newState = state | (1 << j);
                    dp[i][newState] = fmax(dp[i][newState], dp[last][state] + value);
                }
            }
        }

}
    // Find the maximum value attending up to k events
    int result = 0;
    for (int state = 0; state < maxState; ++state) {
        if (dp[m][state] > result) {
            result = dp[m][state];
        }
    }       

    return result;
}