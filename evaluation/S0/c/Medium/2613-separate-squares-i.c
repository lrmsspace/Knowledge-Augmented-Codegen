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

double separateSquares(int** squares, int squaresSize, int* squaresColSize) {
    long long totalArea = 0;
    for (int i = 0; i < squaresSize; i++) {
        totalArea += (long long)squares[i][2] * squares[i][2];
    }
    
    double low = 0, high = 1e9;
    for (int iter = 0; iter < 100; iter++) {
        double mid = (low + high) / 2.0;
        long long areaBelow = 0;
        
        for (int i = 0; i < squaresSize; i++) {
            int y = squares[i][1];
            int l = squares[i][2];
            
            if (mid <= y) {
                continue;
            } else if (mid >= y + l) {
                areaBelow += (long long)l * l;
            } else {
                double h = mid - y;
                areaBelow += (long long)l * h;
            }
        }
        
        if (areaBelow * 2 < totalArea) {
            low = mid;
        } else {
            high = mid;
        }
    }
    
    return low;     
}
