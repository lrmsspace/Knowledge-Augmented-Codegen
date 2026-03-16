# Source: https://leetcode.com/problems/minimum-time-to-finish-the-race/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed 2D integer array tires where tires[i] = [fi, ri] indicates that the ith tire can finish its xth successive lap in fi * ri(x-1) seconds.
#
#
# 	For example, if fi = 3 and ri = 2, then the tire would finish its 1st lap in 3 seconds, its 2nd lap in 3 * 2 = 6 seconds, its 3rd lap in 3 * 22 = 12 seconds, etc.
#
#
# You are also given an integer changeTime and an integer numLaps.
#
# The race consists of numLaps laps and you may start the race with any tire. You have an unlimited supply of each tire and after every lap, you may change to any given tire (including the current tire type) if you wait changeTime seconds.
#
# Return the minimum time to finish the race.
#
# Example:
# Input: tires = [[2,3],[3,4]], changeTime = 5, numLaps = 4
# Output: 21
# Explanation: 
# Lap 1: Start with tire 0 and finish the lap in 2 seconds.
# Lap 2: Continue with tire 0 and finish the lap in 2 * 3 = 6 seconds.
# Lap 3: Change tires to a new tire 0 for 5 seconds and then finish the lap in another 2 seconds.
# Lap 4: Continue with tire 0 and finish the lap in 2 * 3 = 6 seconds.
# Total time = 2 + 6 + 5 + 2 + 6 = 21 seconds.
# The minimum time to complete the race is 21 seconds.
#
# Constraints:
# 1 <= tires.length <= 105
# 	tires[i].length == 2
# 	1 <= fi, changeTime <= 105
# 	2 <= ri <= 105
# 	1 <= numLaps <= 1000
#

class Solution(object):
    def minimumFinishTime(self, tires, changeTime, numLaps):
        """
        :type tires: List[List[int]]
        :type changeTime: int
        :type numLaps: int
        :rtype: int
        """
        import math
        max_laps = 18  # Based on constraints and tire degradation
        
        dp = [math.inf] * (numLaps + 1)
        dp[0] = 0
        
        min_time_for_laps = [math.inf] * (max_laps + 1)
        
        for f, r in tires:
            time = f
            total_time = f
            for lap in range(1, max_laps + 1):
                if total_time > changeTime + f:
                    break
                min_time_for_laps[lap] = min(min_time_for_laps[lap], total_time)
                time *= r
                total_time += time
        
        for laps in range(1, numLaps + 1):
            for k in range(1, min(laps, max_laps) + 1):
                dp[laps] = min(dp[laps], dp[laps - k] + min_time_for_laps[k] + (changeTime if laps != k else 0))
        
        return dp[numLaps]