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
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* closestRoom(int** rooms, int roomsSize, int* roomsColSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
   
    typedef struct {
        int preferred;
        int minSize;
        int index;
    } Query;

    int cmpRooms(const void* a, const void* b) {
        return (*(int**)b)[1] - (*(int**)a)[1];
    }

    int cmpQueries(const void* a, const void* b) {
        return ((Query*)b)->minSize - ((Query*)a)->minSize;
    }

    qsort(rooms, roomsSize, sizeof(int*), cmpRooms);

    Query* queryList = (Query*)malloc(queriesSize * sizeof(Query));
    for (int i = 0; i < queriesSize; i++) {
        queryList[i].preferred = queries[i][0];
        queryList[i].minSize = queries[i][1];
        queryList[i].index = i;
    }
    qsort(queryList, queriesSize, sizeof(Query), cmpQueries);

    int* result = (int*)malloc(queriesSize * sizeof(int));
    int* availableRooms = (int*)malloc(roomsSize * sizeof(int));
    int availableCount = 0;
    int roomIndex = 0;

    for (int i = 0; i < queriesSize; i++) {
        int preferred = queryList[i].preferred;
        int minSize = queryList[i].minSize;

        while (roomIndex < roomsSize && rooms[roomIndex][1] >= minSize) {
            availableRooms[availableCount++] = rooms[roomIndex][0];
            roomIndex++;
        }

        if (availableCount == 0) {
            result[queryList[i].index] = -1;
            continue;
        }

        // Find the closest room
        int closestRoomId = -1;
        int minDiff = INT_MAX;
        for (int j = 0; j < availableCount; j++) {
            int diff = abs(availableRooms[j] - preferred);
            if (diff < minDiff || (diff == minDiff && availableRooms[j] < closestRoomId)) {
                minDiff = diff;
                closestRoomId = availableRooms[j];
            }
        }
        result[queryList[i].index] = closestRoomId;
    }

    free(queryList);
    free(availableRooms);
    *returnSize = queriesSize;
    return result;
    
}
