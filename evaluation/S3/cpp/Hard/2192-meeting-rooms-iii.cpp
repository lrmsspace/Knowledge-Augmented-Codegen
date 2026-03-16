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
// Helpful references (internal KB):
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when tasks with associated processing times and costs need to be sequenced on a single machine to minimize a total objective function, typically involving weighted completion times or penalties. The optimal sequence is found by a greedy sort.
//   • Idea: This method finds an optimal schedule for jobs on a single machine by sorting them according to a greedy criterion derived from an exchange argument. It achieves an optimal solution with O(N log N) time complexity, dominated by the sorting step.
//   • Invariants: The relative order of any two jobs i and j in the sorted sequence is consistent with the greedy comparison rule.; Any prefix of the sorted schedule represents an optimal ordering for the jobs within that prefix.
//   • Tips: Clearly define the objective function to be minimized.; Formulate the greedy sorting rule using an exchange argument for any two adjacent jobs.
//   • Pitfalls: Incorrectly deriving the greedy comparison criterion.; Applying this method to problems with multiple machines or complex precedence constraints without adaptation.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: When tasks need to be processed sequentially on a single resource to optimize a cumulative metric like total completion time or weighted sum of completion times.
//   • Idea: This algorithm finds an optimal sequence for processing jobs on a single machine by applying a greedy strategy, often involving sorting based on specific criteria. It typically achieves an optimal schedule in O(N log N) time complexity.
//   • Invariants: The list of jobs is sorted according to the chosen greedy criterion.; For any prefix of the sorted jobs, the current schedule minimizes the objective function for those jobs.
//   • Tips: Identify the correct sorting key (e.g., processing time, weight/time ratio) for the objective function.; Prove optimality using an exchange argument to justify the greedy choice.
//   • Pitfalls: Applying an incorrect sorting criterion for the specific optimization objective.; Assuming a greedy approach is always optimal without a formal proof.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    int mostBooked(int n, vector<vector<int>>& meetings) {
        vector<int> roomCount(n, 0);    
        priority_queue<int, vector<int>, greater<int>> availableRooms; // Min-heap for available rooms
        priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long
    long, int>>> ongoingMeetings; // Min-heap for ongoing meetings (end time, room number)
        for (int i = 0; i < n; ++i) {
            availableRooms.push(i); // Initially, all rooms are available
        }
        sort(meetings.begin(), meetings.end()); // Sort meetings by start time

        for (const auto& meeting : meetings) {
            long long start = meeting[0];
            long long end = meeting[1];

            // Free up rooms that have finished their meetings
            while (!ongoingMeetings.empty() && ongoingMeetings.top().first <= start) {
                availableRooms.push(ongoingMeetings.top().second);
                ongoingMeetings.pop();
            }

            if (availableRooms.empty()) {
                // No rooms available, delay the meeting
                auto nextAvailable = ongoingMeetings.top();
                ongoingMeetings.pop();
                long long newStart = nextAvailable.first;
                long long newEnd = newStart + (end - start);
                int roomNumber = nextAvailable.second;
                roomCount[roomNumber]++;
                ongoingMeetings.push({newEnd, roomNumber});
            } else {
                // Assign the meeting to the lowest numbered available room
                int roomNumber = availableRooms.top();
                availableRooms.pop();
                roomCount[roomNumber]++;
                ongoingMeetings.push({end, roomNumber});
            }
        }

        // Find the room with the most meetings
        int maxCount = 0;
        int resultRoom = 0;
        for (int i = 0; i < n; ++i) {
            if (roomCount[i] > maxCount) {
                maxCount = roomCount[i];
                resultRoom = i;
            }
        }
        return resultRoom;
    }
};
