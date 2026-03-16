// Source: https://leetcode.com/problems/car-pooling/   |   Difficulty: Medium
//
// Problem Description:
// There is a car with capacity empty seats. The vehicle only drives east (i.e., it cannot turn around and drive west).
//
// You are given the integer capacity and an array trips where trips[i] = [numPassengersi, fromi, toi] indicates that the ith trip has numPassengersi passengers and the locations to pick them up and drop them off are fromi and toi respectively. The locations are given as the number of kilometers due east from the car's initial location.
//
// Return true if it is possible to pick up and drop off all passengers for all the given trips, or false otherwise.
//
// Example:
// Input: trips = [[2,1,5],[3,3,7]], capacity = 4
// Output: false
//
// Constraints:
// 1 <= trips.length <= 1000
// 	trips[i].length == 3
// 	1 <= numPassengersi <= 100
// 	0 <= fromi < toi <= 1000
// 	1 <= capacity <= 105
//

class Solution {
public:
    bool carPooling(vector<vector<int>>& trips, int capacity) {
        vector<int> timeline(1001, 0);

        for (const auto& trip : trips) {
            int numPassengers = trip[0];
            int from = trip[1];
            int to = trip[2];

            timeline[from] += numPassengers;
            timeline[to] -= numPassengers;
        }

        int currentPassengers = 0;
        for (int passengersChange : timeline) {
            currentPassengers += passengersChange;
            if (currentPassengers > capacity) {
                return false;
            }
        }

        return true;            
    }
};
