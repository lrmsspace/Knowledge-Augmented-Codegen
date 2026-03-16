// Source: https://leetcode.com/problems/meeting-rooms-iii/   |   Difficulty: Hard
//
// Problem Description:
// You are given an integer n. There are n rooms numbered from 0 to n - 1.
//
// You are given a 2D integer array meetings where meetings[i] = [starti, endi] means that a meeting will be held during the half-closed time interval [starti, endi). All the values of starti are unique.
//
// Meetings are allocated to rooms in the following manner:
//
//
// 	Each meeting will take place in the unused room with the lowest number.
// 	If there are no available rooms, the meeting will be delayed until a room becomes free. The delayed meeting should have the same duration as the original meeting.
// 	When a room becomes unused, meetings that have an earlier original start time should be given the room.
//
//
// Return the number of the room that held the most meetings. If there are multiple rooms, return the room with the lowest number.
//
// A half-closed interval [a, b) is the interval between a and b including a and not including b.
//
// Example:
// Input: n = 2, meetings = [[0,10],[1,5],[2,7],[3,4]]
// Output: 0
// Explanation:
// - At time 0, both rooms are not being used. The first meeting starts in room 0.
// - At time 1, only room 1 is not being used. The second meeting starts in room 1.
// - At time 2, both rooms are being used. The third meeting is delayed.
// - At time 3, both rooms are being used. The fourth meeting is delayed.
// - At time 5, the meeting in room 1 finishes. The third meeting starts in room 1 for the time period [5,10).
// - At time 10, the meetings in both rooms finish. The fourth meeting starts in room 0 for the time period [10,11).
// Both rooms 0 and 1 held 2 meetings, so we return 0.
//
// Constraints:
// 1 <= n <= 100
// 	1 <= meetings.length <= 105
// 	meetings[i].length == 2
// 	0 <= starti < endi <= 5 * 105
// 	All the values of starti are unique.
//

int mostBooked(int n, int** meetings, int meetingsSize, int* meetingsColSize) {
    /* sort meetings by start time */
    qsort(meetings, meetingsSize, sizeof(int*),
          [](const void *a, const void *b) {
              int *ma = *(int**)a;
              int *mb = *(int**)b;
              return ma[0] - mb[0];
          });

    /* room next available time */
    int *roomTime = (int*)calloc(n, sizeof(int));
    /* room meeting count */
    int *roomCount = (int*)calloc(n, sizeof(int));
    if (!roomTime || !roomCount) {
        free(roomTime); free(roomCount);
        return 0;
    }

    for (int i = 0; i < meetingsSize; ++i) {
        int start = meetings[i][0];
        int end = meetings[i][1];
        int duration = end - start;

        /* find available room with lowest number */
        int room = -1;
        for (int r = 0; r < n; ++r) {
            if (roomTime[r] <= start) {
                room = r;
                break;
            }
        }
        if (room == -1) {
            /* no available room, find the one that becomes free the earliest */
            int earliest = roomTime[0];
            room = 0;
            for (int r = 1; r < n; ++r) {
                if (roomTime[r] < earliest) {
                    earliest = roomTime[r];
                    room = r;
                }
            }
            /* delay the meeting */
            start = roomTime[room];
            end = start + duration;
        }
        /* assign meeting to the room */
        roomTime[room] = end;
        roomCount[room]++;
    }

    /* find the room with the most meetings */
    int maxCount = 0;
    int resultRoom = 0;
    for (int r = 0; r < n; ++r) {
        if (roomCount[r] > maxCount) {
            maxCount = roomCount[r];
            resultRoom = r;
        }
    }

    free(roomTime);
    free(roomCount);
    return resultRoom;      
}
