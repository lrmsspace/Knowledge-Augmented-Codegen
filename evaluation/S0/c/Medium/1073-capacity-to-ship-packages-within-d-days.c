// Source: https://leetcode.com/problems/capacity-to-ship-packages-within-d-days/   |   Difficulty: Medium
//
// Problem Description:
// A conveyor belt has packages that must be shipped from one port to another within days days.
//
// The ith package on the conveyor belt has a weight of weights[i]. Each day, we load the ship with packages on the conveyor belt (in the order given by weights). We may not load more weight than the maximum weight capacity of the ship.
//
// Return the least weight capacity of the ship that will result in all the packages on the conveyor belt being shipped within days days.
//
// Example:
// Input: weights = [1,2,3,4,5,6,7,8,9,10], days = 5
// Output: 15
// Explanation: A ship capacity of 15 is the minimum to ship all the packages in 5 days like this:
// 1st day: 1, 2, 3, 4, 5
// 2nd day: 6, 7
// 3rd day: 8
// 4th day: 9
// 5th day: 10
//
// Note that the cargo must be shipped in the order given, so using a ship of capacity 14 and splitting the packages into parts like (2, 3, 4, 5), (1, 6, 7), (8), (9), (10) is not allowed.
//
// Constraints:
// 1 <= days <= weights.length <= 5 * 104
// 	1 <= weights[i] <= 500
//

int shipWithinDays(int* weights, int weightsSize, int days) {
    int left = 0, right = 0;
    for (int i = 0; i < weightsSize; i++) {
        if (weights[i] > left) {
            left = weights[i];
        }
        right += weights[i];
    }

    while (left < right) {
        int mid = left + (right - left) / 2;
        int currentWeight = 0;
        int requiredDays = 1;

        for (int i = 0; i < weightsSize; i++) {
            if (currentWeight + weights[i] > mid) {
                requiredDays++;
                currentWeight = 0;
            }
            currentWeight += weights[i];
        }

        if (requiredDays > days) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }

    return left;        
}
