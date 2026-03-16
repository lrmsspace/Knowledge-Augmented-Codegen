# Source: https://leetcode.com/problems/number-of-days-between-two-dates/   |   Difficulty: Easy
#
# Problem Description:
# Write a program to count the number of days between two dates.
#
# The two dates are given as strings, their format is YYYY-MM-DD as shown in the examples.
#
# Example:
# Input: date1 = "2019-06-29", date2 = "2019-06-30"
# Output: 1
#
# Constraints:
# The given dates are valid dates between the years 1971 and 2100.
#

class Solution(object):
    def daysBetweenDates(self, date1, date2):
        """
        :type date1: str
        :type date2: str
        :rtype: int
        """
        def is_leap_year(year):
            return year % 4 == 0 and (year % 100 != 0 or year % 400 == 0)

        def days_in_month(year, month):
            if month in [1, 3, 5, 7, 8, 10, 12]:
                return 31
            elif month in [4, 6, 9, 11]:
                return 30
            elif month == 2:
                return 29 if is_leap_year(year) else 28
            return 0

        def date_to_days(date):
            year, month, day = map(int, date.split('-'))
            total_days = day
            for y in range(1971, year):
                total_days += 366 if is_leap_year(y) else 365
            for m in range(1, month):
                total_days += days_in_month(year, m)
            return total_days

        days1 = date_to_days(date1)
        days2 = date_to_days(date2)
        return abs(days1 - days2)