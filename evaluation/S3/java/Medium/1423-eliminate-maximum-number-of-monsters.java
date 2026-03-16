// Source: https://leetcode.com/problems/eliminate-maximum-number-of-monsters/   |   Difficulty: Medium
//
// Problem Description:
// You are playing a video game where you are defending your city from a group of n monsters. You are given a 0-indexed integer array dist of size n, where dist[i] is the initial distance in kilometers of the ith monster from the city.
//
// The monsters walk toward the city at a constant speed. The speed of each monster is given to you in an integer array speed of size n, where speed[i] is the speed of the ith monster in kilometers per minute.
//
// You have a weapon that, once fully charged, can eliminate a single monster. However, the weapon takes one minute to charge. The weapon is fully charged at the very start.
//
// You lose when any monster reaches your city. If a monster reaches the city at the exact moment the weapon is fully charged, it counts as a loss, and the game ends before you can use your weapon.
//
// Return the maximum number of monsters that you can eliminate before you lose, or n if you can eliminate all the monsters before they reach the city.
//
// Example:
// Input: dist = [1,3,4], speed = [1,1,1]
// Output: 3
// Explanation:
// In the beginning, the distances of the monsters are [1,3,4]. You eliminate the first monster.
// After a minute, the distances of the monsters are [X,2,3]. You eliminate the second monster.
// After a minute, the distances of the monsters are [X,X,2]. You eliminate the third monster.
// All 3 monsters can be eliminated.
//
// Constraints:
// n == dist.length == speed.length
// 	1 <= n <= 105
// 	1 <= dist[i], speed[i] <= 105
//
// Helpful references (internal KB):
// - Sqrt Decomposition (array, enumeration, difference-array)
//   • When to use: Efficiently calculate sums or properties over various ranges in a static array. Useful for many range queries or when combining range updates with point queries.
//   • Idea: Prefix sums allow O(1) range sum queries after O(N) preprocessing. Difference arrays enable O(1) range updates and O(N) point queries after O(N) reconstruction.
//   • Invariants: The prefix sum array P[i] stores the sum of elements from A[0] to A[i-1].; The difference array D[i] stores A[i] - A[i-1] (for i > 0).
//   • Tips: Precompute prefix sums to answer range sum queries in constant time.; Use a difference array to apply range updates efficiently.
//   • Pitfalls: Off-by-one errors in range boundaries for prefix sums.; Forgetting to initialize the difference array correctly (e.g., diff[0] = arr[0] for 0-indexed).
// -  
// Kth order statistic in O(N) (array, enumeration)
//   • When to use: Use when you need to find the Kth smallest or largest element in an unsorted array efficiently, without sorting the entire dataset. It's ideal for problems requiring a specific order statistic in linear average time.
//   • Idea: This algorithm finds the Kth smallest (or largest) element in an unsorted array in expected linear time, O(N), by repeatedly partitioning the array around a pivot. It is a selection algorithm, conceptually similar to quicksort but only recursing on one side.
//   • Invariants: All elements to the left of the chosen pivot are less than or equal to the pivot.; All elements to the right of the chosen pivot are greater than or equal to the pivot.
//   • Tips: Choose a good pivot (e.g., random element) to minimize the chance of worst-case performance.; The algorithm can be implemented iteratively to avoid potential recursion depth limits for very large inputs.
//   • Pitfalls: Poor pivot selection can lead to a worst-case time complexity of O(N^2).; Off-by-one errors are common when translating K (1-based) to array indices (0-based).
// - Sqrt Decomposition (array, enumeration, prefix-sum)
//   • When to use: Use when frequent range queries and point/range updates are needed on an array, offering a balanced O(sqrt(N)) time complexity for both operations. It's a good alternative when a segment tree is too complex or overkill.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and updates. It achieves an O(sqrt(N)) time complexity for both query and update operations.
//   • Invariants: Each block maintains an up-to-date aggregate of its elements.; For any query, fully contained blocks are processed using their precomputed aggregates.
//   • Tips: Choose block size carefully, typically sqrt(N) for optimal balance.; Precompute block aggregates (sum, min, max) for efficient queries.
//   • Pitfalls: Incorrectly handling partial blocks or boundary conditions.; Off-by-one errors in block indices or element indices within blocks.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public int eliminateMaximum(int[] dist, int[] speed) {
        int n = dist.length;
        int[] timeToReachCity = new int[n];
        for (int i = 0; i < n; i++) {
            timeToReachCity[i] = (dist[i] + speed[i] - 1) / speed[i]; // Calculate time to reach city, rounding up
        }
        Arrays.sort(timeToReachCity); // Sort the times to reach the city

        for (int i = 0; i < n; i++) {
            if (timeToReachCity[i] <= i) { // If the monster reaches the city before or at the time we can eliminate it
                return i; // Return the number of monsters eliminated before losing
            }
        }
        return n; // All monsters can be eliminated         
    }
}
