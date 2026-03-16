# Source: https://leetcode.com/problems/number-of-flowers-in-full-bloom/   |   Difficulty: Hard
#
# Problem Description:
# You are given a 0-indexed 2D integer array flowers, where flowers[i] = [starti, endi] means the ith flower will be in full bloom from starti to endi (inclusive). You are also given a 0-indexed integer array people of size n, where people[i] is the time that the ith person will arrive to see the flowers.
#
# Return an integer array answer of size n, where answer[i] is the number of flowers that are in full bloom when the ith person arrives.
#
# Example:
# Input: flowers = [[1,6],[3,7],[9,12],[4,13]], people = [2,3,7,11]
# Output: [1,2,2,2]
# Explanation: The figure above shows the times when the flowers are in full bloom and when the people arrive.
# For each person, we return the number of flowers in full bloom during their arrival.
#
# Constraints:
# 1 <= flowers.length <= 5 * 104
# 	flowers[i].length == 2
# 	1 <= starti <= endi <= 109
# 	1 <= people.length <= 5 * 104
# 	1 <= people[i] <= 109
#

class Solution(object):
    def fullBloomFlowers(self, flowers, people):
        """
        :type flowers: List[List[int]]
        :type people: List[int]
        :rtype: List[int]
        """
        events = []
        for start, end in flowers:
            events.append((start, 1))   # Flower starts blooming
            events.append((end + 1, -1)) # Flower stops blooming

        for i, time in enumerate(people):
            events.append((time, 0, i))  # Person arrives

        events.sort()
        
        blooming = 0
        result = [0] * len(people)

        for event in events:
            if event[1] == 1:  # Flower starts blooming
                blooming += 1
            elif event[1] == -1:  # Flower stops blooming
                blooming -= 1
            else:  # Person arrives
                result[event[2]] = blooming

        return result