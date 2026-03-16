# Source: https://leetcode.com/problems/day-of-the-year/   |   Difficulty: Easy
#
# Problem Description:
# Given a string date representing a Gregorian calendar date formatted as YYYY-MM-DD, return the day number of the year.
#
# Example:
# Input: date = "2019-01-09"
# Output: 9
# Explanation: Given date is the 9th day of the year in 2019.
#
# Constraints:
# date.length == 10
# 	date[4] == date[7] == '-', and all other date[i]'s are digits
# 	date represents a calendar date between Jan 1st, 1900 and Dec 31st, 2019.
#

class Solution(object):
    def dayOfYear(self, date):
        """
        :type date: str
        :rtype: int
        """
        year, month, day = map(int, date.split('-'))
        days_in_month = [31, 28 + self.is_leap_year(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
        return sum(days_in_month[:month - 1]) + day