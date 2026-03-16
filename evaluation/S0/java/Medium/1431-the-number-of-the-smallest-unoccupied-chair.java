// Source: https://leetcode.com/problems/the-number-of-the-smallest-unoccupied-chair/   |   Difficulty: Medium
//
// Problem Description:
// There is a party where n friends numbered from 0 to n - 1 are attending. There is an infinite number of chairs in this party that are numbered from 0 to infinity. When a friend arrives at the party, they sit on the unoccupied chair with the smallest number.
//
//
// 	For example, if chairs 0, 1, and 5 are occupied when a friend comes, they will sit on chair number 2.
//
//
// When a friend leaves the party, their chair becomes unoccupied at the moment they leave. If another friend arrives at that same moment, they can sit in that chair.
//
// You are given a 0-indexed 2D integer array times where times[i] = [arrivali, leavingi], indicating the arrival and leaving times of the ith friend respectively, and an integer targetFriend. All arrival times are distinct.
//
// Return the chair number that the friend numbered targetFriend will sit on.
//
// Example:
// Input: times = [[1,4],[2,3],[4,6]], targetFriend = 1
// Output: 1
// Explanation: 
// - Friend 0 arrives at time 1 and sits on chair 0.
// - Friend 1 arrives at time 2 and sits on chair 1.
// - Friend 1 leaves at time 3 and chair 1 becomes empty.
// - Friend 0 leaves at time 4 and chair 0 becomes empty.
// - Friend 2 arrives at time 4 and sits on chair 0.
// Since friend 1 sat on chair 1, we return 1.
//
// Constraints:
// n == times.length
// 	2 <= n <= 104
// 	times[i].length == 2
// 	1 <= arrivali < leavingi <= 105
// 	0 <= targetFriend <= n - 1
// 	Each arrivali time is distinct.
//

class Solution {
    public int smallestChair(int[][] times, int targetFriend) {
        int n = times.length;

        // Create an array to hold friends with their arrival, leaving times and index
        int[][] friends = new int[n][3];
        for (int i = 0; i < n; i++) {
            friends[i][0] = times[i][0]; // arrival time
            friends[i][1] = times[i][1]; // leaving time
            friends[i][2] = i;           // friend index
        }

        // Sort friends by arrival time
        Arrays.sort(friends, (a, b) -> Integer.compare(a[0], b[0]));

        // Min-heap to track available chairs
        PriorityQueue<Integer> availableChairs = new PriorityQueue<>();
        for (int i = 0; i < n; i++) {
            availableChairs.offer(i);
        }

        // Min-heap to track occupied chairs with their leaving times
        PriorityQueue<int[]> occupiedChairs = new PriorityQueue<>((a, b) -> Integer.compare(a[0], b[0]));

        for (int[] friend : friends) {
            int arrival = friend[0];
            int leaving = friend[1];
            int index = friend[2];

            // Free up chairs that have been vacated by the time this friend arrives
            while (!occupiedChairs.isEmpty() && occupiedChairs.peek()[0] <= arrival) {
                availableChairs.offer(occupiedChairs.poll()[1]);
            }

            // Assign the smallest available chair to this friend
            int chair = availableChairs.poll();
            occupiedChairs.offer(new int[]{leaving, chair});

            // If this is the target friend, return the chair number
            if (index == targetFriend) {
                return chair;
            }
        }

        return -1; // This line should never be reached given the problem constraints           
    }
}
