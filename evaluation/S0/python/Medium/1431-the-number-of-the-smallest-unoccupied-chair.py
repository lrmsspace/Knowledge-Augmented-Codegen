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

class Solution(object):
    def smallestChair(self, times, targetFriend):
        """
        :type times: List[List[int]]
        :type targetFriend: int
        :rtype: int
        """
        import heapq

        # Add friend index to each time entry
        for i in range(len(times)):
            times[i].append(i)

        # Sort by arrival time
        times.sort(key=lambda x: x[0])

        # Min-heap for available chairs
        available_chairs = []
        # Min-heap for occupied chairs (leaving time, chair number)
        occupied_chairs = []

        chair_count = 0

        for arrival, leaving, friend_index in times:
            # Free up chairs that have been vacated by the time of arrival
            while occupied_chairs and occupied_chairs[0][0] <= arrival:
                _, chair_num = heapq.heappop(occupied_chairs)
                heapq.heappush(available_chairs, chair_num)

            # Assign chair to the arriving friend
            if available_chairs:
                chair_num = heapq.heappop(available_chairs)
            else:
                chair_num = chair_count
                chair_count += 1

            # If this is the target friend, return the chair number
            if friend_index == targetFriend:
                return chair_num

            # Mark the chair as occupied until the leaving time
            heapq.heappush(occupied_chairs, (leaving, chair_num))