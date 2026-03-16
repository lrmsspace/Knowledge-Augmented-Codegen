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

/**
 * @param {number[][]} events
 * @return {number}
 */
var maxEvents = function(events) {
    events.sort((a, b) => a[0] - b[0]);
    const minHeap = [];
    let eventIndex = 0;
    let attendedEvents = 0;
    const addEventToHeap = (event) => {
        minHeap.push(event);
        let currentIndex = minHeap.length - 1;
        while (currentIndex > 0) {
            const parentIndex = Math.floor((currentIndex - 1) / 2);
            if (minHeap[parentIndex][1] <= minHeap[currentIndex][1]) break;
            [minHeap[parentIndex], minHeap[currentIndex]] = [minHeap[currentIndex], minHeap[parentIndex]];
            currentIndex = parentIndex;
        }
    };
    const removeMinEventFromHeap = () => {
        if (minHeap.length === 0) return null;
        const minEvent = minHeap[0];
        const lastEvent = minHeap.pop();
        if (minHeap.length === 0) return minEvent;
        minHeap[0] = lastEvent;
        let currentIndex = 0;
        while (true) {
            const leftChildIndex = 2 * currentIndex + 1;
            const rightChildIndex = 2 * currentIndex + 2;
            let smallestIndex = currentIndex;
            if (leftChildIndex < minHeap.length && minHeap[leftChildIndex][1] < minHeap[smallestIndex][1]) {
                smallestIndex = leftChildIndex;
            }
            if (rightChildIndex < minHeap.length && minHeap[rightChildIndex][1] < minHeap[smallestIndex][1]) {
                smallestIndex = rightChildIndex;
            }
            if (smallestIndex === currentIndex) break;
            [minHeap[currentIndex], minHeap[smallestIndex]] = [minHeap[smallestIndex], minHeap[currentIndex]];
            currentIndex = smallestIndex;
        }
        return minEvent;
    }
    let currentDay = 0;
    while (eventIndex < events.length || minHeap.length > 0) {
        if (minHeap.length === 0) {
            currentDay = events[eventIndex][0];
        }
        while (eventIndex < events.length && events[eventIndex][0] <= currentDay) {
            addEventToHeap(events[eventIndex]);
            eventIndex++;
        }
        const earliestEndingEvent = removeMinEventFromHeap();
        attendedEvents++;
        currentDay++;
        while (minHeap.length > 0 && minHeap[0][1] < currentDay) {
            removeMinEventFromHeap();
        }
    }
    return attendedEvents;
                    
};
