# Source: https://leetcode.com/problems/maximum-population-year/   |   Difficulty: Easy
#
# Problem Description:
# You are given a 2D integer array logs where each logs[i] = [birthi, deathi] indicates the birth and death years of the ith person.
#
# The population of some year x is the number of people alive during that year. The ith person is counted in year x's population if x is in the inclusive range [birthi, deathi - 1]. Note that the person is not counted in the year that they die.
#
# Return the earliest year with the maximum population.
#
# Example:
# Input: logs = [[1993,1999],[2000,2010]]
# Output: 1993
# Explanation: The maximum population is 1, and 1993 is the earliest year with this population.
#
# Constraints:
# 1 <= logs.length <= 100
# 	1950 <= birthi < deathi <= 2050
#

class Solution(object):
    def maximumPopulation(self, logs):
        """
        :type logs: List[List[int]]
        :rtype: int
        """
        year_count = {}
        
        for birth, death in logs:
            for year in range(birth, death):
                if year in year_count:
                    year_count[year] += 1
                else:
                    year_count[year] = 1
        
        max_population = max(year_count.values())
        earliest_year = min(year for year, count in year_count.items() if count == max_population)
        
        return earliest_year