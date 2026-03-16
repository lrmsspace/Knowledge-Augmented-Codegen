# Source: https://leetcode.com/problems/the-number-of-the-smallest-unoccupied-chair/   |   Difficulty: Medium
#
# Problem Description:
# There is a party where n friends numbered from 0 to n - 1 are attending. There is an infinite number of chairs in this party that are numbered from 0 to infinity. When a friend arrives at the party, they sit on the unoccupied chair with the smallest number.
#
#
# 	For example, if chairs 0, 1, and 5 are occupied when a friend comes, they will sit on chair number 2.
#
#
# When a friend leaves the party, their chair becomes unoccupied at the moment they leave. If another friend arrives at that same moment, they can sit in that chair.
#
# You are given a 0-indexed 2D integer array times where times[i] = [arrivali, leavingi], indicating the arrival and leaving times of the ith friend respectively, and an integer targetFriend. All arrival times are distinct.
#
# Return the chair number that the friend numbered targetFriend will sit on.
#
# Example:
# Input: times = [[1,4],[2,3],[4,6]], targetFriend = 1
# Output: 1
# Explanation: 
# - Friend 0 arrives at time 1 and sits on chair 0.
# - Friend 1 arrives at time 2 and sits on chair 1.
# - Friend 1 leaves at time 3 and chair 1 becomes empty.
# - Friend 0 leaves at time 4 and chair 0 becomes empty.
# - Friend 2 arrives at time 4 and sits on chair 0.
# Since friend 1 sat on chair 1, we return 1.
#
# Constraints:
# n == times.length
# 	2 <= n <= 104
# 	times[i].length == 2
# 	1 <= arrivali < leavingi <= 105
# 	0 <= targetFriend <= n - 1
# 	Each arrivali time is distinct.
#
# Helpful references (internal KB):
# - Optimal schedule of jobs given their deadlines and durations (heap, interval, greedy, simulation)
#   • When to use: When needing to find an optimal schedule for a set of jobs, each with a deadline and duration, typically to maximize completed jobs or minimize total lateness. This approach often involves processing jobs based on deadlines and dynamically selecting tasks.
#   • Idea: This algorithm finds an optimal job schedule by processing jobs sorted by their deadlines, using a priority queue to manage available tasks. It greedily selects jobs with the shortest run-time that can be completed within the current time window, achieving an optimal solution in O(N log N) time complexity.
#   • Invariants: All jobs with deadlines greater than the current job's deadline have been considered.; The priority queue contains jobs that can potentially be scheduled within the current time window.
#   • Tips: Sort jobs by deadline in descending order to process later deadlines first.; Use a min-priority queue to efficiently retrieve the job with the least run-time.
#   • Pitfalls: Incorrectly sorting jobs (e.g., ascending deadline or by duration).; Not handling overlapping time intervals or deadlines properly.
# - MEX (minimal excluded) of a sequence (array, enumeration)
#   • When to use: Use when you need to find the smallest non-negative integer that is not present in a given collection of numbers. It's often applied in problems involving game theory or combinatorial analysis.
#   • Idea: This algorithm finds the smallest non-negative integer not present in a given sequence or set. It typically involves marking present numbers and then iterating from zero to find the first unmarked number, achieving O(N) or O(N log N) complexity.
#   • Invariants: All non-negative integers less than the current candidate MEX value have been found in the input sequence.; The data structure used for presence tracking accurately reflects which non-negative integers up to a certain bound are present.
#   • Tips: Use a boolean array or hash set for efficient presence checking.; The MEX value is at most N (for N elements) if all numbers are distinct and within [0, N-1].
#   • Pitfalls: Forgetting to handle the case where all numbers from 0 to N-1 are present, meaning MEX is N.; Using an inefficient method for presence checking, leading to higher time complexity.
# -  
# Kth order statistic in O(N) (array, quickselect, randomized)
#   • When to use: When you need to efficiently find the Kth smallest or largest element in an unsorted array. It is ideal when a full sort is unnecessary and average linear time performance is acceptable.
#   • Idea: Quickselect is a selection algorithm that finds the Kth smallest element in an unsorted list by repeatedly partitioning the array around a pivot. It achieves an average time complexity of O(N) and a worst-case complexity of O(N^2).
#   • Invariants: All elements in the left partition are less than or equal to the pivot element.; All elements in the right partition are greater than or equal to the pivot element.
#   • Tips: Shuffle the input array or choose a random pivot to achieve average O(N) performance.; The algorithm modifies the input array in place, so a copy might be needed if the original must be preserved.
#   • Pitfalls: A consistently bad pivot choice (e.g., always smallest/largest) leads to O(N^2) worst-case time.; Not suitable if the relative order of other elements needs to be preserved (it's not a stable algorithm).
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def smallestChair(self, times, targetFriend):
        """
        :type times: List[List[int]]
        :type targetFriend: int
        :rtype: int
        """
        import heapq

        events = []
        for i, (arrive, leave) in enumerate(times):
            events.append((arrive, 'arrive', i))
            events.append((leave, 'leave', i))
        events.sort()

        available_chairs = list(range(len(times)))
        heapq.heapify(available_chairs)

        friend_to_chair = {}

        for time, event_type, friend in events:
            if event_type == 'arrive':
                chair = heapq.heappop(available_chairs)
                friend_to_chair[friend] = chair
                if friend == targetFriend:
                    return chair
            else:  # leave
                chair = friend_to_chair[friend]
                heapq.heappush(available_chairs, chair)