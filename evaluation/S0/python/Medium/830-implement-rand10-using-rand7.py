# Source: https://leetcode.com/problems/implement-rand10-using-rand7/   |   Difficulty: Medium
#
# Problem Description:
# Given the API rand7() that generates a uniform random integer in the range [1, 7], write a function rand10() that generates a uniform random integer in the range [1, 10]. You can only call the API rand7(), and you shouldn't call any other API. Please do not use a language's built-in random API.
#
# Each test case will have one internal argument n, the number of times that your implemented function rand10() will be called while testing. Note that this is not an argument passed to rand10().
#
# Example:
# Input: n = 1
# Output: [2]
#
# Constraints:
# 1 <= n <= 105
#
#
#  
# Follow up:
#
#
# 	What is the expected value for the number of calls to rand7() function?
# 	Could you minimize the number of calls to rand7()?
#

# The rand7() API is already defined for you.
# def rand7():
# @return a random integer in the range 1 to 7

class Solution(object):
    def rand10(self):
        """
        :rtype: int
        """
        while True:
            row = rand7()
            col = rand7()
            idx = (row - 1) * 7 + col  # This gives us a uniform integer from 1 to 49
            if idx <= 40:  # We can use numbers 1 to 40 to get a uniform distribution for 1 to 10
                return (idx - 1) % 10 + 1
            # If idx is greater than 40, we discard and try again