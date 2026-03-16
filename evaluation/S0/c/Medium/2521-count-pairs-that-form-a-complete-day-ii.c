// Source: https://leetcode.com/problems/count-pairs-that-form-a-complete-day-ii/   |   Difficulty: Medium
//
// Problem Description:
// Given an integer array hours representing times in hours, return an integer denoting the number of pairs i, j where i < j and hours[i] + hours[j] forms a complete day.
//
// A complete day is defined as a time duration that is an exact multiple of 24 hours.
//
// For example, 1 day is 24 hours, 2 days is 48 hours, 3 days is 72 hours, and so on.
//
// Example:
// Input: hours = [12,12,30,24,24]
//
// Output: 2
//
// Explanation: The pairs of indices that form a complete day are (0, 1) and (3, 4).
//
// Constraints:
// 1 <= hours.length <= 5 * 105
// 	1 <= hours[i] <= 109
//

long long countCompleteDayPairs(int* hours, int hoursSize) {
    int modCount[24] = {0};
    long long pairCount = 0;

    for (int i = 0; i < hoursSize; i++) {
        int modValue = hours[i] % 24;
        int complement = (24 - modValue) % 24;

        pairCount += modCount[complement];
        modCount[modValue]++;
    }

    return pairCount;       
}
