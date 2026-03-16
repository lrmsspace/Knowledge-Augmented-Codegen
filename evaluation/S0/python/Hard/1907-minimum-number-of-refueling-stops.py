# Source: https://leetcode.com/problems/minimum-number-of-refueling-stops/   |   Difficulty: Hard
#
# Problem Description:
# A car travels from a starting position to a destination which is target miles east of the starting position.
#
# There are gas stations along the way. The gas stations are represented as an array stations where stations[i] = [positioni, fueli] indicates that the ith gas station is positioni miles east of the starting position and has fueli liters of gas.
#
# The car starts with an infinite tank of gas, which initially has startFuel liters of fuel in it. It uses one liter of gas per one mile that it drives. When the car reaches a gas station, it may stop and refuel, transferring all the gas from the station into the car.
#
# Return the minimum number of refueling stops the car must make in order to reach its destination. If it cannot reach the destination, return -1.
#
# Note that if the car reaches a gas station with 0 fuel left, the car can still refuel there. If the car reaches the destination with 0 fuel left, it is still considered to have arrived.
#
# Example:
# Input: target = 1, startFuel = 1, stations = []
# Output: 0
# Explanation: We can reach the target without refueling.
#
# Constraints:
# 1 <= target, startFuel <= 109
# 	0 <= stations.length <= 500
# 	1 <= positioni < positioni+1 < target
# 	1 <= fueli < 109
#

class Solution(object):
    def minRefuelStops(self, target, startFuel, stations):
        """
        :type target: int
        :type startFuel: int
        :type stations: List[List[int]]
        :rtype: int
        """
        import heapq

        # Max-heap to store available fuel at stations we've passed
        max_heap = []
        stations.append([target, 0])  # Add target as the last "station"
        fuel = startFuel
        prev_position = 0
        refuels = 0

        for position, station_fuel in stations:
            fuel -= (position - prev_position)

            # Refuel from the stations we've passed if we don't have enough fuel
            while fuel < 0 and max_heap:
                fuel += -heapq.heappop(max_heap)  # Pop the largest fuel available
                refuels += 1

            if fuel < 0:
                return -1  # Can't reach this station

            heapq.heappush(max_heap, -station_fuel)  # Push current station's fuel into max-heap
            prev_position = position

        return refuels