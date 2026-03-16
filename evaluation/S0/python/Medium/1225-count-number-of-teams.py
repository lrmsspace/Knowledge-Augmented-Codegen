# Source: https://leetcode.com/problems/count-number-of-teams/   |   Difficulty: Medium
#
# Problem Description:
# There are n soldiers standing in a line. Each soldier is assigned a unique rating value.
#
# You have to form a team of 3 soldiers amongst them under the following rules:
#
#
# 	Choose 3 soldiers with index (i, j, k) with rating (rating[i], rating[j], rating[k]).
# 	A team is valid if: (rating[i] < rating[j] < rating[k]) or (rating[i] > rating[j] > rating[k]) where (0 <= i < j < k < n).
#
#
# Return the number of teams you can form given the conditions. (soldiers can be part of multiple teams).
#
# Example:
# Input: rating = [2,5,3,4,1]
# Output: 3
# Explanation: We can form three teams given the conditions. (2,3,4), (5,4,1), (5,3,1).
#
# Constraints:
# n == rating.length
# 	3 <= n <= 1000
# 	1 <= rating[i] <= 105
# 	All the integers in rating are unique.
#

class Solution(object):
    def numTeams(self, rating):
        """
        :type rating: List[int]
        :rtype: int
        """
        n = len(rating)
        count = 0
        
        for j in range(n):
            less_left = sum(1 for i in range(j) if rating[i] < rating[j])
            greater_left = j - less_left
            less_right = sum(1 for k in range(j + 1, n) if rating[k] < rating[j])
            greater_right = (n - j - 1) - less_right
            
            count += less_left * greater_right + greater_left * less_right
        
        return count