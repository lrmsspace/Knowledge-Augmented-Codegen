// Source: https://leetcode.com/problems/determine-if-two-events-have-conflict/   |   Difficulty: Easy
//
// Problem Description:
// You are given two arrays of strings that represent two inclusive events that happened on the same day, event1 and event2, where:
//
//
// 	event1 = [startTime1, endTime1] and
// 	event2 = [startTime2, endTime2].
//
//
// Event times are valid 24 hours format in the form of HH:MM.
//
// A conflict happens when two events have some non-empty intersection (i.e., some moment is common to both events).
//
// Return true if there is a conflict between two events. Otherwise, return false.
//
// Example:
// Input: event1 = ["01:15","02:00"], event2 = ["02:00","03:00"]
// Output: true
// Explanation: The two events intersect at time 2:00.
//
// Constraints:
// event1.length == event2.length == 2
// 	event1[i].length == event2[i].length == 5
// 	startTime1 <= endTime1
// 	startTime2 <= endTime2
// 	All the event times follow the HH:MM format.
//

class Solution {
    public boolean haveConflict(String[] event1, String[] event2) {
        return !(event1[1].compareTo(event2[0]) < 0 || event2[1].compareTo(event1[0]) < 0);         
    }
}
