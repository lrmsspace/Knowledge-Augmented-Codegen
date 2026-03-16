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

/**
 * @param {number[][]} rooms
 * @param {number[][]} queries
 * @return {number[]}
 */
var closestRoom = function(rooms, queries) {
    rooms.sort((a, b) => b[1] - a[1]);
    const indexedQueries = queries.map((query, index) => [...query, index]);
    indexedQueries.sort((a, b) => b[1] - a[1]);
    const result = new Array(queries.length).fill(-1);
    const roomIds = [];
    let roomIndex = 0;
    for (const [preferred, minSize, queryIndex] of indexedQueries) {
        while (roomIndex < rooms.length && rooms[roomIndex][1] >= minSize) {
            const roomId = rooms[roomIndex][0];
            const insertPos = binarySearch(roomIds, roomId);
            roomIds.splice(insertPos, 0, roomId);
            roomIndex++;
        }
        if (roomIds.length > 0) {
            const pos = binarySearch(roomIds, preferred);
            const candidates = [];
            if (pos < roomIds.length) {
                candidates.push(roomIds[pos]);
            }
            if (pos > 0) {
                candidates.push(roomIds[pos - 1]);
            }
            candidates.sort((a, b) => {
                const diffA = Math.abs(a - preferred);
                const diffB = Math.abs(b - preferred);
                if (diffA === diffB) {
                    return a - b;
                }
                return diffA - diffB;
            }
            );
            result[queryIndex] = candidates[0];
        }
    }
    return result;
};
