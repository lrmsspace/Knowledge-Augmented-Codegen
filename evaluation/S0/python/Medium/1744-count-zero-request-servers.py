# Source: https://leetcode.com/problems/count-zero-request-servers/   |   Difficulty: Medium
#
# Problem Description:
# You are given an integer n denoting the total number of servers and a 2D 0-indexed integer array logs, where logs[i] = [server_id, time] denotes that the server with id server_id received a request at time time.
#
# You are also given an integer x and a 0-indexed integer array queries.
#
# Return a 0-indexed integer array arr of length queries.length where arr[i] represents the number of servers that did not receive any requests during the time interval [queries[i] - x, queries[i]].
#
# Note that the time intervals are inclusive.
#
# Example:
# Input: n = 3, logs = [[1,3],[2,6],[1,5]], x = 5, queries = [10,11]
# Output: [1,2]
# Explanation: 
# For queries[0]: The servers with ids 1 and 2 get requests in the duration of [5, 10]. Hence, only server 3 gets zero requests.
# For queries[1]: Only the server with id 2 gets a request in duration of [6,11]. Hence, the servers with ids 1 and 3 are the only servers that do not receive any requests during that time period.
#
# Constraints:
# 1 <= n <= 105
# 	1 <= logs.length <= 105
# 	1 <= queries.length <= 105
# 	logs[i].length == 2
# 	1 <= logs[i][0] <= n
# 	1 <= logs[i][1] <= 106
# 	1 <= x <= 105
# 	x < queries[i] <= 106
#

class Solution(object):
    def countServers(self, n, logs, x, queries):
        """
        :type n: int
        :type logs: List[List[int]]
        :type x: int
        :type queries: List[int]
        :rtype: List[int]
        """
        from collections import defaultdict
        import bisect

        log_map = defaultdict(list)
        for server_id, time in logs:
            log_map[server_id].append(time)

        for server_id in log_map:
            log_map[server_id].sort()

        result = []
        for query in queries:
            count = 0
            start_time = query - x
            for server_id in range(1, n + 1):
                if server_id not in log_map:
                    count += 1
                    continue
                times = log_map[server_id]
                left_index = bisect.bisect_left(times, start_time)
                right_index = bisect.bisect_right(times, query)
                if left_index == right_index:
                    count += 1
            result.append(count)

        return result