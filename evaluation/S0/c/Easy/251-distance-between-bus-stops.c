// Source: https://leetcode.com/problems/distance-between-bus-stops/   |   Difficulty: Easy
//
// Problem Description:
// A bus has n stops numbered from 0 to n - 1 that form a circle. We know the distance between all pairs of neighboring stops where distance[i] is the distance between the stops number i and (i + 1) % n.
//
// The bus goes along both directions i.e. clockwise and counterclockwise.
//
// Return the shortest distance between the given start and destination stops.
//
// Example:
// Input: distance = [1,2,3,4], start = 0, destination = 1
// Output: 1
// Explanation: Distance between 0 and 1 is 1 or 9, minimum is 1.
//
// Constraints:
// 1 <= n <= 10^4
// 	distance.length == n
// 	0 <= start, destination < n
// 	0 <= distance[i] <= 10^4
//



int distanceBetweenBusStops(int* distance, int distanceSize, int start, int destination){
    if (start > destination) {
        int temp = start;
        start = destination;
        destination = temp;
    }
    
    int clockwise_distance = 0;
    int counterclockwise_distance = 0;
    
    for (int i = 0; i < distanceSize; i++) {
        if (i >= start && i < destination) {
            clockwise_distance += distance[i];
        } else {
            counterclockwise_distance += distance[i];
        }
    }
    
    return clockwise_distance < counterclockwise_distance ? clockwise_distance : counterclockwise_distance;
}
