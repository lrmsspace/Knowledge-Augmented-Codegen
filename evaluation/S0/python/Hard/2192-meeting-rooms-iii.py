# Source: https://leetcode.com/problems/meeting-rooms-iii/   |   Difficulty: Hard
#
# Problem Description:
# You are given an integer n. There are n rooms numbered from 0 to n - 1.
#
# You are given a 2D integer array meetings where meetings[i] = [starti, endi] means that a meeting will be held during the half-closed time interval [starti, endi). All the values of starti are unique.
#
# Meetings are allocated to rooms in the following manner:
#
#
# 	Each meeting will take place in the unused room with the lowest number.
# 	If there are no available rooms, the meeting will be delayed until a room becomes free. The delayed meeting should have the same duration as the original meeting.
# 	When a room becomes unused, meetings that have an earlier original start time should be given the room.
#
#
# Return the number of the room that held the most meetings. If there are multiple rooms, return the room with the lowest number.
#
# A half-closed interval [a, b) is the interval between a and b including a and not including b.
#
# Example:
# Input: n = 2, meetings = [[0,10],[1,5],[2,7],[3,4]]
# Output: 0
# Explanation:
# - At time 0, both rooms are not being used. The first meeting starts in room 0.
# - At time 1, only room 1 is not being used. The second meeting starts in room 1.
# - At time 2, both rooms are being used. The third meeting is delayed.
# - At time 3, both rooms are being used. The fourth meeting is delayed.
# - At time 5, the meeting in room 1 finishes. The third meeting starts in room 1 for the time period [5,10).
# - At time 10, the meetings in both rooms finish. The fourth meeting starts in room 0 for the time period [10,11).
# Both rooms 0 and 1 held 2 meetings, so we return 0.
#
# Constraints:
# 1 <= n <= 100
# 	1 <= meetings.length <= 105
# 	meetings[i].length == 2
# 	0 <= starti < endi <= 5 * 105
# 	All the values of starti are unique.
#

class Solution(object):
    def mostBooked(self, n, meetings):
        """
        :type n: int
        :type meetings: List[List[int]]
        :rtype: int
        """
        import heapq

        meetings.sort(key=lambda x: x[0])
        free_rooms = list(range(n))
        busy_rooms = []
        room_meetings_count = [0] * n

        for start, end in meetings:
            while busy_rooms and busy_rooms[0][0] <= start:
                _, room_id = heapq.heappop(busy_rooms)
                heapq.heappush(free_rooms, room_id)

            if free_rooms:
                room_id = heapq.heappop(free_rooms)
                actual_start = start
            else:
                actual_end, room_id = heapq.heappop(busy_rooms)
                actual_start = actual_end

            actual_end = actual_start + (end - start)
            heapq.heappush(busy_rooms, (actual_end, room_id))
            room_meetings_count[room_id] += 1

        max_meetings = max(room_meetings_count)
        for i in range(n):
            if room_meetings_count[i] == max_meetings:
                return i