// Source: https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/   |   Difficulty: Hard
//
// Problem Description:
// You have k servers numbered from 0 to k-1 that are being used to handle multiple requests simultaneously. Each server has infinite computational capacity but cannot handle more than one request at a time. The requests are assigned to servers according to a specific algorithm:
//
//
// 	The ith (0-indexed) request arrives.
// 	If all servers are busy, the request is dropped (not handled at all).
// 	If the (i % k)th server is available, assign the request to that server.
// 	Otherwise, assign the request to the next available server (wrapping around the list of servers and starting from 0 if necessary). For example, if the ith server is busy, try to assign the request to the (i+1)th server, then the (i+2)th server, and so on.
//
//
// You are given a strictly increasing array arrival of positive integers, where arrival[i] represents the arrival time of the ith request, and another array load, where load[i] represents the load of the ith request (the time it takes to complete). Your goal is to find the busiest server(s). A server is considered busiest if it handled the most number of requests successfully among all the servers.
//
// Return a list containing the IDs (0-indexed) of the busiest server(s). You may return the IDs in any order.
//
// Example:
// Input: k = 3, arrival = [1,2,3,4,5], load = [5,2,3,3,3] 
// Output: [1] 
// Explanation: 
// All of the servers start out available.
// The first 3 requests are handled by the first 3 servers in order.
// Request 3 comes in. Server 0 is busy, so it's assigned to the next available server, which is 1.
// Request 4 comes in. It cannot be handled since all servers are busy, so it is dropped.
// Servers 0 and 2 handled one request each, while server 1 handled two requests. Hence server 1 is the busiest server.
//
// Constraints:
// 1 <= k <= 105
// 	1 <= arrival.length, load.length <= 105
// 	arrival.length == load.length
// 	1 <= arrival[i], load[i] <= 109
// 	arrival is strictly increasing.
//

class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> serverLoad(k, 0);
        vector<int> requestCount(k, 0);
        set<int> availableServers;
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> busyServers; // (endTime, serverId)
        
        for (int i = 0; i < k; i++) {
            availableServers.insert(i);
        }
        
        for (int i = 0; i < arrival.size(); i++) {
            long long currentTime = arrival[i];
            int duration = load[i];
            
            // Free up servers that have completed their tasks
            while (!busyServers.empty() && busyServers.top().first <= currentTime) {
                int freedServer = busyServers.top().second;
                busyServers.pop();
                availableServers.insert(freedServer);
            }
            
            if (availableServers.empty()) {
                // All servers are busy, drop the request
                continue;
            }
            
            // Find the server to handle the request
            int preferredServer = i % k;
            auto it = availableServers.lower_bound(preferredServer);
            if (it == availableServers.end()) {
                it = availableServers.begin();
            }
            int assignedServer = *it;
            availableServers.erase(it);
            
            // Assign the request to the server
            serverLoad[assignedServer] += duration;
            requestCount[assignedServer]++;
            busyServers.push({currentTime + duration, assignedServer});
        }
        
        // Find the maximum number of requests handled
        int maxRequests = *max_element(requestCount.begin(), requestCount.end());
        vector<int> busiestServers;
        
        for (int i = 0; i < k; i++) {
            if (requestCount[i] == maxRequests) {
                busiestServers.push_back(i);
            }
        }
        
        return busiestServers;          
    }
};
