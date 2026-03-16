# Source: https://leetcode.com/problems/merge-operations-for-minimum-travel-time/   |   Difficulty: Hard
#
# Problem Description:
# You are given a straight road of length l km, an integer n, an integer k, and two integer arrays, position and time, each of length n.
#
# The array position lists the positions (in km) of signs in strictly increasing order (with position[0] = 0 and position[n - 1] = l).
#
# Each time[i] represents the time (in minutes) required to travel 1 km between position[i] and position[i + 1].
#
# You must perform exactly k merge operations. In one merge, you can choose any two adjacent signs at indices i and i + 1 (with i > 0 and i + 1 < n) and:
#
#
#  Update the sign at index i + 1 so that its time becomes time[i] + time[i + 1].
#  Remove the sign at index i.
#
#
# Return the minimum total travel time (in minutes) to travel from 0 to l after exactly k merges.
#
# Example:
# Input: l = 10, n = 4, k = 1, position = [0,3,8,10], time = [5,8,3,6]
#
# Output: 62
#
# Explanation:
#
#
#  
#  Merge the signs at indices 1 and 2. Remove the sign at index 1, and change the time at index 2 to 8 + 3 = 11.
#  
#  After the merge:
#  
#   position array: [0, 8, 10]
#   time array: [5, 11, 6]
#    
#  
#  
#  
#  
#   
#    
#     Segment
#     Distance (km)
#     Time per km (min)
#     Segment Travel Time (min)
#    
#   
#   
#    
#     0 → 8
#     8
#     5
#     8 × 5 = 40
#    
#    
#     8 → 10
#     2
#     11
#     2 × 11 = 22
#    
#   
#  
#  
#  Total Travel Time: 40 + 22 = 62, which is the minimum possible time after exactly 1 merge.
#
# Constraints:
# 1 <= l <= 105
#  2 <= n <= min(l + 1, 50)
#  0 <= k <= min(n - 2, 10)
#  position.length == n
#  position[0] = 0 and position[n - 1] = l
#  position is sorted in strictly increasing order.
#  time.length == n
#  1 <= time[i] <= 100​
#  1 <= sum(time) <= 100​​​​​​
#

class Solution(object):
    def minTravelTime(self, l, n, k, position, time):
        """
        :type l: int
        :type n: int
        :type k: int
        :type position: List[int]
        :type time: List[int]
        :rtype: int
        """
        import heapq

        segments = []
        for i in range(n - 1):
            distance = position[i + 1] - position[i]
            travel_time = distance * time[i]
            segments.append([travel_time, distance, time[i]])

        heap = []
        for i in range(len(segments) - 1):
            merged_travel_time = (segments[i][1] + segments[i + 1][1]) * (segments[i][2] + segments[i + 1][2])
            cost = merged_travel_time - (segments[i][0] + segments[i + 1][0])
            heapq.heappush(heap, (cost, i))

        total_travel_time = sum(seg[0] for seg in segments)

        for _ in range(k):
            while True:
                cost, idx = heapq.heappop(heap)
                if idx < len(segments) - 1 and segments[idx] is not None and segments[idx + 1] is not None:
                    break

            total_travel_time += cost
            merged_distance = segments[idx][1] + segments[idx + 1][1]
            merged_time = segments[idx][2] + segments[idx + 1][2]
            merged_travel_time = merged_distance * merged_time
            segments[idx] = [merged_travel_time, merged_distance, merged_time]
            segments[idx + 1] = None

            if idx > 0 and segments[idx - 1] is not None:
                left_merged_travel_time = (segments[idx - 1][1] + merged_distance) * (segments[idx - 1][2] + merged_time)
                left_cost = left_merged_travel_time - (segments[idx - 1][0] + merged_travel_time)
                heapq.heappush(heap, (left_cost, idx - 1))

            if idx + 2 < len(segments) and segments[idx + 2] is not None:
                right_merged_travel_time = (merged_distance + segments[idx + 2][1]) * (merged_time + segments[idx + 2][2])
                right_cost = right_merged_travel_time - (merged_travel_time + segments[idx + 2][0])
                heapq.heappush(heap, (right_cost, idx))

        return total_travel_time