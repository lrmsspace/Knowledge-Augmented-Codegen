// Source: https://leetcode.com/problems/maximize-distance-to-closest-person/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array representing a row of seats where seats[i] = 1 represents a person sitting in the ith seat, and seats[i] = 0 represents that the ith seat is empty (0-indexed).
//
// There is at least one empty seat, and at least one person sitting.
//
// Alex wants to sit in the seat such that the distance between him and the closest person to him is maximized. 
//
// Return that maximum distance to the closest person.
//
// Example:
// Input: seats = [1,0,0,0,1,0,1]
// Output: 2
// Explanation: 
// If Alex sits in the second open seat (i.e. seats[2]), then the closest person has distance 2.
// If Alex sits in any other open seat, the closest person has distance 1.
// Thus, the maximum distance to the closest person is 2.
//
// Constraints:
// 2 <= seats.length <= 2 * 104
// 	seats[i] is 0 or 1.
// 	At least one seat is empty.
// 	At least one seat is occupied.
//

int maxDistToClosest(int* seats, int seatsSize) {
    int max_distance = 0;
    int last_person_index = -1;

    for (int i = 0; i < seatsSize; i++) {
        if (seats[i] == 1) {
            if (last_person_index == -1) {
                max_distance = i; // Distance from the start to the first person
            } else {
                int distance = (i - last_person_index) / 2;
                if (distance > max_distance) {
                    max_distance = distance;
                }
            }
            last_person_index = i;
        }
    }

    // Check the distance from the last person to the end
    if (seatsSize - 1 - last_person_index > max_distance) {
        max_distance = seatsSize - 1 - last_person_index;
    }

    return max_distance;        
}
