// Source: https://leetcode.com/problems/count-zero-request-servers/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer n denoting the total number of servers and a 2D 0-indexed integer array logs, where logs[i] = [server_id, time] denotes that the server with id server_id received a request at time time.
//
// You are also given an integer x and a 0-indexed integer array queries.
//
// Return a 0-indexed integer array arr of length queries.length where arr[i] represents the number of servers that did not receive any requests during the time interval [queries[i] - x, queries[i]].
//
// Note that the time intervals are inclusive.
//
// Example:
// Input: n = 3, logs = [[1,3],[2,6],[1,5]], x = 5, queries = [10,11]
// Output: [1,2]
// Explanation: 
// For queries[0]: The servers with ids 1 and 2 get requests in the duration of [5, 10]. Hence, only server 3 gets zero requests.
// For queries[1]: Only the server with id 2 gets a request in duration of [6,11]. Hence, the servers with ids 1 and 3 are the only servers that do not receive any requests during that time period.
//
// Constraints:
// 1 <= n <= 105
// 	1 <= logs.length <= 105
// 	1 <= queries.length <= 105
// 	logs[i].length == 2
// 	1 <= logs[i][0] <= n
// 	1 <= logs[i][1] <= 106
// 	1 <= x <= 105
// 	x < queries[i] <= 106
//

class Solution {
    public int[] countServers(int n, int[][] logs, int x, int[] queries) {
        Arrays.sort(logs, (a, b) -> Integer.compare(a[1], b[1]));
        int m = queries.length;
        int[] result = new int[m];
        Integer[] queryIndices = new Integer[m];
        for (int i = 0; i < m; i++) {
            queryIndices[i] = i;
        }
        Arrays.sort(queryIndices, (a, b) -> Integer.compare(queries[a], queries[b]));

        Map<Integer, Integer> serverRequestCount = new HashMap<>();
        int left = 0;
        int right = 0;

        for (int index : queryIndices) {
            int queryTime = queries[index];
            int startTime = queryTime - x;

            while (right < logs.length && logs[right][1] <= queryTime) {
                serverRequestCount.put(logs[right][0], serverRequestCount.getOrDefault(logs[right][0], 0) + 1);
                right++;
            }

            while (left < logs.length && logs[left][1] < startTime) {
                int serverId = logs[left][0];
                serverRequestCount.put(serverId, serverRequestCount.get(serverId) - 1);
                if (serverRequestCount.get(serverId) == 0) {
                    serverRequestCount.remove(serverId);
                }
                left++;
            }

            result[index] = n - serverRequestCount.size();
        }

        return result;          
    }
}
