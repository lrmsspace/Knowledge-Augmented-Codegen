// Source: https://leetcode.com/problems/closest-room/   |   Difficulty: Hard
//
// Problem Description:
// There is a hotel with n rooms. The rooms are represented by a 2D integer array rooms where rooms[i] = [roomIdi, sizei] denotes that there is a room with room number roomIdi and size equal to sizei. Each roomIdi is guaranteed to be unique.
//
// You are also given k queries in a 2D array queries where queries[j] = [preferredj, minSizej]. The answer to the jth query is the room number id of a room such that:
//
//
// 	The room has a size of at least minSizej, and
// 	abs(id - preferredj) is minimized, where abs(x) is the absolute value of x.
//
//
// If there is a tie in the absolute difference, then use the room with the smallest such id. If there is no such room, the answer is -1.
//
// Return an array answer of length k where answer[j] contains the answer to the jth query.
//
// Example:
// Input: rooms = [[2,2],[1,2],[3,2]], queries = [[3,1],[3,3],[5,2]]
// Output: [3,-1,3]
// Explanation: The answers to the queries are as follows:
// Query = [3,1]: Room number 3 is the closest as abs(3 - 3) = 0, and its size of 2 is at least 1. The answer is 3.
// Query = [3,3]: There are no rooms with a size of at least 3, so the answer is -1.
// Query = [5,2]: Room number 3 is the closest as abs(3 - 5) = 2, and its size of 2 is at least 2. The answer is 3.
//
// Constraints:
// n == rooms.length
// 	1 <= n <= 105
// 	k == queries.length
// 	1 <= k <= 104
// 	1 <= roomIdi, preferredj <= 107
// 	1 <= sizei, minSizej <= 107
//

class Solution {
public:
    vector<int> closestRoom(vector<vector<int>>& rooms, vector<vector<int>>& queries) {
        int n = rooms.size();
        int k = queries.size();
        
        // Sort rooms by size descending
        sort(rooms.begin(), rooms.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] > b[1];
        });
        
        // Prepare queries with original indices
        vector<vector<int>> queriesWithIndex(k, vector<int>(3));
        for (int i = 0; i < k; i++) {
            queriesWithIndex[i][0] = queries[i][0];
            queriesWithIndex[i][1] = queries[i][1];
            queriesWithIndex[i][2] = i;
        }
        
        // Sort queries by minSize descending
        sort(queriesWithIndex.begin(), queriesWithIndex.end(), [](const vector<int>& a, const vector<int>& b) {
            return a[1] > b[1];
        });
        
        set<int> availableRooms;
        vector<int> result(k, -1);
        int roomIdx = 0;
        
        for (const auto& query : queriesWithIndex) {
            int preferred = query[0];
            int minSize = query[1];
            int originalIdx = query[2];
            
            // Add all rooms that satisfy the minSize condition
            while (roomIdx < n && rooms[roomIdx][1] >= minSize) {
                availableRooms.insert(rooms[roomIdx][0]);
                roomIdx++;
            }
            
            if (availableRooms.empty()) {
                result[originalIdx] = -1;
                continue;
            }
            
            // Find the closest room
            auto it = availableRooms.lower_bound(preferred);
            int closestRoom = -1;
            int minDiff = INT_MAX;
            
            if (it != availableRooms.end()) {
                int diff = abs(*it - preferred);
                if (diff < minDiff || (diff == minDiff && *it < closestRoom)) {
                    closestRoom = *it;
                    minDiff = diff;
                }
            }
            
            if (it != availableRooms.begin()) {
                --it;
                int diff = abs(*it - preferred);
                if (diff < minDiff || (diff == minDiff && *it < closestRoom)) {
                    closestRoom = *it;
                    minDiff = diff;
                }
            }
            
            result[originalIdx] = closestRoom;        
        }
        return result;  
    }
};
