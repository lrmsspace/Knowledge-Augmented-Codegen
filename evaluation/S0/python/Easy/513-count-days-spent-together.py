# Source: https://leetcode.com/problems/count-days-spent-together/   |   Difficulty: Easy
#
# Problem Description:
# Alice and Bob are traveling to Rome for separate business meetings.
#
# You are given 4 strings arriveAlice, leaveAlice, arriveBob, and leaveBob. Alice will be in the city from the dates arriveAlice to leaveAlice (inclusive), while Bob will be in the city from the dates arriveBob to leaveBob (inclusive). Each will be a 5-character string in the format "MM-DD", corresponding to the month and day of the date.
#
# Return the total number of days that Alice and Bob are in Rome together.
#
# You can assume that all dates occur in the same calendar year, which is not a leap year. Note that the number of days per month can be represented as: [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31].
#
# Example:
# Input: arriveAlice = "08-15", leaveAlice = "08-18", arriveBob = "08-16", leaveBob = "08-19"
# Output: 3
# Explanation: Alice will be in Rome from August 15 to August 18. Bob will be in Rome from August 16 to August 19. They are both in Rome together on August 16th, 17th, and 18th, so the answer is 3.
#
# Constraints:
# All dates are provided in the format "MM-DD".
# 	Alice and Bob's arrival dates are earlier than or equal to their leaving dates.
# 	The given dates are valid dates of a non-leap year.
#

class Solution(object):
    def countDaysTogether(self, arriveAlice, leaveAlice, arriveBob, leaveBob):
        """
        :type arriveAlice: str
        :type leaveAlice: str
        :type arriveBob: str
        :type leaveBob: str
        :rtype: int
        """
        days_in_month = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
        
        def date_to_day_of_year(date):
            month, day = map(int, date.split('-'))
            return sum(days_in_month[:month - 1]) + day
        
        arriveAlice_day = date_to_day_of_year(arriveAlice)
        leaveAlice_day = date_to_day_of_year(leaveAlice)
        arriveBob_day = date_to_day_of_year(arriveBob)
        leaveBob_day = date_to_day_of_year(leaveBob)
        
        start_overlap = max(arriveAlice_day, arriveBob_day)
        end_overlap = min(leaveAlice_day, leaveBob_day)
        
        if start_overlap > end_overlap:
            return 0
        else:
            return end_overlap - start_overlap + 1