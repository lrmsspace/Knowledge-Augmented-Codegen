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
// Helpful references (internal KB):
// - N/A
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;

        unordered_map<int, vector<int>> stop_to_buses;
        for (int i = 0; i < routes.size(); ++i) {
            for (int stop : routes[i]) {
                stop_to_buses[stop].push_back(i);
            }
        }

        queue<pair<int, int>> q; // {current_stop, buses_taken}
        unordered_set<int> visited_stops;
        unordered_set<int> visited_buses;

        q.push({source, 0});
        visited_stops.insert(source);

        while (!q.empty()) {
            auto [current_stop, buses_taken] = q.front();
            q.pop();

            for (int bus : stop_to_buses[current_stop]) {
                if (visited_buses.count(bus)) continue;
                visited_buses.insert(bus);

                for (int next_stop : routes[bus]) {
                    if (next_stop == target) return buses_taken + 1;
                    if (!visited_stops.count(next_stop)) {
                        visited_stops.insert(next_stop);
                        q.push({next_stop, buses_taken + 1});
                    }
                }
            }
        }

        return -1;          
    }
};
