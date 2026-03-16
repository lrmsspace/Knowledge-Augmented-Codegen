// Source: https://leetcode.com/problems/minimum-time-to-complete-trips/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array time where time[i] denotes the time taken by the ith bus to complete one trip.
//
// Each bus can make multiple trips successively; that is, the next trip can start immediately after completing the current trip. Also, each bus operates independently; that is, the trips of one bus do not influence the trips of any other bus.
//
// You are also given an integer totalTrips, which denotes the number of trips all buses should make in total. Return the minimum time required for all buses to complete at least totalTrips trips.
//
// Example:
// Input: time = [1,2,3], totalTrips = 5
// Output: 3
// Explanation:
// - At time t = 1, the number of trips completed by each bus are [1,0,0]. 
//   The total number of trips completed is 1 + 0 + 0 = 1.
// - At time t = 2, the number of trips completed by each bus are [2,1,0]. 
//   The total number of trips completed is 2 + 1 + 0 = 3.
// - At time t = 3, the number of trips completed by each bus are [3,1,1]. 
//   The total number of trips completed is 3 + 1 + 1 = 5.
// So the minimum time needed for all buses to complete at least 5 trips is 3.
//
// Constraints:
// 1 <= time.length <= 105
// 	1 <= time[i], totalTrips <= 107
//
// Helpful references (internal KB):
// - Binary search (interval, number, binary-search-answer, enumeration)
//   • When to use: When searching for a specific element in a sorted collection or finding an optimal value over a monotonic function within a defined range. It efficiently reduces the search space by half in each step.
//   • Idea: A search algorithm that finds the position of a target value within a sorted array or determines a value that satisfies a monotonic predicate. It operates in logarithmic time complexity, O(log N).
//   • Invariants: The potential answer always lies within the current search interval `[low, high]`.; All elements strictly less than `low` have been determined not to be the answer.
//   • Tips: Ensure the search space exhibits a monotonic property.; Carefully define the `low` and `high` bounds for the search interval.
//   • Pitfalls: Incorrectly updating `low` or `high` bounds leading to infinite loops.; Off-by-one errors in array indexing or loop conditions.
// - Number of divisors / sum of divisors (number, counting, enumeration)
//   • When to use: Use this when you need to efficiently calculate the total count or sum of all positive divisors for a given integer. It is applicable in number theory problems or combinatorial tasks involving factors.
//   • Idea: This method computes the number of divisors and sum of divisors of an integer n by first finding its prime factorization. The core idea leverages properties of multiplicative functions, with a typical complexity of O(sqrt(n)) for factorization.
//   • Invariants: During prime factorization, temp_n always holds the remaining unfactored part of the original number.; The current_prime_factor iterates through potential prime divisors in increasing order.
//   • Tips: First find the prime factorization n = p1^a1 * p2^a2 * ... * pk^ak.; Number of divisors d(n) = (a1+1)(a2+1)...(ak+1).
//   • Pitfalls: Forgetting to handle the special case of n=1 (1 divisor, sum 1).; Incorrectly calculating powers or sums, especially for large exponents.
// - Knapsack Problem (array, knapsack, dp-1d, enumeration)
//   • When to use: Use when selecting items from a set to maximize or minimize a value under a capacity constraint. It's also applicable for partitioning problems with a fixed budget.
//   • Idea: This algorithm finds the maximum value that can be obtained by selecting a subset of items, each with a weight and a value, such that their total weight does not exceed a given capacity. It typically uses dynamic programming with a time complexity of O(N*W), where N is the number of items and W is the capacity.
//   • Invariants: After processing item `i`, `dp[w]` stores the maximum value for capacity `w` using items up to `i`.; For each item, `dp[w]` is updated considering either including or excluding the current item.
//   • Tips: Use a 2D DP table `dp[i][w]` for item `i` and weight `w` for clarity, then optimize to 1D.; When optimizing to 1D, iterate weights downwards to avoid using an item multiple times.
//   • Pitfalls: Incorrectly initializing the DP table can lead to wrong results or infinite loops.; Forgetting to iterate weights downwards in 1D DP can lead to items being picked multiple times (unbounded knapsack).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

long long minimumTime(int* time, int timeSize, int totalTrips) {
    long long left = 1;
    long long right = (long long)1e14; // A large enough upper bound
    long long answer = right;

    while (left <= right) {
        long long mid = left + (right - left) / 2;
        long long trips_completed = 0;

        for (int i = 0; i < timeSize; i++) {
            trips_completed += mid / time[i];
            if (trips_completed >= totalTrips) {
                break; // No need to count further if we already reached the target
            }
        }

        if (trips_completed >= totalTrips) {
            answer = mid; // Found a potential answer
            right = mid - 1; // Try to find a smaller time
        } else {
            left = mid + 1; // Increase time
        }
    }

    return answer;      
}
