// Source: https://leetcode.com/problems/bus-routes/   |   Difficulty: Hard
//
// Problem Description:
// You are given an array routes representing bus routes where routes[i] is a bus route that the ith bus repeats forever.
//
//
// 	For example, if routes[0] = [1, 5, 7], this means that the 0th bus travels in the sequence 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... forever.
//
//
// You will start at the bus stop source (You are not on any bus initially), and you want to go to the bus stop target. You can travel between bus stops by buses only.
//
// Return the least number of buses you must take to travel from source to target. Return -1 if it is not possible.
//
// Example:
// Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
// Output: 2
// Explanation: The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.
//
// Constraints:
// 1 <= routes.length <= 500.
// 	1 <= routes[i].length <= 105
// 	All the values of routes[i] are unique.
// 	sum(routes[i].length) <= 105
// 	0 <= routes[i][j] < 106
// 	0 <= source, target < 106
//

class Solution {
    public int numBusesToDestination(int[][] routes, int source, int target) {
        if (source == target) return 0;

        Map<Integer, List<Integer>> stopToBuses = new HashMap<>();
        for (int bus = 0; bus < routes.length; bus++) {
            for (int stop : routes[bus]) {
                stopToBuses.computeIfAbsent(stop, k -> new ArrayList<>()).add(bus);
            }
        }

        Queue<Integer> queue = new LinkedList<>();
        Set<Integer> visitedBuses = new HashSet<>();
        Set<Integer> visitedStops = new HashSet<>();
        queue.offer(source);
        visitedStops.add(source);
        int busesTaken = 0;

        while (!queue.isEmpty()) {
            int size = queue.size();
            busesTaken++;
            for (int i = 0; i < size; i++) {
                int currentStop = queue.poll();
                List<Integer> busesAtStop = stopToBuses.getOrDefault(currentStop, new ArrayList<>());

                for (int bus : busesAtStop) {
                    if (visitedBuses.contains(bus)) continue;
                    visitedBuses.add(bus);

                    for (int nextStop : routes[bus]) {
                        if (nextStop == target) return busesTaken;
                        if (!visitedStops.contains(nextStop)) {
                            visitedStops.add(nextStop);
                            queue.offer(nextStop);
                        }
                    }
                }
            }
        }

        return -1;          
    }
}
