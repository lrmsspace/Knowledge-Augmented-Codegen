// Source: https://leetcode.com/problems/separate-squares-i/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 2D integer array squares. Each squares[i] = [xi, yi, li] represents the coordinates of the bottom-left point and the side length of a square parallel to the x-axis.
//
// Find the minimum y-coordinate value of a horizontal line such that the total area of the squares above the line equals the total area of the squares below the line.
//
// Answers within 10-5 of the actual answer will be accepted.
//
// Note: Squares may overlap. Overlapping areas should be counted multiple times.
//
// Example:
// Input: squares = [[0,0,1],[2,2,1]]
//
// Output: 1.00000
//
// Explanation:
//
//
//
// Any horizontal line between y = 1 and y = 2 will have 1 square unit above it and 1 square unit below it. The lowest option is 1.
//
// Constraints:
// 1 <= squares.length <= 5 * 104
// 	squares[i] = [xi, yi, li]
// 	squares[i].length == 3
// 	0 <= xi, yi <= 109
// 	1 <= li <= 109
// 	The total area of all the squares will not exceed 1012.
//

class Solution {
    public double separateSquares(int[][] squares) {
        long totalArea = 0;
        for (int[] square : squares) {
            totalArea += (long) square[2] * square[2];
        }

        long targetArea = totalArea / 2;
        long low = 0, high = (long) 1e9 + 1;

        while (low < high) {
            long mid = low + (high - low) / 2;
            long areaBelow = 0;

            for (int[] square : squares) {
                int y = square[1];
                int l = square[2];

                if (mid <= y) {
                    continue;
                } else if (mid >= y + l) {
                    areaBelow += (long) l * l;
                } else {
                    long heightBelow = mid - y;
                    areaBelow += heightBelow * l;
                }
            }

            if (areaBelow < targetArea) {
                low = mid + 1;
            } else {
                high = mid;
            }
        }

        return low;         
    }
}
