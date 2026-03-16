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
public:
    int eatenApples(vector<int>& apples, vector<int>& days) {
        using pii = pair<int, int>; // {rotDay, appleCount}
        priority_queue<pii, vector<pii>, greater<pii>> minHeap;
        int n = apples.size();
        int day = 0;
        int eatenCount = 0;

        while (day < n || !minHeap.empty()) {
            // Add new apples for the current day
            if (day < n && apples[day] > 0) {
                minHeap.push({day + days[day], apples[day]});
            }

            // Remove rotten apples
            while (!minHeap.empty() && minHeap.top().first <= day) {
                minHeap.pop();
            }

            // Eat an apple if available
            if (!minHeap.empty()) {
                pii top = minHeap.top();
                minHeap.pop();
                eatenCount++;
                if (top.second > 1) {
                    minHeap.push({top.first, top.second - 1});
                }
            }

            day++;
        }

        return eatenCount;          
    }
};
