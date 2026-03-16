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
// - kth-largest-element-in-an-array (array, merge-sort)
//   • When to use: Use Merge Sort when a stable, guaranteed O(N log N) time complexity is required, especially for large datasets or linked lists where random access is costly.
//   • Idea: Merge Sort is a divide-and-conquer algorithm that recursively divides an array into halves, sorts them, and then merges the sorted halves. It has a time complexity of O(N log N) and a space complexity of O(N).
//   • Invariants: Each sub-array passed to merge is sorted.; The merge operation combines two sorted sub-arrays into a single sorted array.
//   • Tips: Implement the merge step carefully to maintain stability.; Consider iterative implementation to avoid recursion depth limits.
//   • Pitfalls: High space complexity due to auxiliary arrays.; Overhead of recursion can be significant for small inputs.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
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
    // Create an array of pairs (position, speed)
    typedef struct {
        int position;
        int speed;
    } Car;

    Car* cars = (Car*)malloc(positionSize * sizeof(Car));
    for (int i = 0; i < positionSize; i++) {
        cars[i].position = position[i];
        cars[i].speed = speed[i];
    }

    // Sort cars based on their starting position in descending order
    int compare(const void* a, const void* b) {
        Car* carA = (Car*)a;
        Car* carB = (Car*)b;
        return carB->position - carA->position;
    }
    qsort(cars, positionSize, sizeof(Car), compare);

    // Calculate the time it takes for each car to reach the target
    double* times = (double*)malloc(positionSize * sizeof(double));
    for (int i = 0; i < positionSize; i++) {
        times[i] = (double)(target - cars[i].position) / cars[i].speed;
    }

    // Count the number of fleets
    int fleets = 0;
    double lastTime = 0.0;

    for (int i = 0; i < positionSize; i++) {
        if (times[i] > lastTime) {
            fleets++;
            lastTime = times[i];
        }
    }

    free(cars);
    free(times);
    
    return fleets;      
}
