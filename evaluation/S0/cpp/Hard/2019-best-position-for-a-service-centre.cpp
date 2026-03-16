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

class Solution {
public:
    double getMinDistSum(vector<vector<int>>& positions) {
        double x = 50.0, y = 50.0;  // initial guess
        double step = 50.0;
        double learningRate = 0.5;
        double tolerance = 1e-7;
        
        auto computeDistSum = [&](double cx, double cy) {
            double sum = 0.0;
            for (const auto& pos : positions) {
                double dx = cx - pos[0];
                double dy = cy - pos[1];
                sum += sqrt(dx * dx + dy * dy);
            }
            return sum;
        };
        
        for (int iter = 0; iter < 10000; iter++) {
            double currentDistSum = computeDistSum(x, y);
            double bestDistSum = currentDistSum;
            double bestX = x, bestY = y;
            
            // Explore in four directions
            vector<pair<double, double>> directions = {
                {step, 0}, {-step, 0}, {0, step}, {0, -step}
            };
            
            for (const auto& dir : directions) {
                double newX = x + dir.first;
                double newY = y + dir.second;
                double newDistSum = computeDistSum(newX, newY);
                
                if (newDistSum < bestDistSum) {
                    bestDistSum = newDistSum;
                    bestX = newX;
                    bestY = newY;
                }
            }
            
            if (bestDistSum < currentDistSum) {
                x = bestX;
                y = bestY;
            } else {
                step *= learningRate;  // reduce step size
            }
            
            if (step < tolerance) break;  // convergence
        }
        
        return computeDistSum(x, y);            
    }
};
