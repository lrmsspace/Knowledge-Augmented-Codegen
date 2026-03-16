// Source: https://leetcode.com/problems/minimum-lines-to-represent-a-line-chart/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array stockPrices where stockPrices[i] = [dayi, pricei] indicates the price of the stock on day dayi is pricei. A line chart is created from the array by plotting the points on an XY plane with the X-axis representing the day and the Y-axis representing the price and connecting adjacent points. One such example is shown below:
//
// Return the minimum number of lines needed to represent the line chart.
//
// Example:
// Input: stockPrices = [[1,7],[2,6],[3,5],[4,4],[5,4],[6,3],[7,2],[8,1]]
// Output: 3
// Explanation:
// The diagram above represents the input, with the X-axis representing the day and Y-axis representing the price.
// The following 3 lines can be drawn to represent the line chart:
// - Line 1 (in red) from (1,7) to (4,4) passing through (1,7), (2,6), (3,5), and (4,4).
// - Line 2 (in blue) from (4,4) to (5,4).
// - Line 3 (in green) from (5,4) to (8,1) passing through (5,4), (6,3), (7,2), and (8,1).
// It can be shown that it is not possible to represent the line chart using less than 3 lines.
//
// Constraints:
// 1 <= stockPrices.length <= 105
// 	stockPrices[i].length == 2
// 	1 <= dayi, pricei <= 109
// 	All dayi are distinct.
//

/**
 * @param {number[][]} stockPrices
 * @return {number}
 */
var minimumLines = function(stockPrices) {
    stockPrices.sort((a, b) => a[0] - b[0]);

    let lines = 0;
    let prevSlope = null;

    for (let i = 1; i < stockPrices.length; i++) {
        const dx = stockPrices[i][0] - stockPrices[i - 1][0];
        const dy = stockPrices[i][1] - stockPrices[i - 1][1];
        const slope = dy / dx;

        if (slope !== prevSlope) {
            lines++;
            prevSlope = slope;
        }
    }

    return lines;
};