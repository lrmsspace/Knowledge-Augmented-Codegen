// Source: https://leetcode.com/problems/minimum-number-of-refueling-stops/   |   Difficulty: Hard
//
// Problem Description:
// A car travels from a starting position to a destination which is target miles east of the starting position.
//
// There are gas stations along the way. The gas stations are represented as an array stations where stations[i] = [positioni, fueli] indicates that the ith gas station is positioni miles east of the starting position and has fueli liters of gas.
//
// The car starts with an infinite tank of gas, which initially has startFuel liters of fuel in it. It uses one liter of gas per one mile that it drives. When the car reaches a gas station, it may stop and refuel, transferring all the gas from the station into the car.
//
// Return the minimum number of refueling stops the car must make in order to reach its destination. If it cannot reach the destination, return -1.
//
// Note that if the car reaches a gas station with 0 fuel left, the car can still refuel there. If the car reaches the destination with 0 fuel left, it is still considered to have arrived.
//
// Example:
// Input: target = 1, startFuel = 1, stations = []
// Output: 0
// Explanation: We can reach the target without refueling.
//
// Constraints:
// 1 <= target, startFuel <= 109
// 	0 <= stations.length <= 500
// 	1 <= positioni < positioni+1 < target
// 	1 <= fueli < 109
//
// Helpful references (internal KB):
// - Search the subarray with the maximum/minimum sum (array, greedy, dp-1d)
//   • When to use: When you need to find the contiguous subarray within a one-dimensional array of numbers that has the largest or smallest sum, typically in linear time.
//   • Idea: This algorithm efficiently finds the maximum (or minimum) sum of a contiguous subarray by iterating through the array and maintaining a current sum, resetting it if it becomes detrimental. It operates in O(N) time complexity with O(1) space complexity.
//   • Invariants: `global_max` holds the maximum sum of any contiguous subarray encountered up to the current element.; `current_max` holds the maximum sum of a contiguous subarray ending at the current element.
//   • Tips: Initialize current and global maximums appropriately (e.g., to negative infinity or first element).; Adapt for minimum sum by resetting current sum if it becomes positive.
//   • Pitfalls: Failing to correctly initialize maximum/minimum sum variables.; Not handling arrays where all elements are negative (for max sum) or positive (for min sum).
// - Digit DP (array, number, digit-dp)
//   • When to use: Use Digit DP to count numbers within a given range [a, b] that satisfy a property based on their digits. It's effective when the property can be checked digit by digit.
//   • Idea: Digit DP is a dynamic programming technique to count numbers within a given range [A, B] that satisfy specific properties related to their digits. It typically involves a recursive function with memoization, building numbers digit by digit, and has a complexity roughly proportional to (number of digits * state space).
//   • Invariants: The `tight` parameter accurately reflects if the current prefix matches the upper bound's prefix.; The `is_leading_zero` parameter correctly indicates if all preceding digits chosen were zero.
//   • Tips: Define the DP state carefully, including index, tight constraint, and leading zero flag.; Handle leading zeros correctly, as they can affect properties like sum or count of digits.
//   • Pitfalls: Incorrectly handling the 'tight' constraint, leading to overcounting or undercounting.; Forgetting to account for leading zeros or mismanaging their impact on the property.
// - Generating all K-combinations (array, enumeration, greedy)
//   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
//   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
//   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
//   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
//   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int minRefuelStops(int target, int startFuel, int** stations, int stationsSize, int* stationsColSize) {
    // This problem can be solved using a greedy approach with a max heap (priority queue).
    // We will keep track of the maximum fuel we can get from the stations we have passed.
    // Whenever we run out of fuel, we will refuel at the station that offers the most fuel among the ones we have passed.

    // Create a max heap to store the fuel amounts from the stations we have passed.
    int* maxHeap = (int*)malloc(stationsSize * sizeof(int));
    int heapSize = 0;

    int currentFuel = startFuel;
    int refuelStops = 0;
    int stationIndex = 0;

    while (currentFuel < target) {
        // Add all stations that we can reach with the current fuel to the max heap.
        while (stationIndex < stationsSize && stations[stationIndex][0] <= currentFuel) {
            maxHeap[heapSize++] = stations[stationIndex][1];
            stationIndex++;
        }

        // If we cannot reach any more stations and we haven't reached the target, return -1.
        if (heapSize == 0) {
            free(maxHeap);
            return -1;
        }

        // Refuel at the station with the most fuel available.
        currentFuel += maxHeap[--heapSize];
        refuelStops++;
    }

    free(maxHeap);
    return refuelStops;     
}
