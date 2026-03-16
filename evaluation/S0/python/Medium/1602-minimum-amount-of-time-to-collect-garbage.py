# Source: https://leetcode.com/problems/minimum-amount-of-time-to-collect-garbage/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed array of strings garbage where garbage[i] represents the assortment of garbage at the ith house. garbage[i] consists only of the characters 'M', 'P' and 'G' representing one unit of metal, paper and glass garbage respectively. Picking up one unit of any type of garbage takes 1 minute.
#
# You are also given a 0-indexed integer array travel where travel[i] is the number of minutes needed to go from house i to house i + 1.
#
# There are three garbage trucks in the city, each responsible for picking up one type of garbage. Each garbage truck starts at house 0 and must visit each house in order; however, they do not need to visit every house.
#
# Only one garbage truck may be used at any given moment. While one truck is driving or picking up garbage, the other two trucks cannot do anything.
#
# Return the minimum number of minutes needed to pick up all the garbage.
#
# Example:
# Input: garbage = ["G","P","GP","GG"], travel = [2,4,3]
# Output: 21
# Explanation:
# The paper garbage truck:
# 1. Travels from house 0 to house 1
# 2. Collects the paper garbage at house 1
# 3. Travels from house 1 to house 2
# 4. Collects the paper garbage at house 2
# Altogether, it takes 8 minutes to pick up all the paper garbage.
# The glass garbage truck:
# 1. Collects the glass garbage at house 0
# 2. Travels from house 0 to house 1
# 3. Travels from house 1 to house 2
# 4. Collects the glass garbage at house 2
# 5. Travels from house 2 to house 3
# 6. Collects the glass garbage at house 3
# Altogether, it takes 13 minutes to pick up all the glass garbage.
# Since there is no metal garbage, we do not need to consider the metal garbage truck.
# Therefore, it takes a total of 8 + 13 = 21 minutes to collect all the garbage.
#
# Constraints:
# 2 <= garbage.length <= 105
# 	garbage[i] consists of only the letters 'M', 'P', and 'G'.
# 	1 <= garbage[i].length <= 10
# 	travel.length == garbage.length - 1
# 	1 <= travel[i] <= 100
#

class Solution(object):
    def garbageCollection(self, garbage, travel):
        """
        :type garbage: List[str]
        :type travel: List[int]
        :rtype: int
        """
        total_time = 0
        last_seen = {'M': 0, 'P': 0, 'G': 0}
        
        # Calculate total garbage collection time and last seen indices
        for i in range(len(garbage)):
            total_time += len(garbage[i])
            for g in 'MPG':
                if g in garbage[i]:
                    last_seen[g] = i
        
        # Calculate travel time for each garbage truck
        travel_time = [0] * len(travel)
        for i in range(1, len(travel_time)):
            travel_time[i] = travel_time[i - 1] + travel[i - 1]
        
        for g in 'MPG':
            if last_seen[g] > 0:
                total_time += travel_time[last_seen[g] - 1]
        
        return total_time