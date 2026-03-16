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
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;
        
        unordered_map<int, vector<int>> stopToBuses;
        int n = routes.size();
        
        for (int bus = 0; bus < n; bus++) {
            for (int stop : routes[bus]) {
                stopToBuses[stop].push_back(bus);
            }
        }
        
        queue<int> q;
        vector<bool> visitedBus(n, false);
        unordered_set<int> visitedStop;
        
        q.push(source);
        visitedStop.insert(source);
        
        int busesTaken = 0;
        
        while (!q.empty()) {
            int size = q.size();
            busesTaken++;
            
            for (int i = 0; i < size; i++) {
                int currStop = q.front();
                q.pop();
                
                for (int bus : stopToBuses[currStop]) {
                    if (visitedBus[bus]) continue;
                    visitedBus[bus] = true;
                    
                    for (int nextStop : routes[bus]) {
                        if (nextStop == target) return busesTaken;
                        if (visitedStop.find(nextStop) == visitedStop.end()) {
                            visitedStop.insert(nextStop);
                            q.push(nextStop);
                        }
                    }
                }
            }
        }
        
        return -1;          
    }
};
