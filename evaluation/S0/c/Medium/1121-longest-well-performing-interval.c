// Source: https://leetcode.com/problems/longest-well-performing-interval/   |   Difficulty: Medium
//
// Problem Description:
// We are given hours, a list of the number of hours worked per day for a given employee.
//
// A day is considered to be a tiring day if and only if the number of hours worked is (strictly) greater than 8.
//
// A well-performing interval is an interval of days for which the number of tiring days is strictly larger than the number of non-tiring days.
//
// Return the length of the longest well-performing interval.
//
// Example:
// Input: hours = [9,9,6,0,6,6,9]
// Output: 3
// Explanation: The longest well-performing interval is [9,9,6].
//
// Constraints:
// 1 <= hours.length <= 104
// 	0 <= hours[i] <= 16
//

int longestWPI(int* hours, int hoursSize) {
    int prefixSum[hoursSize + 1];
    prefixSum[0] = 0;
    for (int i = 0; i < hoursSize; i++) {
        prefixSum[i + 1] = prefixSum[i] + (hours[i] > 8 ? 1 : -1);
    }

    int maxLength = 0;
    int stack[hoursSize + 1];
    int stackSize = 0;

    for (int i = 0; i <= hoursSize; i++) {
        if (stackSize == 0 || prefixSum[i] < prefixSum[stack[stackSize - 1]]) {
            stack[stackSize++] = i;
        }
    }

    for (int i = hoursSize; i >= 0; i--) {
        while (stackSize > 0 && prefixSum[i] > prefixSum[stack[stackSize - 1]]) {
            int j = stack[--stackSize];
            if (i - j > maxLength) {
                maxLength = i - j;
            }
        }
    }

    return maxLength;       
}
