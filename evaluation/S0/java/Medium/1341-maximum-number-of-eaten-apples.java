// Source: https://leetcode.com/problems/maximum-number-of-eaten-apples/   |   Difficulty: Medium
//
// Problem Description:
// There is a special kind of apple tree that grows apples every day for n days. On the ith day, the tree grows apples[i] apples that will rot after days[i] days, that is on day i + days[i] the apples will be rotten and cannot be eaten. On some days, the apple tree does not grow any apples, which are denoted by apples[i] == 0 and days[i] == 0.
//
// You decided to eat at most one apple a day (to keep the doctors away). Note that you can keep eating after the first n days.
//
// Given two integer arrays days and apples of length n, return the maximum number of apples you can eat.
//
// Example:
// Input: apples = [1,2,3,5,2], days = [3,2,1,4,2]
// Output: 7
// Explanation: You can eat 7 apples:
// - On the first day, you eat an apple that grew on the first day.
// - On the second day, you eat an apple that grew on the second day.
// - On the third day, you eat an apple that grew on the second day. After this day, the apples that grew on the third day rot.
// - On the fourth to the seventh days, you eat apples that grew on the fourth day.
//
// Constraints:
// n == apples.length == days.length
// 	1 <= n <= 2 * 104
// 	0 <= apples[i], days[i] <= 2 * 104
// 	days[i] = 0 if and only if apples[i] = 0.
//

class Solution {
    public int eatenApples(int[] apples, int[] days) {
        PriorityQueue<int[]> pq = new PriorityQueue<>((a, b) -> a[0] - b[0]);
        int n = apples.length;
        int day = 0;
        int eaten = 0;

        while (day < n || !pq.isEmpty()) {
            // Add new apples grown on the current day
            if (day < n && apples[day] > 0) {
                pq.offer(new int[]{day + days[day], apples[day]});
            }

            // Remove rotten apples
            while (!pq.isEmpty() && pq.peek()[0] <= day) {
                pq.poll();
            }

            // Eat an apple if available
            if (!pq.isEmpty()) {
                int[] current = pq.poll();
                current[1]--; // Eat one apple
                eaten++;
                if (current[1] > 0) {
                    pq.offer(current); // Put back if there are apples left
                }
            }

            day++;
        }

        return eaten;           
    }
}
