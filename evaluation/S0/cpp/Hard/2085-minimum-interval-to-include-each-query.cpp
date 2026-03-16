// Source: https://leetcode.com/problems/minimum-interval-to-include-each-query/   |   Difficulty: Hard
//
// Problem Description:
// You are given a 2D integer array intervals, where intervals[i] = [lefti, righti] describes the ith interval starting at lefti and ending at righti (inclusive). The size of an interval is defined as the number of integers it contains, or more formally righti - lefti + 1.
//
// You are also given an integer array queries. The answer to the jth query is the size of the smallest interval i such that lefti <= queries[j] <= righti. If no such interval exists, the answer is -1.
//
// Return an array containing the answers to the queries.
//
// Example:
// Input: intervals = [[1,4],[2,4],[3,6],[4,4]], queries = [2,3,4,5]
// Output: [3,3,1,4]
// Explanation: The queries are processed as follows:
// - Query = 2: The interval [2,4] is the smallest interval containing 2. The answer is 4 - 2 + 1 = 3.
// - Query = 3: The interval [2,4] is the smallest interval containing 3. The answer is 4 - 2 + 1 = 3.
// - Query = 4: The interval [4,4] is the smallest interval containing 4. The answer is 4 - 4 + 1 = 1.
// - Query = 5: The interval [3,6] is the smallest interval containing 5. The answer is 6 - 3 + 1 = 4.
//
// Constraints:
// 1 <= intervals.length <= 105
// 	1 <= queries.length <= 105
// 	intervals[i].length == 2
// 	1 <= lefti <= righti <= 107
// 	1 <= queries[j] <= 107
//

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        int n = intervals.size();
        int m = queries.size();
        
        // Sort intervals by starting point
        sort(intervals.begin(), intervals.end());
        
        // Pair queries with their original indices and sort
        vector<pair<int, int>> sortedQueries;
        for (int i = 0; i < m; i++) {
            sortedQueries.push_back({queries[i], i});
        }
        sort(sortedQueries.begin(), sortedQueries.end());
        
        vector<int> result(m, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> minHeap; // (size, end)
        
        int intervalIdx = 0;
        
        for (const auto& [query, originalIdx] : sortedQueries) {
            // Add all intervals that start before or at the query point
            while (intervalIdx < n && intervals[intervalIdx][0] <= query) {
                int size = intervals[intervalIdx][1] - intervals[intervalIdx][0] + 1;
                minHeap.push({size, intervals[intervalIdx][1]});
                intervalIdx++;
            }
            
            // Remove intervals that end before the query point
            while (!minHeap.empty() && minHeap.top().second < query) {
                minHeap.pop();
            }
            
            // The top of the heap is the smallest interval containing the query
            if (!minHeap.empty()) {
                result[originalIdx] = minHeap.top().first;
            }
        }
        
        return result;          
    }
};
