# Source: https://leetcode.com/problems/maximize-the-minimum-powered-city/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed integer array stations of length n, where stations[i] represents the number of power stations in the ith city.
#
# Each power station can provide power to every city in a fixed range. In other words, if the range is denoted by r, then a power station at city i can provide power to all cities j such that |i - j| <= r and 0 <= i, j <= n - 1.
#
#
# 	Note that |x| denotes absolute value. For example, |7 - 5| = 2 and |3 - 10| = 7.
#
#
# The power of a city is the total number of power stations it is being provided power from.
#
# The government has sanctioned building k more power stations, each of which can be built in any city, and have the same range as the pre-existing ones.
#
# Given the two integers r and k, return the maximum possible minimum power of a city, if the additional power stations are built optimally.
#
# Note that you can build the k power stations in multiple cities.
#
# Example:
# Input: stations = [1,2,4,5,0], r = 1, k = 2
# Output: 5
# Explanation: 
# One of the optimal ways is to install both the power stations at city 1. 
# So stations will become [1,4,4,5,0].
# - City 0 is provided by 1 + 4 = 5 power stations.
# - City 1 is provided by 1 + 4 + 4 = 9 power stations.
# - City 2 is provided by 4 + 4 + 5 = 13 power stations.
# - City 3 is provided by 5 + 4 = 9 power stations.
# - City 4 is provided by 5 + 0 = 5 power stations.
# So the minimum power of a city is 5.
# Since it is not possible to obtain a larger power, we return 5.
#
# Constraints:
# n == stations.length
# 	1 <= n <= 105
# 	0 <= stations[i] <= 105
# 	0 <= r <= n - 1
# 	0 <= k <= 109
#

class Solution(object):
    def maxPower(self, stations, r, k):
        """
        :type stations: List[int]
        :type r: int
        :type k: int
        :rtype: int
        """
        n = len(stations)
        
        def canAchieve(minPower):
            added = [0] * n
            totalAdded = 0
            currentPower = 0
            
            for i in range(n):
                if i - r - 1 >= 0:
                    currentPower -= stations[i - r - 1] + added[i - r - 1]
                
                currentPower += stations[min(i + r, n - 1)] + added[min(i + r, n - 1)]
                
                if currentPower < minPower:
                    need = minPower - currentPower
                    if totalAdded + need > k:
                        return False
                    totalAdded += need
                    added[min(i + r, n - 1)] += need
                    currentPower += need
            
            return True
        
        left, right = 0, sum(stations) + k
        answer = 0
        
        while left <= right:
            mid = (left + right) // 2
            if canAchieve(mid):
                answer = mid
                left = mid + 1
            else:
                right = mid - 1
        
        return answer