// Source: https://leetcode.com/problems/car-fleet-ii/   |   Difficulty: Hard
//
// Problem Description:
// There are n cars traveling at different speeds in the same direction along a one-lane road. You are given an array cars of length n, where cars[i] = [positioni, speedi] represents:
//
//
// 	positioni is the distance between the ith car and the beginning of the road in meters. It is guaranteed that positioni < positioni+1.
// 	speedi is the initial speed of the ith car in meters per second.
//
//
// For simplicity, cars can be considered as points moving along the number line. Two cars collide when they occupy the same position. Once a car collides with another car, they unite and form a single car fleet. The cars in the formed fleet will have the same position and the same speed, which is the initial speed of the slowest car in the fleet.
//
// Return an array answer, where answer[i] is the time, in seconds, at which the ith car collides with the next car, or -1 if the car does not collide with the next car. Answers within 10-5 of the actual answers are accepted.
//
// Example:
// Input: cars = [[1,2],[2,1],[4,3],[7,2]]
// Output: [1.00000,-1.00000,3.00000,-1.00000]
// Explanation: After exactly one second, the first car will collide with the second car, and form a car fleet with speed 1 m/s. After exactly 3 seconds, the third car will collide with the fourth car, and form a car fleet with speed 2 m/s.
//
// Constraints:
// 1 <= cars.length <= 105
// 	1 <= positioni, speedi <= 106
// 	positioni < positioni+1
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
double* getCollisionTimes(int** cars, int carsSize, int* carsColSize, int* returnSize) {
    if (!returnSize || !cars || carsSize <= 0 || !carsColSize || carsColSize[0] != 2)
        return NULL;

    double *res = (double*)malloc(carsSize * sizeof(double));
    if (!res) return NULL;

    int *stack = (int*)malloc(carsSize * sizeof(int));
    if (!stack) { free(res); return NULL; }

    int top = -1; /* stack is empty */

    for (int i = carsSize - 1; i >= 0; --i) {
        res[i] = -1.0;
        int pos_i = cars[i][0];
        int speed_i = cars[i][1];

        while (top >= 0) {
            int j = stack[top];
            int pos_j = cars[j][0];
            int speed_j = cars[j][1];

            if (speed_i <= speed_j) {
                /* car i will never catch up to car j */
                --top;
                continue;
            }

            double t_ij = (double)(pos_j - pos_i) / (speed_i - speed_j);
            if (res[j] < 0 || t_ij <= res[j]) {
                res[i] = t_ij;
                break;
            } else {
                /* car j will collide before car i can catch it */
                --top;
            }
        }

        stack[++top] = i;
    }

    free(stack);
    *returnSize = carsSize;
    return res;     
}
