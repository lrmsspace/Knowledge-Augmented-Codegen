// Source: https://leetcode.com/problems/max-value-of-equation/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array points containing the coordinates of points on a 2D plane, sorted by the x-values, where points[i] = [xi, yi] such that xi < xj for all 1 <= i < j <= points.length. You are also given an integer k.
//
// Return the maximum value of the equation yi + yj + |xi - xj| where |xi - xj| <= k and 1 <= i < j <= points.length.
//
// It is guaranteed that there exists at least one pair of points that satisfy the constraint |xi - xj| <= k.
//
// Example:
// Input: points = [[1,3],[2,0],[5,10],[6,-10]], k = 1
// Output: 4
// Explanation: The first two points satisfy the condition |xi - xj| <= 1 and if we calculate the equation we get 3 + 0 + |1 - 2| = 4. Third and fourth points also satisfy the condition and give a value of 10 + -10 + |5 - 6| = 1.
// No other pairs satisfy the condition, so we return the max of 4 and 1.
//
// Constraints:
// 2 <= points.length <= 105
// 	points[i].length == 2
// 	-108 <= xi, yi <= 108
// 	0 <= k <= 2 * 108
// 	xi < xj for all 1 <= i < j <= points.length
// 	xi form a strictly increasing sequence.
//

int findMaxValueOfEquation(int** points, int pointsSize, int* pointsColSize, int k) {
    int maxValue = -2147483648; // INT_MIN
    int *deque = (int*)malloc(pointsSize * sizeof(int));
    int front = 0, back = 0;

    for (int j = 0; j < pointsSize; ++j) {
        int xj = points[j][0];
        int yj = points[j][1];

        // Remove points from the front of the deque that are out of range
        while (front < back && xj - points[deque[front]][0] > k) {
            front++;
        }

        // Calculate max value using the front of the deque
        if (front < back) {
            int i = deque[front];
            int xi = points[i][0];
            int yi = points[i][1];
            int currentValue = yi + yj + (xj - xi);
            if (currentValue > maxValue) {
                maxValue = currentValue;
            }
        }

        // Maintain the deque to keep only useful points
        while (front < back && (points[deque[back - 1]][1] - points[deque[back - 1]][0]) <= (yj - xj)) {
            back--;
        }
        deque[back++] = j;
    }

    free(deque);
    return maxValue;        
}
