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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countServers(int n, int** logs, int logsSize, int* logsColSize, int x, int* queries, int queriesSize, int* returnSize) {
    // Create an array to store the last request time for each server
    int* lastRequestTime = (int*)calloc(n + 1, sizeof(int));
    
    // Update the last request time for each server based on logs
    for (int i = 0; i < logsSize; i++) {
        int serverId = logs[i][0];
        int time = logs[i][1];
        if (time > lastRequestTime[serverId]) {
            lastRequestTime[serverId] = time;
        }
    }
    
    // Prepare the result array
    int* result = (int*)malloc(queriesSize * sizeof(int));
    
    // For each query, count the number of servers with no requests in the given interval
    for (int i = 0; i < queriesSize; i++) {
        int queryTime = queries[i];
        int count = 0;
        
        for (int serverId = 1; serverId <= n; serverId++) {
            if (lastRequestTime[serverId] < queryTime - x) {
                count++;
            }
        }
        
        result[i] = count;
    }
    
    // Free the allocated memory for lastRequestTime
    free(lastRequestTime);
    
    // Set the return size
    *returnSize = queriesSize;
    
    return result;      
}
