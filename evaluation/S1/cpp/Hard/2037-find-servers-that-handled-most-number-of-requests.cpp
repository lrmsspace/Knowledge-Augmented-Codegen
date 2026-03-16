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
// Helpful references (internal KB):
// - Priority Queues (array, heap, heap-select)
//   • When to use: Use when you need to efficiently retrieve the highest or lowest priority item from a dynamic collection. It's ideal for scenarios requiring frequent insertions and extractions of extreme values without full sorting.
//   • Idea: A Priority Queue is an abstract data type that provides efficient retrieval of the maximum or minimum element. It is typically implemented using a binary heap, which stores elements in an array representing a complete binary tree, maintaining the heap-ordered property for O(log N) insertion and deletion.
//   • Invariants: For a max-heap, every parent node's key is greater than or equal to its children's keys.; The heap structure is always a complete binary tree, represented contiguously in an array.
//   • Tips: Represent the complete binary tree using an array, often 1-indexed for simpler parent/child calculations.; Use 'swim' (bottom-up reheapify) after insertion to restore heap order.
//   • Pitfalls: Forgetting to handle 0-indexed vs 1-indexed array representations correctly (parent/child formulas differ).; Violating the heap-ordered property during updates or custom operations.
// - Scheduling jobs on two machines (array, number, simulation, enumeration)
//   • When to use: Use when determining the optimal sequence of jobs to minimize the total completion time (makespan) on two machines, with a fixed processing order (machine 1 then machine 2) for all jobs.
//   • Idea: This problem involves ordering N jobs, each with two processing times (one for each machine), to minimize the overall makespan. Johnson's rule provides an optimal greedy solution for this specific two-machine flow shop problem in O(N log N) or O(N) time.
//   • Invariants: All jobs processed so far maintain the optimal relative order determined by Johnson's rule.; The current makespan is the minimum possible for the jobs already scheduled.
//   • Tips: Sort jobs based on Johnson's rule criteria: jobs with min(a_i, b_i).; Prioritize jobs with shorter machine 1 times or longer machine 2 times for early scheduling.
//   • Pitfalls: Applying Johnson's rule to problems with more than two machines, where it is not optimal.; Incorrectly sorting jobs within the two partitioned sets.
// - Minimum stack / Minimum queue (queue, stack, simulation)
//   • When to use: Use when needing to efficiently query the minimum element of a stack or queue in O(1) average time. Also applicable for finding minimums in all fixed-length subarrays using a sliding window.
//   • Idea: This technique augments a stack or queue to support O(1) average time retrieval of its minimum element, typically by storing minimums alongside data or using auxiliary structures. It achieves amortized constant time for all operations.
//   • Invariants: For a minimum stack, the auxiliary minimum stack's top element is always the minimum of all elements currently in the main stack.; For a minimum queue implemented with two stacks, the output stack is only refilled from the input stack when the output stack becomes empty.
//   • Tips: For a minimum stack, use an auxiliary stack to store minimums encountered so far.; Only push to the auxiliary minimum stack if the new element is less than or equal to its current top.
//   • Pitfalls: Forgetting to pop from the auxiliary minimum stack when the main stack's top is removed.; Incorrectly handling the transfer logic between the two stacks for a minimum queue.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        using pii = pair<int, int>;
        struct cmp {
            bool operator()(const pii& a, const pii& b) const {
                return a.first > b.first || (a.first == b.first && a.second > b.second);
            }
        };
        
        priority_queue<pii, vector<pii>, cmp> busy; // (endTime, serverId)
        set<int> available;
        for (int i = 0; i < k; ++i) {
            available.insert(i);
        }
        
        vector<int> requestCount(k, 0);
        int maxRequests = 0;
        
        for (int i = 0; i < arrival.size(); ++i) {
            int currTime = arrival[i];
            int duration = load[i];
            
            // Free up servers that have completed their tasks
            while (!busy.empty() && busy.top().first <= currTime) {
                int freedServerId = busy.top().second;
                busy.pop();
                available.insert(freedServerId);
            }
            
            if (available.empty()) {
                // All servers are busy, drop the request
                continue;
            }
            
            // Find the server to assign the request
            int serverId = i % k;
            auto it = available.lower_bound(serverId);
            if (it == available.end()) {
                it = available.begin(); // wrap around
            }
            serverId = *it;
            available.erase(it);
            
            // Assign the request to the server
            busy.emplace(currTime + duration, serverId);
            requestCount[serverId]++;
            maxRequests = max(maxRequests, requestCount[serverId]);
        }
        
        vector<int> busiestServers;
        for (int i = 0; i < k; ++i) {
            if (requestCount[i] == maxRequests) {
                busiestServers.push_back(i);
            }
        }
        
        return busiestServers;          
    }
};
