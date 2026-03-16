# Source: https://leetcode.com/problems/watering-plants-ii/   |   Difficulty: Medium
#
# Problem Description:
# Alice and Bob want to water n plants in their garden. The plants are arranged in a row and are labeled from 0 to n - 1 from left to right where the ith plant is located at x = i.
#
# Each plant needs a specific amount of water. Alice and Bob have a watering can each, initially full. They water the plants in the following way:
#
#
# 	Alice waters the plants in order from left to right, starting from the 0th plant. Bob waters the plants in order from right to left, starting from the (n - 1)th plant. They begin watering the plants simultaneously.
# 	It takes the same amount of time to water each plant regardless of how much water it needs.
# 	Alice/Bob must water the plant if they have enough in their can to fully water it. Otherwise, they first refill their can (instantaneously) then water the plant.
# 	In case both Alice and Bob reach the same plant, the one with more water currently in his/her watering can should water this plant. If they have the same amount of water, then Alice should water this plant.
#
#
# Given a 0-indexed integer array plants of n integers, where plants[i] is the amount of water the ith plant needs, and two integers capacityA and capacityB representing the capacities of Alice's and Bob's watering cans respectively, return the number of times they have to refill to water all the plants.
#
# Example:
# Input: plants = [2,2,3,3], capacityA = 5, capacityB = 5
# Output: 1
# Explanation:
# - Initially, Alice and Bob have 5 units of water each in their watering cans.
# - Alice waters plant 0, Bob waters plant 3.
# - Alice and Bob now have 3 units and 2 units of water respectively.
# - Alice has enough water for plant 1, so she waters it. Bob does not have enough water for plant 2, so he refills his can then waters it.
# So, the total number of times they have to refill to water all the plants is 0 + 0 + 1 + 0 = 1.
#
# Constraints:
# n == plants.length
# 	1 <= n <= 105
# 	1 <= plants[i] <= 106
# 	max(plants[i]) <= capacityA, capacityB <= 109
#

class Solution(object):
    def minimumRefill(self, plants, capacityA, capacityB):
        """
        :type plants: List[int]
        :type capacityA: int
        :type capacityB: int
        :rtype: int
        """
        n = len(plants)
        left, right = 0, n - 1
        refill_count = 0
        currA, currB = capacityA, capacityB
        
        while left < right:
            if currA < plants[left]:
                refill_count += 1
                currA = capacityA
            currA -= plants[left]
            left += 1
            
            if currB < plants[right]:
                refill_count += 1
                currB = capacityB
            currB -= plants[right]
            right -= 1
        
        if left == right:
            if currA >= currB:
                if currA < plants[left]:
                    refill_count += 1
            else:
                if currB < plants[right]:
                    refill_count += 1
        
        return refill_count