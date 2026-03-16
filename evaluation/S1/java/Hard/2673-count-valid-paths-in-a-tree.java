// Source: https://leetcode.com/problems/count-valid-paths-in-a-tree/   |   Difficulty: Hard
//
// Problem Description:
// There is an undirected tree with n nodes labeled from 1 to n. You are given the integer n and a 2D integer array edges of length n - 1, where edges[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the tree.
//
// Return the number of valid paths in the tree.
//
// A path (a, b) is valid if there exists exactly one prime number among the node labels in the path from a to b.
//
// Note that:
//
//
// 	The path (a, b) is a sequence of distinct nodes starting with node a and ending with node b such that every two adjacent nodes in the sequence share an edge in the tree.
// 	Path (a, b) and path (b, a) are considered the same and counted only once.
//
// Example:
// Input: n = 5, edges = [[1,2],[1,3],[2,4],[2,5]]
// Output: 4
// Explanation: The pairs with exactly one prime number on the path between them are: 
// - (1, 2) since the path from 1 to 2 contains prime number 2. 
// - (1, 3) since the path from 1 to 3 contains prime number 3.
// - (1, 4) since the path from 1 to 4 contains prime number 2.
// - (2, 4) since the path from 2 to 4 contains prime number 2.
// It can be shown that there are only 4 valid paths.
//
// Constraints:
// 1 <= n <= 105
// 	edges.length == n - 1
// 	edges[i].length == 2
// 	1 <= ui, vi <= n
// 	The input is generated such that edges represent a valid tree.
//
// Helpful references (internal KB):
// - Sieve of Eratosthenes (array, bitset, sieve)
//   • When to use: When you need to find all prime numbers up to a certain limit N, or efficiently check primality for many numbers within that range. It is ideal for precomputing primes.
//   • Idea: The Sieve of Eratosthenes efficiently finds all prime numbers up to a specified integer N by iteratively marking multiples of each prime. It achieves O(N log log N) time complexity and O(N) space.
//   • Invariants: For any number i less than the current prime p, is_prime[i] correctly reflects its primality.; All multiples of primes smaller than the current prime p have already been marked as composite.
//   • Tips: Optimize by starting marking multiples from p*p for each prime p.; Use a bitset for memory efficiency when N is large.
//   • Pitfalls: Forgetting to explicitly handle 0 and 1 as non-prime.; Incorrectly marking multiples, e.g., starting from 2*p instead of p*p.
// - Undirected Graphs (graph, array, simulation)
//   • When to use: When modeling symmetric relationships between entities and needing to explore, analyze connectivity, or find paths within the network. Useful for problems involving reachability or structural properties.
//   • Idea: Undirected graphs represent symmetric relationships between pairs of vertices. Simulation on them involves systematically exploring or processing these connections, often with O(V+E) complexity for basic traversals.
//   • Invariants: All vertices reachable from the source within 'k' edges have been processed by the 'k'-th step of BFS.; Each edge in the graph is traversed at most twice (once for each direction) during a full graph traversal.
//   • Tips: Use an adjacency list for sparse graphs to optimize space and traversal time.; Use an adjacency matrix for dense graphs or when O(1) edge existence checks are critical.
//   • Pitfalls: Forgetting to handle disconnected components, leading to incomplete graph processing.; Incorrectly representing undirected edges (e.g., only adding one direction to an adjacency list).
// - Counting labeled graphs (number, recursion, counting, dp-1d)
//   • When to use: When the problem requires enumerating distinct labeled graphs with specific properties, such as connectivity, on a given number of vertices. It is suitable for combinatorial counting problems involving graph structures.
//   • Idea: This technique determines the number of connected labeled graphs by subtracting the count of disconnected graphs from the total. It typically employs a recursive or dynamic programming approach, often involving combinatorial terms like binomial coefficients, with a polynomial time complexity.
//   • Invariants: The total number of labeled graphs $G_n$ for $n$ vertices is always $2^{n(n-1)/2}$.; For any $n$, the sum of connected and disconnected labeled graphs equals the total number of labeled graphs.
//   • Tips: Start with the total number of labeled graphs $G_n = 2^{n(n-1)/2}$.; Use complementary counting: total graphs minus disconnected graphs.
//   • Pitfalls: Forgetting to divide by $n$ when converting from rooted to unrooted disconnected graphs.; Incorrectly handling base cases for recursive definitions or DP states.
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public long countPaths(int n, int[][] edges) {
        // Step 1: Sieve of Eratosthenes to find all primes up to n
        boolean[] isPrime = new boolean[n + 1];
        Arrays.fill(isPrime, 2, n + 1, true);
        for (int i = 2; i * i <= n; i++) {
            if (isPrime[i]) {
                for (int j = i * i; j <= n; j += i) {
                    isPrime[j] = false;
                }
            }
        }

        // Step 2: Build the tree as an adjacency list
        List<List<Integer>> graph = new ArrayList<>();
        for (int i = 0; i <= n; i++) {
            graph.add(new ArrayList<>());
        }
        for (int[] edge : edges) {
            graph.get(edge[0]).add(edge[1]);
            graph.get(edge[1]).add(edge[0]);
        }

        // Step 3: DFS to count valid paths
        boolean[] visited = new boolean[n + 1];
        long result = 0;

        for (int node = 1; node <= n; node++) {
            if (isPrime[node] && !visited[node]) {
                int primeCount = dfsCount(graph, visited, isPrime, node);
                result += (long) primeCount * (n - primeCount);
            }
        }

        return result;          
    }
}
