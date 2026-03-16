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
// Helpful references (internal KB):
// - Mergesort (array, merge-sort)
//   • When to use: Use when a stable, guaranteed O(N log N) time complexity sort is required, especially for large datasets or when external sorting is beneficial. It is also suitable for linked lists where random access is inefficient.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and O(N) space complexity.
//   • Invariants: Before merging, the left subarray `a[lo...mid]` and the right subarray `a[mid+1...hi]` are sorted.; During the merge, `a[lo...k-1]` contains the `k-lo` smallest elements from `aux[lo...hi]` in sorted order.
//   • Tips: Utilize an auxiliary array for merging to maintain stability and simplify the merge logic.; Consider the bottom-up iterative implementation to avoid recursion depth limits and potentially improve cache performance.
//   • Pitfalls: Requires O(N) auxiliary space, which can be a significant concern for memory-constrained environments.; Recursive implementations can lead to stack overflow errors for extremely large input arrays.
// - Scheduling jobs on two machines (array, number, simulation, enumeration)
//   • When to use: Use when determining the optimal sequence of jobs to minimize the total completion time (makespan) on two machines, with a fixed processing order (machine 1 then machine 2) for all jobs.
//   • Idea: This problem involves ordering N jobs, each with two processing times (one for each machine), to minimize the overall makespan. Johnson's rule provides an optimal greedy solution for this specific two-machine flow shop problem in O(N log N) or O(N) time.
//   • Invariants: All jobs processed so far maintain the optimal relative order determined by Johnson's rule.; The current makespan is the minimum possible for the jobs already scheduled.
//   • Tips: Sort jobs based on Johnson's rule criteria: jobs with min(a_i, b_i).; Prioritize jobs with shorter machine 1 times or longer machine 2 times for early scheduling.
//   • Pitfalls: Applying Johnson's rule to problems with more than two machines, where it is not optimal.; Incorrectly sorting jobs within the two partitioned sets.
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int latestTimeCatchTheBus(vector<int>& buses, vector<int>& passengers, int capacity) {
        sort(buses.begin(), buses.end());
        sort(passengers.begin(), passengers.end());

        int busIdx = 0;
        int passIdx = 0;
        int n = buses.size();
        int m = passengers.size();

        int latestTime = -1;

        for (busIdx = 0; busIdx < n; ++busIdx) {
            int cap = capacity;
            // Board passengers onto the current bus
            while (passIdx < m && passengers[passIdx] <= buses[busIdx] && cap > 0) {
                --cap;
                ++passIdx;
            }

            // Determine latest time to catch this bus
            if (cap > 0) {
                // Bus not full, can arrive at bus departure time
                latestTime = max(latestTime, buses[busIdx]);
            } else {
                // Bus full, arrive just before the last boarded passenger
                int lastPassengerTime = passengers[passIdx - 1];
                if (lastPassengerTime - 1 >= 0) {
                    latestTime = max(latestTime, lastPassengerTime - 1);
                }
            }
        }

        // Ensure latestTime does not coincide with any passenger arrival time
        unordered_set<int> passengerSet(passengers.begin(), passengers.end());
        while (passengerSet.count(latestTime)) {
            --latestTime;
        }

        return latestTime;          
    }
};
