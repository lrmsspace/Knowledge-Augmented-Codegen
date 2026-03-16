# Source: https://leetcode.com/problems/happy-students/   |   Difficulty: Medium
#
# Problem Description:
# You are given a 0-indexed integer array nums of length n where n is the total number of students in the class. The class teacher tries to select a group of students so that all the students remain happy.
#
# The ith student will become happy if one of these two conditions is met:
#
#
# 	The student is selected and the total number of selected students is strictly greater than nums[i].
# 	The student is not selected and the total number of selected students is strictly less than nums[i].
#
#
# Return the number of ways to select a group of students so that everyone remains happy.
#
# Example:
# Input: nums = [1,1]
# Output: 2
# Explanation: 
# The two possible ways are:
# The class teacher selects no student.
# The class teacher selects both students to form the group. 
# If the class teacher selects just one student to form a group then the both students will not be happy. Therefore, there are only two possible ways.
#
# Constraints:
# 1 <= nums.length <= 105
# 	0 <= nums[i] < nums.length
#

class Solution(object):
    def countWays(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """
        n = len(nums)
        nums.sort()
        result = 0
        
        for i in range(n + 1):
            # Count how many students have nums[j] < i
            less_count = 0
            for num in nums:
                if num < i:
                    less_count += 1
            
            # Check if the current selection size i makes all students happy
            if less_count == i:
                continue
            
            result += 1
        
        return result