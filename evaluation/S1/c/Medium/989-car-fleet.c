// Source: https://leetcode.com/problems/car-fleet/   |   Difficulty: Medium
//
// Problem Description:
// There are n cars at given miles away from the starting mile 0, traveling to reach the mile target.
//
// You are given two integer arrays position and speed, both of length n, where position[i] is the starting mile of the ith car and speed[i] is the speed of the ith car in miles per hour.
//
// A car cannot pass another car, but it can catch up and then travel next to it at the speed of the slower car.
//
// A car fleet is a single car or a group of cars driving next to each other. The speed of the car fleet is the minimum speed of any car in the fleet.
//
// If a car catches up to a car fleet at the mile target, it will still be considered as part of the car fleet.
//
// Return the number of car fleets that will arrive at the destination.
//
// Example:
// Input: target = 12, position = [10,8,0,5,3], speed = [2,4,1,1,3]
//
// Output: 3
//
// Explanation:
//
//
// 	The cars starting at 10 (speed 2) and 8 (speed 4) become a fleet, meeting each other at 12. The fleet forms at target.
// 	The car starting at 0 (speed 1) does not catch up to any other car, so it is a fleet by itself.
// 	The cars starting at 5 (speed 1) and 3 (speed 3) become a fleet, meeting each other at 6. The fleet moves at speed 1 until it reaches target.
//
// Constraints:
// n == position.length == speed.length
// 	1 <= n <= 105
// 	0 < target <= 106
// 	0 <= position[i] < target
// 	All the values of position are unique.
// 	0 < speed[i] <= 106
//
// Helpful references (internal KB):
// - Mergesort (array, merge-sort)
//   • When to use: Use when a stable, guaranteed O(N log N) time complexity sort is required, especially for large datasets or when external sorting is beneficial. It is also suitable for linked lists where random access is inefficient.
//   • Idea: Mergesort is a divide-and-conquer sorting algorithm that recursively divides an array into two halves, sorts them, and then merges the sorted halves. It guarantees O(N log N) time complexity and O(N) space complexity.
//   • Invariants: Before merging, the left subarray `a[lo...mid]` and the right subarray `a[mid+1...hi]` are sorted.; During the merge, `a[lo...k-1]` contains the `k-lo` smallest elements from `aux[lo...hi]` in sorted order.
//   • Tips: Utilize an auxiliary array for merging to maintain stability and simplify the merge logic.; Consider the bottom-up iterative implementation to avoid recursion depth limits and potentially improve cache performance.
//   • Pitfalls: Requires O(N) auxiliary space, which can be a significant concern for memory-constrained environments.; Recursive implementations can lead to stack overflow errors for extremely large input arrays.
// - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
//   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
//   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
//   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
//   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
//   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
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

int carFleet(int target, int* position, int positionSize, int* speed, int speedSize) {
    // Pair positions with speeds
    typedef struct {
        int pos;
        int spd;
    } Car;

    Car* cars = (Car*)malloc(positionSize * sizeof(Car));
    for (int i = 0; i < positionSize; i++) {
        cars[i].pos = position[i];
        cars[i].spd = speed[i];
    }

    // Sort cars by position in descending order using mergesort
    void merge(Car* arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        Car* L = (Car*)malloc(n1 * sizeof(Car));
        Car* R = (Car*)malloc(n2 * sizeof(Car));

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i].pos >= R[j].pos) {
                arr[k++] = L[i++];
            } else {
                arr[k++] = R[j++];
            }
        }

        while (i < n1) {
            arr[k++] = L[i++];
        }
        while (j < n2) {
            arr[k++] = R[j++];
        }

        free(L);
        free(R);
    }

    void mergeSort(Car* arr, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);
            merge(arr, left, mid, right);
        }
    }

    mergeSort(cars, 0, positionSize - 1);

    // Calculate fleets
    int fleetCount = 0;
    double lastArrivalTime = -1.0;

    for (int i = 0; i < positionSize; i++) {
        double timeToTarget = (double)(target - cars[i].pos) / cars[i].spd;
        if (timeToTarget > lastArrivalTime) {
            fleetCount++;
            lastArrivalTime = timeToTarget;
        }
    }
    free(cars);
    return fleetCount;
}
