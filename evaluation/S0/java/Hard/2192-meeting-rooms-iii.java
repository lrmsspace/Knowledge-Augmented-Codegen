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

class Solution {
    public int mostBooked(int n, int[][] meetings) {
        // Sort meetings by start time
        Arrays.sort(meetings, (a, b) -> Integer.compare(a[0], b[0]));

        // Min-heap for available rooms
        PriorityQueue<Integer> availableRooms = new PriorityQueue<>();
        for (int i = 0; i < n; i++) {
            availableRooms.offer(i);
        }

        // Min-heap for ongoing meetings (end time, room number)
        PriorityQueue<int[]> ongoingMeetings = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));

        // Count of meetings held in each room
        int[] meetingCount = new int[n];

        for (int[] meeting : meetings) {
            int start = meeting[0];
            int end = meeting[1];

            // Free up rooms that have finished their meetings
            while (!ongoingMeetings.isEmpty() && ongoingMeetings.peek()[0] <= start) {
                int[] finishedMeeting = ongoingMeetings.poll();
                availableRooms.offer(finishedMeeting[1]);
            }

            if (!availableRooms.isEmpty()) {
                // Assign the meeting to the lowest numbered available room
                int room = availableRooms.poll();
                meetingCount[room]++;
                ongoingMeetings.offer(new int[]{end, room});
            } else {
                // Delay the meeting to the earliest finishing room
                int[] earliestMeeting = ongoingMeetings.poll();
                int room = earliestMeeting[1];
                int newEnd = earliestMeeting[0] + (end - start);
                meetingCount[room]++;
                ongoingMeetings.offer(new int[]{newEnd, room});
            }
        }

        // Find the room with the maximum meetings held
        int maxMeetings = 0;
        int resultRoom = 0;
        for (int i = 0; i < n; i++) {
            if (meetingCount[i] > maxMeetings) {
                maxMeetings = meetingCount[i];
                resultRoom = i;
            }
        }

        return resultRoom;          
    }
}
