// Source: https://leetcode.com/problems/number-of-smooth-descent-periods-of-a-stock/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer array prices representing the daily price history of a stock, where prices[i] is the stock price on the ith day.
//
// A smooth descent period of a stock consists of one or more contiguous days such that the price on each day is lower than the price on the preceding day by exactly 1. The first day of the period is exempted from this rule.
//
// Return the number of smooth descent periods.
//
// Example:
// Input: prices = [3,2,1,4]
// Output: 7
// Explanation: There are 7 smooth descent periods:
// [3], [2], [1], [4], [3,2], [2,1], and [3,2,1]
// Note that a period with one day is a smooth descent period by the definition.
//
// Constraints:
// 1 <= prices.length <= 105
// 	1 <= prices[i] <= 105
//

long long getDescentPeriods(int* prices, int pricesSize) {
    long long totalPeriods = 0;
    long long currentDescentLength = 1;

    for (int i = 1; i < pricesSize; i++) {
        if (prices[i] == prices[i - 1] - 1) {
            currentDescentLength++;
        } else {
            totalPeriods += (currentDescentLength * (currentDescentLength + 1)) / 2;
            currentDescentLength = 1;
        }
    }

    totalPeriods += (currentDescentLength * (currentDescentLength + 1)) / 2;

    return totalPeriods;        
}
