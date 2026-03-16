# Source: https://leetcode.com/problems/bus-routes/   |   Difficulty: Hard
#
# Problem Description:
# You are given an array routes representing bus routes where routes[i] is a bus route that the ith bus repeats forever.
#
#
# 	For example, if routes[0] = [1, 5, 7], this means that the 0th bus travels in the sequence 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... forever.
#
#
# You will start at the bus stop source (You are not on any bus initially), and you want to go to the bus stop target. You can travel between bus stops by buses only.
#
# Return the least number of buses you must take to travel from source to target. Return -1 if it is not possible.
#
# Example:
# Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
# Output: 2
# Explanation: The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
#
# Constraints:
# 1 <= routes.length <= 500.
# 	1 <= routes[i].length <= 105
# 	All the values of routes[i] are unique.
# 	sum(routes[i].length) <= 105
# 	0 <= routes[i][j] < 106
# 	0 <= source, target < 106
#

class Solution(object):
    def numBusesToDestination(self, routes, source, target):
        """
        :type routes: List[List[int]]
        :type source: int
        :type target: int
        :rtype: int
        """
        if source == target:
            return 0

        from collections import defaultdict, deque

        stop_to_buses = defaultdict(set)
        for bus_id, stops in enumerate(routes):
            for stop in stops:
                stop_to_buses[stop].add(bus_id)

        visited_stops = set()
        visited_buses = set()
        queue = deque([(source, 0)])  # (current_stop, buses_taken)

        while queue:
            current_stop, buses_taken = queue.popleft()

            for bus_id in stop_to_buses[current_stop]:
                if bus_id in visited_buses:
                    continue
                visited_buses.add(bus_id)

                for next_stop in routes[bus_id]:
                    if next_stop == target:
                        return buses_taken + 1
                    if next_stop not in visited_stops:
                        visited_stops.add(next_stop)
                        queue.append((next_stop, buses_taken + 1))

        return -1