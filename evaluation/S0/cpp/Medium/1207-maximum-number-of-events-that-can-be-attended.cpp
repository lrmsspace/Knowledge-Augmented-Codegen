// Source: https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of events where events[i] = [startDayi, endDayi]. Every event i starts at startDayi and ends at endDayi.
//
// You can attend an event i at any day d where startDayi <= d <= endDayi. You can only attend one event at any time d.
//
// Return the maximum number of events you can attend.
//
// Example:
// Input: events = [[1,2],[2,3],[3,4]]
// Output: 3
// Explanation: You can attend all the three events.
// One way to attend them all is as shown.
// Attend the first event on day 1.
// Attend the second event on day 2.
// Attend the third event on day 3.
//
// Constraints:
// 1 <= events.length <= 105
// 	events[i].length == 2
// 	1 <= startDayi <= endDayi <= 105
//

class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        sort(events.begin(), events.end());

        priority_queue<int, vector<int>, greater<int>> minHeap;
        int eventIndex = 0;
        int attendedEvents = 0;
        int currentDay = 1;
        const int totalEvents = events.size();

        while (eventIndex < totalEvents || !minHeap.empty()) {
            if (minHeap.empty()) {
                currentDay = events[eventIndex][0];
            }

            while (eventIndex < totalEvents && events[eventIndex][0] <= currentDay) {
                minHeap.push(events[eventIndex][1]);
                eventIndex++;
            }

            minHeap.pop();
            attendedEvents++;
            currentDay++;

            while (!minHeap.empty() && minHeap.top() < currentDay) {
                minHeap.pop();
            }
        }

        return attendedEvents;          
    }
};
