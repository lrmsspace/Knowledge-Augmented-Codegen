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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* corpFlightBookings(int** bookings, int bookingsSize, int* bookingsColSize, int n, int* returnSize) {
    int* result = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < bookingsSize; i++) {
        int first = bookings[i][0];
        int last = bookings[i][1];
        int seats = bookings[i][2];
        result[first - 1] += seats;
        if (last < n) {
            result[last] -= seats;
        }
    }
    for (int i = 1; i < n; i++) {
        result[i] += result[i - 1];
    }
    *returnSize = n;
    return result;      
}
