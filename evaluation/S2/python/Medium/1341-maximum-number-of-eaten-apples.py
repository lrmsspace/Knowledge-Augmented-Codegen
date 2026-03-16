# Source: https://leetcode.com/problems/maximum-number-of-eaten-apples/   |   Difficulty: Medium
#
# Problem Description:
# There is a special kind of apple tree that grows apples every day for n days. On the ith day, the tree grows apples[i] apples that will rot after days[i] days, that is on day i + days[i] the apples will be rotten and cannot be eaten. On some days, the apple tree does not grow any apples, which are denoted by apples[i] == 0 and days[i] == 0.
#
# You decided to eat at most one apple a day (to keep the doctors away). Note that you can keep eating after the first n days.
#
# Given two integer arrays days and apples of length n, return the maximum number of apples you can eat.
#
# Example:
# Input: apples = [1,2,3,5,2], days = [3,2,1,4,2]
# Output: 7
# Explanation: You can eat 7 apples:
# - On the first day, you eat an apple that grew on the first day.
# - On the second day, you eat an apple that grew on the second day.
# - On the third day, you eat an apple that grew on the second day. After this day, the apples that grew on the third day rot.
# - On the fourth to the seventh days, you eat apples that grew on the fourth day.
#
# Constraints:
# n == apples.length == days.length
# 	1 <= n <= 2 * 104
# 	0 <= apples[i], days[i] <= 2 * 104
# 	days[i] = 0 if and only if apples[i] = 0.
#
# Helpful references (internal KB):
# - N/A
#
# Notes:
# - Keep the given function signature unchanged.
# - Use only the Python standard library; no third-party packages.
# - Do not change input/output formats or return value semantics as defined by the template/problem.
# - Conformance: use features compatible with LeetCode’s Python3 runtime; do NOT rely on undefined/implementation-specific behavior.
# - If you introduce any helper functions/classes, include their full implementations in this file; no hidden helpers.

class Solution(object):
    def eatenApples(self, apples, days):
        """
        :type apples: List[int]
        :type days: List[int]
        :rtype: int
        """
        import heapq
        heap = []
        total_eaten = 0
        day = 0
        
        while day < len(apples) or heap:
            # Add new apples that grow on the current day
            if day < len(apples) and apples[day] > 0:
                heapq.heappush(heap, (day + days[day], apples[day]))
            
            # Remove rotten apples
            while heap and heap[0][0] <= day:
                heapq.heappop(heap)
            
            # Eat an apple if available
            if heap:
                total_eaten += 1
                next_rotten_day, count = heapq.heappop(heap)
                if count > 1:
                    heapq.heappush(heap, (next_rotten_day, count - 1))
            
            day += 1
        
        return total_eaten