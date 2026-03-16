// Source: https://leetcode.com/problems/check-if-all-the-integers-in-a-range-are-covered/   |   Difficulty: Easy
//
// Problem Description:
// You are given a 2D integer array ranges and two integers left and right. Each ranges[i] = [starti, endi] represents an inclusive interval between starti and endi.
//
// Return true if each integer in the inclusive range [left, right] is covered by at least one interval in ranges. Return false otherwise.
//
// An integer x is covered by an interval ranges[i] = [starti, endi] if starti <= x <= endi.
//
// Example:
// Input: ranges = [[1,2],[3,4],[5,6]], left = 2, right = 5
// Output: true
// Explanation: Every integer between 2 and 5 is covered:
// - 2 is covered by the first range.
// - 3 and 4 are covered by the second range.
// - 5 is covered by the third range.
//
// Constraints:
// 1 <= ranges.length <= 50
// 	1 <= starti <= endi <= 50
// 	1 <= left <= right <= 50
//

bool isCovered(int** ranges, int rangesSize, int* rangesColSize, int left, int right) {
    int covered[51] = {0}; // Array to track coverage of integers from 1 to 50

    // Mark the covered integers based on the given ranges
    for (int i = 0; i < rangesSize; i++) {
        int start = ranges[i][0];
        int end = ranges[i][1];
        for (int j = start; j <= end; j++) {
            covered[j] = 1; // Mark integer j as covered
        }
    }

    // Check if all integers in the range [left, right] are covered
    for (int k = left; k <= right; k++) {
        if (covered[k] == 0) {
            return false; // Found an integer that is not covered
        }
    }

    return true; // All integers in the range are covered       
}
