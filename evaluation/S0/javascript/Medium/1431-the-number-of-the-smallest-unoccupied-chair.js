// Source: https://leetcode.com/problems/the-number-of-the-smallest-unoccupied-chair/   |   Difficulty: Medium
//
// Problem Description:
// There is a party where n friends numbered from 0 to n - 1 are attending. There is an infinite number of chairs in this party that are numbered from 0 to infinity. When a friend arrives at the party, they sit on the unoccupied chair with the smallest number.
//
//
// 	For example, if chairs 0, 1, and 5 are occupied when a friend comes, they will sit on chair number 2.
//
//
// When a friend leaves the party, their chair becomes unoccupied at the moment they leave. If another friend arrives at that same moment, they can sit in that chair.
//
// You are given a 0-indexed 2D integer array times where times[i] = [arrivali, leavingi], indicating the arrival and leaving times of the ith friend respectively, and an integer targetFriend. All arrival times are distinct.
//
// Return the chair number that the friend numbered targetFriend will sit on.
//
// Example:
// Input: times = [[1,4],[2,3],[4,6]], targetFriend = 1
// Output: 1
// Explanation: 
// - Friend 0 arrives at time 1 and sits on chair 0.
// - Friend 1 arrives at time 2 and sits on chair 1.
// - Friend 1 leaves at time 3 and chair 1 becomes empty.
// - Friend 0 leaves at time 4 and chair 0 becomes empty.
// - Friend 2 arrives at time 4 and sits on chair 0.
// Since friend 1 sat on chair 1, we return 1.
//
// Constraints:
// n == times.length
// 	2 <= n <= 104
// 	times[i].length == 2
// 	1 <= arrivali < leavingi <= 105
// 	0 <= targetFriend <= n - 1
// 	Each arrivali time is distinct.
//

/**
 * @param {number[][]} times
 * @param {number} targetFriend
 * @return {number}
 */
var smallestChair = function(times, targetFriend) {
    const n = times.length;
    const events = [];
    for (let i = 0; i < n; i++) {
        events.push([times[i][0], 'arrive', i]);
        events.push([times[i][1], 'leave', i]);
    }
    events.sort((a, b) => {
        if (a[0] !== b[0]) {
            return a[0] - b[0];
        }
        if (a[1] === 'leave' && b[1] === 'arrive') {
            return -1;
        }
        if (a[1] === 'arrive' && b[1] === 'leave') {
            return 1;
        }
        return 0;
    });

    const availableChairs = [];
    const friendToChair = new Array(n);
    let nextChair = 0;

    for (const [time, eventType, friend] of events) {
        if (eventType === 'arrive') {
            let chair;
            if (availableChairs.length > 0) {
                chair = availableChairs.pop();
            } else {
                chair = nextChair++;
            }
            friendToChair[friend] = chair;
            if (friend === targetFriend) {
                return chair;
            }
        } else {
            availableChairs.push(friendToChair[friend]);
        }
    }
};