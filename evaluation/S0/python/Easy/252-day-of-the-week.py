# Source: https://leetcode.com/problems/day-of-the-week/   |   Difficulty: Easy
#
# Problem Description:
# Given a date, return the corresponding day of the week for that date.
#
# The input is given as three integers representing the day, month and year respectively.
#
# Return the answer as one of the following values {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"}.
#
# Example:
# Input: day = 31, month = 8, year = 2019
# Output: "Saturday"
#
# Constraints:
# The given dates are valid dates between the years 1971 and 2100.
#

class Solution(object):
    def dayOfTheWeek(self, day, month, year):
        """
        :type day: int
        :type month: int
        :type year: int
        :rtype: str
        """
        import datetime
        days = ["Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"]
        date = datetime.date(year, month, day)
        return days[date.weekday()]