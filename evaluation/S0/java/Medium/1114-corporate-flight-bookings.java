// Source: https://leetcode.com/problems/corporate-flight-bookings/   |   Difficulty: Medium
//
// Problem Description:
// There are n flights that are labeled from 1 to n.
//
// You are given an array of flight bookings bookings, where bookings[i] = [firsti, lasti, seatsi] represents a booking for flights firsti through lasti (inclusive) with seatsi seats reserved for each flight in the range.
//
// Return an array answer of length n, where answer[i] is the total number of seats reserved for flight i.
//
// Example:
// Input: bookings = [[1,2,10],[2,3,20],[2,5,25]], n = 5
// Output: [10,55,45,25,25]
// Explanation:
// Flight labels:        1   2   3   4   5
// Booking 1 reserved:  10  10
// Booking 2 reserved:      20  20
// Booking 3 reserved:      25  25  25  25
// Total seats:         10  55  45  25  25
// Hence, answer = [10,55,45,25,25]
//
// Constraints:
// 1 <= n <= 2 * 104
// 	1 <= bookings.length <= 2 * 104
// 	bookings[i].length == 3
// 	1 <= firsti <= lasti <= n
// 	1 <= seatsi <= 104
//

class Solution {
    public int[] corpFlightBookings(int[][] bookings, int n) {
        int[] result = new int[n];
        int[] diff = new int[n + 1];

        for (int[] booking : bookings) {
            int first = booking[0] - 1; // Convert to 0-based index
            int last = booking[1] - 1;  // Convert to 0-based index
            int seats = booking[2];

            diff[first] += seats;
            if (last + 1 < n) {
                diff[last + 1] -= seats;
            }
        }

        result[0] = diff[0];
        for (int i = 1; i < n; i++) {
            result[i] = result[i - 1] + diff[i];
        }

        return result;          
    }
}
