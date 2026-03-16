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

class Solution {
    public int minimumLines(int[][] stockPrices) {
        Arrays.sort(stockPrices, (a, b) -> Integer.compare(a[0], b[0]));
        int n = stockPrices.length;
        if (n <= 2) {
            return n - 1;
        }

        int lines = 1;
        for (int i = 2; i < n; i++) {
            long x1 = stockPrices[i - 2][0], y1 = stockPrices[i - 2][1];
            long x2 = stockPrices[i - 1][0], y2 = stockPrices[i - 1][1];
            long x3 = stockPrices[i][0], y3 = stockPrices[i][1];

            // Check if the slopes between (x1, y1) & (x2, y2) and (x2, y2) & (x3, y3) are equal
            if ((y2 - y1) * (x3 - x2) != (y3 - y2) * (x2 - x1)) {
                lines++;
            }
        }

        return lines;           
    }
}
