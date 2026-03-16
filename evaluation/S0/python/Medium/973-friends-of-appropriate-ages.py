# Source: https://leetcode.com/problems/friends-of-appropriate-ages/   |   Difficulty: Medium
#
# Problem Description:
# There are n persons on a social media website. You are given an integer array ages where ages[i] is the age of the ith person.
#
# A Person x will not send a friend request to a person y (x != y) if any of the following conditions is true:
#
#
# 	age[y] <= 0.5 * age[x] + 7
# 	age[y] > age[x]
# 	age[y] > 100 && age[x] < 100
#
#
# Otherwise, x will send a friend request to y.
#
# Note that if x sends a request to y, y will not necessarily send a request to x. Also, a person will not send a friend request to themself.
#
# Return the total number of friend requests made.
#
# Example:
# Input: ages = [16,16]
# Output: 2
# Explanation: 2 people friend request each other.
#
# Constraints:
# n == ages.length
# 	1 <= n <= 2 * 104
# 	1 <= ages[i] <= 120
#

class Solution(object):
    def numFriendRequests(self, ages):
        """
        :type ages: List[int]
        :rtype: int
        """
        count = [0] * 121
        for age in ages:
            count[age] += 1

        total_requests = 0
        for age_a in range(15, 121):
            for age_b in range(15, 121):
                if age_b <= 0.5 * age_a + 7:
                    continue
                if age_b > age_a:
                    continue
                if age_b > 100 and age_a < 100:
                    continue

                if age_a == age_b:
                    total_requests += count[age_a] * (count[age_a] - 1)
                else:
                    total_requests += count[age_a] * count[age_b]

        return total_requests