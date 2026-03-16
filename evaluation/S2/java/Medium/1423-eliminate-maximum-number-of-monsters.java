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
// - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
//   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
//   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
//   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
//   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
//   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
// - Finding a negative cycle in the graph (graph, array, bellman-ford)
//   • When to use: Use when a graph may contain negative edge weights and you need to find the shortest paths from a single source, or specifically to detect and identify negative cycles.
//   • Idea: The Bellman-Ford algorithm computes single-source shortest paths in a weighted graph, even with negative edge weights, and can detect negative cycles. It has a time complexity of O(VE).
//   • Invariants: After k iterations, dist[v] is the shortest path from the source to v using at most k edges.; If no negative cycle is reachable, dist[v] will be the true shortest path distance after V-1 iterations.
//   • Tips: Perform V-1 iterations for shortest path calculation, then one more for cycle detection.; A negative cycle exists if any distance can still be reduced in the V-th iteration.
//   • Pitfalls: Inefficient for graphs with only non-negative weights compared to Dijkstra's.; Does not directly work for undirected graphs with negative edges.
// - Lattice points inside non-lattice polygon (number, recursion, counting, gcd)
//   • When to use: Use when counting pairs or elements satisfying divisibility or GCD conditions. Also applicable for summing functions over pairs using number theory properties.
//   • Idea: This approach leverages number theoretic properties like GCD, LCM, and prime factorization to efficiently count elements or pairs satisfying specific criteria. It often involves iterating through divisors or multiples, achieving complexities like O(N log N) or O(sqrt N) per query.
//   • Invariants: All numbers processed so far have their relevant number-theoretic properties (e.g., prime factors, divisors) correctly determined.; The current count or sum accurately reflects all valid combinations found up to the current iteration.
//   • Tips: Precompute primes or divisors using a sieve for efficiency.; Utilize properties of GCD and LCM, such as gcd(a,b) * lcm(a,b) = a * b.
//   • Pitfalls: Overcounting or undercounting when using inclusion-exclusion.; Integer overflow with large products or sums.
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
        int[] timeToReach = new int[n];
        for (int i = 0; i < n; i++) {
            timeToReach[i] = (dist[i] + speed[i] - 1) / speed[i]; // Calculate time to reach city
        }
        Arrays.sort(timeToReach); // Sort by time to reach

        for (int i = 0; i < n; i++) {
            if (timeToReach[i] <= i) { // If the monster reaches before or at the same time as we can eliminate it
                return i; // Return the number of monsters eliminated before losing
            }
        }
        return n; // All monsters can be eliminated         
    }
}
