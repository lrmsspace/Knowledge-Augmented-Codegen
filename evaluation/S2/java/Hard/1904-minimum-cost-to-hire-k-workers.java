// Source: https://leetcode.com/problems/minimum-cost-to-hire-k-workers/   |   Difficulty: Hard
//
// Problem Description:
// There are n workers. You are given two integer arrays quality and wage where quality[i] is the quality of the ith worker and wage[i] is the minimum wage expectation for the ith worker.
//
// We want to hire exactly k workers to form a paid group. To hire a group of k workers, we must pay them according to the following rules:
//
//
// 	Every worker in the paid group must be paid at least their minimum wage expectation.
// 	In the group, each worker's pay must be directly proportional to their quality. This means if a worker’s quality is double that of another worker in the group, then they must be paid twice as much as the other worker.
//
//
// Given the integer k, return the least amount of money needed to form a paid group satisfying the above conditions. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: quality = [10,20,5], wage = [70,50,30], k = 2
// Output: 105.00000
// Explanation: We pay 70 to 0th worker and 35 to 2nd worker.
//
// Constraints:
// n == quality.length == wage.length
// 	1 <= k <= n <= 104
// 	1 <= quality[i], wage[i] <= 104
//
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given method signatures unchanged.
// - Use only Java standard library (`java.*`); no external dependencies.
// - Do not change input/output formats or return value semantics.
// - Conformance: single public class 'Solution'; no 'package' statement; place any extra types as static inner classes.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
    public double mincostToHireWorkers(int[] quality, int[] wage, int k) {
        int n = quality.length;
        double[][] workers = new double[n][2];
        for (int i = 0; i < n; i++) {
            workers[i][0] = (double) wage[i] / quality[i]; // wage-to-quality ratio
            workers[i][1] = quality[i];
        }
        Arrays.sort(workers, Comparator.comparingDouble(a -> a[0]));

        PriorityQueue<Double> maxHeap = new PriorityQueue<>(Comparator.reverseOrder());
        double totalQuality = 0;
        double minCost = Double.MAX_VALUE;

        for (double[] worker : workers) {
            double ratio = worker[0];
            double q = worker[1];

            maxHeap.offer(q);
            totalQuality += q;

            if (maxHeap.size() > k) {
                totalQuality -= maxHeap.poll(); // remove the worker with the highest quality
            }

            if (maxHeap.size() == k) {
                minCost = Math.min(minCost, ratio * totalQuality); // calculate cost for current group of k workers
            }
        }

        return minCost;         
    }
}
