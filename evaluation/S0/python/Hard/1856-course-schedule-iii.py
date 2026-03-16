# Source: https://leetcode.com/problems/course-schedule-iii/   |   Difficulty: Hard
#
# Problem Description:
# There are n different online courses numbered from 1 to n. You are given an array courses where courses[i] = [durationi, lastDayi] indicate that the ith course should be taken continuously for durationi days and must be finished before or on lastDayi.
#
# You will start on the 1st day and you cannot take two or more courses simultaneously.
#
# Return the maximum number of courses that you can take.
#
# Example:
# Input: courses = [[100,200],[200,1300],[1000,1250],[2000,3200]]
# Output: 3
# Explanation: 
# There are totally 4 courses, but you can take 3 courses at most:
# First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the 101st day.
# Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day. 
# Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day. 
# The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
#
# Constraints:
# 1 <= courses.length <= 104
# 	1 <= durationi, lastDayi <= 104
#

class Solution(object):
    def scheduleCourse(self, courses):
        """
        :type courses: List[List[int]]
        :rtype: int
        """
        import heapq

        # Sort courses by their end days
        courses.sort(key=lambda x: x[1])

        total_time = 0
        max_heap = []

        for duration, last_day in courses:
            # Add the current course duration to total time
            total_time += duration
            # Push the negative duration to simulate a max-heap
            heapq.heappush(max_heap, -duration)

            # If total time exceeds the last day of the current course
            if total_time > last_day:
                # Remove the course with the longest duration
                longest_duration = -heapq.heappop(max_heap)
                total_time -= longest_duration

        # The number of courses in the max-heap is the maximum number of courses that can be taken
        return len(max_heap)