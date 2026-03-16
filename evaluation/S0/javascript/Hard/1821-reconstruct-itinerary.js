// Source: https://leetcode.com/problems/reconstruct-itinerary/   |   Difficulty: Hard
//
// Problem Description:
// You are given a list of airline tickets where tickets[i] = [fromi, toi] represent the departure and the arrival airports of one flight. Reconstruct the itinerary in order and return it.
//
// All of the tickets belong to a man who departs from "JFK", thus, the itinerary must begin with "JFK". If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string.
//
//
// 	For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
//
//
// You may assume all tickets form at least one valid itinerary. You must use all the tickets once and only once.
//
// Example:
// Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
// Output: ["JFK","MUC","LHR","SFO","SJC"]
//
// Constraints:
// 1 <= tickets.length <= 300
// 	tickets[i].length == 2
// 	fromi.length == 3
// 	toi.length == 3
// 	fromi and toi consist of uppercase English letters.
// 	fromi != toi
//

/**
 * @param {string[][]} tickets
 * @return {string[]}
 */
var findItinerary = function(tickets) {

        const graph = {};
    for (const [from, to] of tickets) {
        if (!graph[from]) {
            graph[from] = [];
        }
        graph[from].push(to);
    }
    for (const from in graph) {
        graph[from].sort();
    }
    const itinerary = [];
    function dfs(airport) {
        while (graph[airport] && graph[airport].length > 0) {
            const nextAirport = graph[airport].shift();
            dfs(nextAirport);
        }
        itinerary.push(airport);
    }
    dfs("JFK");
    return itinerary.reverse(); 
    
};
