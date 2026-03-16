# Source: https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/   |   Difficulty: Hard
#
# Problem Description:
# You have k servers numbered from 0 to k-1 that are being used to handle multiple requests simultaneously. Each server has infinite computational capacity but cannot handle more than one request at a time. The requests are assigned to servers according to a specific algorithm:
#
#
# 	The ith (0-indexed) request arrives.
# 	If all servers are busy, the request is dropped (not handled at all).
# 	If the (i % k)th server is available, assign the request to that server.
# 	Otherwise, assign the request to the next available server (wrapping around the list of servers and starting from 0 if necessary). For example, if the ith server is busy, try to assign the request to the (i+1)th server, then the (i+2)th server, and so on.
#
#
# You are given a strictly increasing array arrival of positive integers, where arrival[i] represents the arrival time of the ith request, and another array load, where load[i] represents the load of the ith request (the time it takes to complete). Your goal is to find the busiest server(s). A server is considered busiest if it handled the most number of requests successfully among all the servers.
#
# Return a list containing the IDs (0-indexed) of the busiest server(s). You may return the IDs in any order.
#
# Example:
# Input: k = 3, arrival = [1,2,3,4,5], load = [5,2,3,3,3] 
# Output: [1] 
# Explanation: 
# All of the servers start out available.
# The first 3 requests are handled by the first 3 servers in order.
# Request 3 comes in. Server 0 is busy, so it's assigned to the next available server, which is 1.
# Request 4 comes in. It cannot be handled since all servers are busy, so it is dropped.
# Servers 0 and 2 handled one request each, while server 1 handled two requests. Hence server 1 is the busiest server.
#
# Constraints:
# 1 <= k <= 105
# 	1 <= arrival.length, load.length <= 105
# 	arrival.length == load.length
# 	1 <= arrival[i], load[i] <= 109
# 	arrival is strictly increasing.
#

class Solution(object):
    def busiestServers(self, k, arrival, load):
        """
        :type k: int
        :type arrival: List[int]
        :type load: List[int]
        :rtype: List[int]
        """
        import heapq
        from sortedcontainers import SortedList

        free_servers = SortedList(range(k))
        busy_servers = []
        request_count = [0] * k

        for i, (start, duration) in enumerate(zip(arrival, load)):
            while busy_servers and busy_servers[0][0] <= start:
                _, server_id = heapq.heappop(busy_servers)
                free_servers.add(server_id)

            if not free_servers:
                continue

            index = free_servers.bisect_left(i % k)
            if index == len(free_servers):
                index = 0

            server_id = free_servers[index]
            free_servers.remove(server_id)
            heapq.heappush(busy_servers, (start + duration, server_id))
            request_count[server_id] += 1

        max_requests = max(request_count)
        return [i for i, count in enumerate(request_count) if count == max_requests]