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
    public int[] closestRoom(int[][] rooms, int[][] queries) {
        Arrays.sort(rooms, (a, b) -> b[1] - a[1]);
        int qLen = queries.length;
        int[][] newQueries = new int[qLen][3];
        for (int i = 0; i < qLen; i++) {
            newQueries[i][0] = queries[i][0];
            newQueries[i][1] = queries[i][1];
            newQueries[i][2] = i;
        }
        Arrays.sort(newQueries, (a, b) -> b[1] - a[1]);

        TreeSet<Integer> roomIds = new TreeSet<>();
        int[] result = new int[qLen];
        int rIndex = 0;
        for (int i = 0; i < qLen; i++) {
            int preferred = newQueries[i][0];
            int minSize = newQueries[i][1];
            int originalIndex = newQueries[i][2];

            while (rIndex < rooms.length && rooms[rIndex][1] >= minSize) {
                roomIds.add(rooms[rIndex][0]);
                rIndex++;
            }

            if (roomIds.isEmpty()) {
                result[originalIndex] = -1;
            } else {
                Integer lower = roomIds.floor(preferred);
                Integer higher = roomIds.ceiling(preferred);
                if (lower == null) {
                    result[originalIndex] = higher;
                } else if (higher == null) {
                    result[originalIndex] = lower;
                } else {
                    if (preferred - lower <= higher - preferred) {
                        result[originalIndex] = lower;
                    } else {
                        result[originalIndex] = higher;
                    }
                }
            }
        }
        return result;          
    }
}
