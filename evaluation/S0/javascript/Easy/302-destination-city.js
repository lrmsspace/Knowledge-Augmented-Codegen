// Source: https://leetcode.com/problems/destination-city/   |   Difficulty: Easy
//
// Problem Description:
// You are given the array paths, where paths[i] = [cityAi, cityBi] means there exists a direct path going from cityAi to cityBi. Return the destination city, that is, the city without any path outgoing to another city.
//
// It is guaranteed that the graph of paths forms a line without any loop, therefore, there will be exactly one destination city.
//
// Example:
// Input: paths = [["London","New York"],["New York","Lima"],["Lima","Sao Paulo"]]
// Output: "Sao Paulo" 
// Explanation: Starting at "London" city you will reach "Sao Paulo" city which is the destination city. Your trip consist of: "London" -> "New York" -> "Lima" -> "Sao Paulo".
//
// Constraints:
// 1 <= paths.length <= 100
// 	paths[i].length == 2
// 	1 <= cityAi.length, cityBi.length <= 10
// 	cityAi != cityBi
// 	All strings consist of lowercase and uppercase English letters and the space character.
//

/**
 * @param {string[][]} paths
 * @return {string}
 */
var destCity = function(paths) {
    const destinations = new Set();
    const starts = new Set();
    for (const [start, destination] of paths) {
        starts.add(start);
        destinations.add(destination);
    }
    for (const city of destinations) {
        if (!starts.has(city)) {
            return city;
        }
    }
};