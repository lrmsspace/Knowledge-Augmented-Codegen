# Source: https://leetcode.com/problems/maximum-number-of-eaten-apples/   |   Difficulty: Medium
#
# Problem Description:
# There is a special kind of apple tree that grows apples every day for n days. On the ith day, the tree grows apples[i] apples that will rot after days[i] days, that is on day i + days[i] the apples will be rotten and cannot be eaten. On some days, the apple tree does not grow any apples, which are denoted by apples[i] == 0 and days[i] == 0.
#
# You decided to eat at most one apple a day (to keep the doctors away). Note that you can keep eating after the first n days.
#
# Given two integer arrays days and apples of length n, return the maximum number of apples you can eat.
#
# Example:
# Input: apples = [1,2,3,5,2], days = [3,2,1,4,2]
# Output: 7
# Explanation: You can eat 7 apples:
# - On the first day, you eat an apple that grew on the first day.
# - On the second day, you eat an apple that grew on the second day.
# - On the third day, you eat an apple that grew on the second day. After this day, the apples that grew on the third day rot.
# - On the fourth to the seventh days, you eat apples that grew on the fourth day.
#
# Constraints:
# n == apples.length == days.length
# 	1 <= n <= 2 * 104
# 	0 <= apples[i], days[i] <= 2 * 104
# 	days[i] = 0 if and only if apples[i] = 0.
#
# Helpful references (internal KB):
# - Optimal schedule of jobs given their deadlines and durations (array, heap, greedy)
#   • When to use: Use when given a set of tasks with deadlines and durations, and the objective is to maximize the number of completed tasks without interruption.
#   • Idea: This greedy algorithm aims to maximize the number of jobs completed by prioritizing tasks that finish earliest. It typically involves sorting and using a min-heap, achieving an O(N log N) time complexity.
#   • Invariants: All jobs processed up to the current point have been considered for scheduling.; The set of jobs in the heap represents the jobs currently scheduled to meet their deadlines.
#   • Tips: Sort jobs by their deadlines in ascending order.; Maintain a min-heap of durations for jobs currently scheduled.
#   • Pitfalls: Confusing job count maximization with total duration or profit.; Failing to update the current time correctly after scheduling a job.
# - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
#   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
#   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
#   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
#   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
#   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
# - Priority Queues (array, heap, heap-select)
#   • When to use: Use when an in-place sorting algorithm with O(N log N) worst-case time complexity is required, especially when memory constraints are a concern. It's also applicable for efficiently finding the K largest/smallest elements.
#   • Idea: Heapsort is an in-place comparison-based sorting algorithm that uses a binary heap data structure. It first builds a max-heap from the input array, then repeatedly extracts the maximum element and places it at the end of the array, achieving O(N log N) time complexity.
#   • Invariants: During heap construction, the processed subarray forms a valid heap-ordered complete binary tree.; During sortdown, the elements in `arr[0...i]` form a valid heap, and `arr[i+1...N-1]` contains sorted elements.
#   • Tips: Heap construction can be done in linear time using a bottom-up sink-based approach.; Heapsort is an in-place sorting algorithm, requiring O(1) auxiliary space.
#   • Pitfalls: Heapsort is not a stable sorting algorithm; the relative order of equal elements is not preserved.; Cache performance can be poor due to non-sequential memory access patterns during heap operations.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def eatenApples(self, apples, days):
        """
        :type apples: List[int]
        :type days: List[int]
        :rtype: int
        """
        import heapq
        
        heap = []
        ans = 0
        n = len(apples)
        
        for i in range(n):
            if apples[i] > 0:
                heapq.heappush(heap, (i + days[i], apples[i]))
            
            while heap and (heap[0][0] <= i or heap[0][1] <= 0):
                heapq.heappop(heap)
            
            if heap:
                ans += 1
                heap[0] = (heap[0][0], heap[0][1] - 1)
        
        i = n
        while heap:
            while heap and (heap[0][0] <= i or heap[0][1] <= 0):
                heapq.heappop(heap)
            
            if not heap:
                break
            
            ans += 1
            heap[0] = (heap[0][0], heap[0][1] - 1)
            i += 1
        
        return ans