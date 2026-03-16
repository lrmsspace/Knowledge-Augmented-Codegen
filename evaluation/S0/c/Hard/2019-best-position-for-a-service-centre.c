// Source: https://leetcode.com/problems/best-position-for-a-service-centre/   |   Difficulty: Hard
//
// Problem Description:
// A delivery company wants to build a new service center in a new city. The company knows the positions of all the customers in this city on a 2D-Map and wants to build the new center in a position such that the sum of the euclidean distances to all customers is minimum.
//
// Given an array positions where positions[i] = [xi, yi] is the position of the ith customer on the map, return the minimum sum of the euclidean distances to all customers.
//
// In other words, you need to choose the position of the service center [xcentre, ycentre] such that the following formula is minimized:
//
// Answers within 10-5 of the actual value will be accepted.
//
// Example:
// Input: positions = [[0,1],[1,0],[1,2],[2,1]]
// Output: 4.00000
// Explanation: As shown, you can see that choosing [xcentre, ycentre] = [1, 1] will make the distance to each customer = 1, the sum of all distances is 4 which is the minimum possible we can achieve.
//
// Constraints:
// 1 <= positions.length <= 50
// 	positions[i].length == 2
// 	0 <= xi, yi <= 100
//

double getMinDistSum(int** positions, int positionsSize, int* positionsColSize) {
    double x = 50.0, y = 50.0; /* initial guess */
    double step = 50.0;
    double learningRate = 0.5;
    double tolerance = 1e-7;
    int maxIter = 10000;

    for (int iter = 0; iter < maxIter; ++iter) {
        double gradX = 0.0, gradY = 0.0;
        for (int i = 0; i < positionsSize; ++i) {
            double dx = x - positions[i][0];
            double dy = y - positions[i][1];
            double dist = sqrt(dx * dx + dy * dy);
            if (dist > 1e-10) { /* avoid division by zero */
                gradX += dx / dist;
                gradY += dy / dist;
            }
        }
        double newX = x - learningRate * gradX;
        double newY = y - learningRate * gradY;

        if (fabs(newX - x) < tolerance && fabs(newY - y) < tolerance) {
            break; /* convergence */
        }
        x = newX;
        y = newY;
    }

    double totalDist = 0.0;
    for (int i = 0; i < positionsSize; ++i) {
        double dx = x - positions[i][0];
        double dy = y - positions[i][1];
        totalDist += sqrt(dx * dx + dy * dy);
    }
    return totalDist;       
}
