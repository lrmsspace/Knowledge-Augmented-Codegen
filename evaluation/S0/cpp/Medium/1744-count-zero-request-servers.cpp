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
public:
    vector<int> countServers(int n, vector<vector<int>>& logs, int x, vector<int>& queries) {
        sort(logs.begin(), logs.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] < b[1];
        });

        vector<pair<int, int>> queryWithIndex;
        for (int i = 0; i < queries.size(); ++i) {
            queryWithIndex.emplace_back(queries[i], i);
        }
        sort(queryWithIndex.begin(), queryWithIndex.end());

        vector<int> result(queries.size());
        unordered_map<int, int> serverRequestCount;
        int left = 0, right = 0;

        for (const auto& [queryTime, originalIndex] : queryWithIndex) {
            while (right < logs.size() && logs[right][1] <= queryTime) {
                serverRequestCount[logs[right][0]]++;
                right++;
            }
            while (left < logs.size() && logs[left][1] < queryTime - x) {
                serverRequestCount[logs[left][0]]--;
                if (serverRequestCount[logs[left][0]] == 0) {
                    serverRequestCount.erase(logs[left][0]);
                }
                left++;
            }
            result[originalIndex] = n - serverRequestCount.size();
        }

        return result;          
    }
};
