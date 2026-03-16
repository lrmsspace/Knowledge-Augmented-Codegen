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

/**
 * @param {number[][]} routes
 * @param {number} source
 * @param {number} target
 * @return {number}
 */
var numBusesToDestination = function(routes, source, target) {
    if (source === target) return 0;
    const stopToBuses = new Map();
    for (let i = 0; i < routes.length; i++) {
        for (const stop of routes[i]) {
            if (!stopToBuses.has(stop)) stopToBuses.set(stop, []);
            stopToBuses.get(stop).push(i);
        }
    }
    const visitedBuses = new Set();
    const queue = [];
    for (const bus of stopToBuses.get(source) || []) {
        visitedBuses.add(bus);
        queue.push(bus);
    }
    let busesTaken = 1;
    while (queue.length > 0) {
        const size = queue.length;
        for (let i = 0; i < size; i++) {
            const bus = queue.shift();
            for (const stop of routes[bus]) {
                if (stop === target) return busesTaken;
                for (const nextBus of stopToBuses.get(stop) || []) {
                    if (!visitedBuses.has(nextBus)) {
                        visitedBuses.add(nextBus);
                        queue.push(nextBus);
                    }
                }
            }
        }
        busesTaken++;
    }
        
    return -1;
};
