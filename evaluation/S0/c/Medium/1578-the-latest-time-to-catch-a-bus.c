// Source: https://leetcode.com/problems/the-latest-time-to-catch-a-bus/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array buses of length n, where buses[i] represents the departure time of the ith bus. You are also given a 0-indexed integer array passengers of length m, where passengers[j] represents the arrival time of the jth passenger. All bus departure times are unique. All passenger arrival times are unique.
//
// You are given an integer capacity, which represents the maximum number of passengers that can get on each bus.
//
// When a passenger arrives, they will wait in line for the next available bus. You can get on a bus that departs at x minutes if you arrive at y minutes where y <= x, and the bus is not full. Passengers with the earliest arrival times get on the bus first.
//
// More formally when a bus arrives, either:
//
//
// 	If capacity or fewer passengers are waiting for a bus, they will all get on the bus, or
// 	The capacity passengers with the earliest arrival times will get on the bus.
//
//
// Return the latest time you may arrive at the bus station to catch a bus. You cannot arrive at the same time as another passenger.
//
// Note: The arrays buses and passengers are not necessarily sorted.
//
// Example:
// Input: buses = [10,20], passengers = [2,17,18,19], capacity = 2
// Output: 16
// Explanation: Suppose you arrive at time 16.
// At time 10, the first bus departs with the 0th passenger. 
// At time 20, the second bus departs with you and the 1st passenger.
// Note that you may not arrive at the same time as another passenger, which is why you must arrive before the 1st passenger to catch the bus.
//
// Constraints:
// n == buses.length
// 	m == passengers.length
// 	1 <= n, m, capacity <= 105
// 	2 <= buses[i], passengers[i] <= 109
// 	Each element in buses is unique.
// 	Each element in passengers is unique.
//

int latestTimeCatchTheBus(int* buses, int busesSize, int* passengers, int passengersSize, int capacity) {
    // Sort buses and passengers
    qsort(buses, busesSize, sizeof(int), (int (*)(const void*, const void*))strcmp);
    qsort(passengers, passengersSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int passengerIndex = 0;
    int latestTime = -1;

    for (int i = 0; i < busesSize; i++) {
        int busTime = buses[i];
        int boarded = 0;

        // Board passengers onto the bus
        while (passengerIndex < passengersSize && passengers[passengerIndex] <= busTime && boarded < capacity) {
            boarded++;
            passengerIndex++;
        }

        // Determine the latest time to catch this bus
        if (boarded < capacity) {
            latestTime = busTime; // Bus has space, can arrive at bus time
        } else {
            latestTime = passengers[passengerIndex - 1] - 1; // Bus is full, arrive before the last boarded passenger
        }
    }

    // Ensure latestTime does not coincide with any passenger arrival time
    while (1) {
        int conflict = 0;
        for (int j = 0; j < passengersSize; j++) {
            if (passengers[j] == latestTime) {
                conflict = 1;
                break;
            }
        }
        if (!conflict) {
            break;
        }
        latestTime--;
    }

    return latestTime;      
}
