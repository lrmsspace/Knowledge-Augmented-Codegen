# Source: https://leetcode.com/problems/maximum-performance-of-a-team/   |   Difficulty: Hard
#
# Problem Description:
# You are given two integers n and k and two integer arrays speed and efficiency both of length n. There are n engineers numbered from 1 to n. speed[i] and efficiency[i] represent the speed and efficiency of the ith engineer respectively.
#
# Choose at most k different engineers out of the n engineers to form a team with the maximum performance.
#
# The performance of a team is the sum of its engineers' speeds multiplied by the minimum efficiency among its engineers.
#
# Return the maximum performance of this team. Since the answer can be a huge number, return it modulo 109 + 7.
#
# Example:
# Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 2
# Output: 60
# Explanation: 
# We have the maximum performance of the team by selecting engineer 2 (with speed=10 and efficiency=4) and engineer 5 (with speed=5 and efficiency=7). That is, performance = (10 + 5) * min(4, 7) = 60.
#
# Constraints:
# 1 <= k <= n <= 105
# 	speed.length == n
# 	efficiency.length == n
# 	1 <= speed[i] <= 105
# 	1 <= efficiency[i] <= 108
#

class Solution(object):
    def maxPerformance(self, n, speed, efficiency, k):
        """
        :type n: int
        :type speed: List[int]
        :type efficiency: List[int]
        :type k: int
        :rtype: int
        """
        import heapq

        engineers = sorted(zip(efficiency, speed), reverse=True)
        max_perf = 0
        speed_heap = []
        speed_sum = 0

        for curr_eff, curr_speed in engineers:
            heapq.heappush(speed_heap, curr_speed)
            speed_sum += curr_speed

            if len(speed_heap) > k:
                speed_sum -= heapq.heappop(speed_heap)

            max_perf = max(max_perf, speed_sum * curr_eff)

        return max_perf % (10**9 + 7)   