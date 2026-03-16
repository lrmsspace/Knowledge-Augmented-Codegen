// Source: https://leetcode.com/problems/two-best-non-overlapping-events/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed 2D integer array of events where events[i] = [startTimei, endTimei, valuei]. The ith event starts at startTimei and ends at endTimei, and if you attend this event, you will receive a value of valuei. You can choose at most two non-overlapping events to attend such that the sum of their values is maximized.
//
// Return this maximum sum.
//
// Note that the start time and end time is inclusive: that is, you cannot attend two events where one of them starts and the other ends at the same time. More specifically, if you attend an event with end time t, the next event must start at or after t + 1.
//
// Example:
// Input: events = [[1,3,2],[4,5,2],[2,4,3]]
// Output: 4
// Explanation: Choose the green events, 0 and 1 for a sum of 2 + 2 = 4.
//
// Constraints:
// 2 <= events.length <= 105
// 	events[i].length == 3
// 	1 <= startTimei <= endTimei <= 109
// 	1 <= valuei <= 106
//

class Solution {
    public int maxTwoEvents(int[][] events) {
        Arrays.sort(events, (a, b) -> Integer.compare(a[0], b[0]));
        int n = events.length;
        int[] maxFromRight = new int[n];
        maxFromRight[n - 1] = events[n - 1][2];

        for (int i = n - 2; i >= 0; i--) {
            maxFromRight[i] = Math.max(maxFromRight[i + 1], events[i][2]);
        }

        int maxSum = 0;

        for (int i = 0; i < n; i++) {
            int currentValue = events[i][2];
            int nextIndex = binarySearchNextEvent(events, events[i][1] + 1);
            if (nextIndex != -1) {
                currentValue += maxFromRight[nextIndex];
            }
            maxSum = Math.max(maxSum, currentValue);
        }

        return maxSum;          
    }
}
