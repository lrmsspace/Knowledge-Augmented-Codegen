# Source: https://leetcode.com/problems/time-to-cross-a-bridge/   |   Difficulty: Hard
#
# Problem Description:
# There are k workers who want to move n boxes from the right (old) warehouse to the left (new) warehouse. You are given the two integers n and k, and a 2D integer array time of size k x 4 where time[i] = [righti, picki, lefti, puti].
#
# The warehouses are separated by a river and connected by a bridge. Initially, all k workers are waiting on the left side of the bridge. To move the boxes, the ith worker can do the following:
#
#
# 	Cross the bridge to the right side in righti minutes.
# 	Pick a box from the right warehouse in picki minutes.
# 	Cross the bridge to the left side in lefti minutes.
# 	Put the box into the left warehouse in puti minutes.
#
#
# The ith worker is less efficient than the jth worker if either condition is met:
#
#
# 	lefti + righti > leftj + rightj
# 	lefti + righti == leftj + rightj and i > j
#
#
# The following rules regulate the movement of the workers through the bridge:
#
#
# 	Only one worker can use the bridge at a time.
# 	When the bridge is unused prioritize the least efficient worker (who have picked up the box) on the right side to cross. If not, prioritize the least efficient worker on the left side to cross.
# 	If enough workers have already been dispatched from the left side to pick up all the remaining boxes, no more workers will be sent from the left side.
#
#
# Return the elapsed minutes at which the last box reaches the left side of the bridge.
#
# Example:
# Input: n = 1, k = 3, time = [[1,1,2,1],[1,1,3,1],[1,1,4,1]]
#
# Output: 6
#
# Explanation:
#
#
# From 0 to 1 minutes: worker 2 crosses the bridge to the right.
# From 1 to 2 minutes: worker 2 picks up a box from the right warehouse.
# From 2 to 6 minutes: worker 2 crosses the bridge to the left.
# From 6 to 7 minutes: worker 2 puts a box at the left warehouse.
# The whole process ends after 7 minutes. We return 6 because the problem asks for the instance of time at which the last worker reaches the left side of the bridge.
#
# Constraints:
# 1 <= n, k <= 104
# 	time.length == k
# 	time[i].length == 4
# 	1 <= lefti, picki, righti, puti <= 1000
#
# Helpful references (internal KB):
# - Generating all K-combinations (array, enumeration, greedy)
#   • When to use: Use this when you need to iterate through all possible subsets of a fixed size K from a larger set, especially when a specific order like lexicographical is required.
#   • Idea: This algorithm systematically generates all unique combinations of K elements from a set of N elements. It typically proceeds in lexicographical order, allowing for efficient enumeration of all C(N, K) possibilities.
#   • Invariants: The current combination C is always sorted: C[0] < C[1] < ... < C[K-1].; All elements C[i] are distinct and within the range [0, N-1] (assuming 0-indexed).
#   • Tips: Start with the smallest lexicographical combination (e.g., {1, 2, ..., K}).; To find the next combination, locate the rightmost element that can be incremented.
#   • Pitfalls: Incorrectly handling boundary conditions when incrementing elements.; Duplicating combinations if not careful with the increment logic.
# - Scheduling jobs on two machines (array, number, simulation, enumeration)
#   • When to use: Use when determining the optimal sequence of jobs to minimize the total completion time (makespan) on two machines, with a fixed processing order (machine 1 then machine 2) for all jobs.
#   • Idea: This problem involves ordering N jobs, each with two processing times (one for each machine), to minimize the overall makespan. Johnson's rule provides an optimal greedy solution for this specific two-machine flow shop problem in O(N log N) or O(N) time.
#   • Invariants: All jobs processed so far maintain the optimal relative order determined by Johnson's rule.; The current makespan is the minimum possible for the jobs already scheduled.
#   • Tips: Sort jobs based on Johnson's rule criteria: jobs with min(a_i, b_i).; Prioritize jobs with shorter machine 1 times or longer machine 2 times for early scheduling.
#   • Pitfalls: Applying Johnson's rule to problems with more than two machines, where it is not optimal.; Incorrectly sorting jobs within the two partitioned sets.
# - Scheduling jobs on one machine (array, number, greedy, merge-sort)
#   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
#   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
#   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
#   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
#   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def findCrossingTime(self, n, k, time):
        """
        :type n: int
        :type k: int
        :type time: List[List[int]]
        :rtype: int
        """
        # Step 1: Calculate efficiency and sort workers
        workers = sorted([(time[i][0] + time[i][2], i) for i in range(k)], key=lambda x: (x[0], x[1]))

        # Step 2: Initialize priority queues for left and right sides
        left_queue = []
        right_queue = []
        for _, idx in workers:
            heapq.heappush(left_queue, (0, idx))  # (available_time, worker_index)

        current_time = 0
        boxes_moved = 0

        while boxes_moved < n:
            # Move workers from right to left if they are available
            while right_queue and right_queue[0][0] <= current_time:
                _, idx = heapq.heappop(right_queue)
                heapq.heappush(left_queue, (current_time + time[idx][3], idx))  # put time

            # Move workers from left to right if they are available and we still have boxes to move
            while left_queue and boxes_moved < n:
                available_time, idx = heapq.heappop(left_queue)
                if available_time > current_time:
                    current_time = available_time
                heapq.heappush(right_queue, (current_time + time[idx][0] + time[idx][1], idx))  # cross + pick time
                boxes_moved += 1

            # If no workers are moving, advance time to the next event
            if not right_queue and not left_queue:
                current_time += 1

        return current_time