// Source: https://leetcode.com/problems/time-to-cross-a-bridge/   |   Difficulty: Hard
//
// Problem Description:
// There are k workers who want to move n boxes from the right (old) warehouse to the left (new) warehouse. You are given the two integers n and k, and a 2D integer array time of size k x 4 where time[i] = [righti, picki, lefti, puti].
//
// The warehouses are separated by a river and connected by a bridge. Initially, all k workers are waiting on the left side of the bridge. To move the boxes, the ith worker can do the following:
//
//
// 	Cross the bridge to the right side in righti minutes.
// 	Pick a box from the right warehouse in picki minutes.
// 	Cross the bridge to the left side in lefti minutes.
// 	Put the box into the left warehouse in puti minutes.
//
//
// The ith worker is less efficient than the jth worker if either condition is met:
//
//
// 	lefti + righti > leftj + rightj
// 	lefti + righti == leftj + rightj and i > j
//
//
// The following rules regulate the movement of the workers through the bridge:
//
//
// 	Only one worker can use the bridge at a time.
// 	When the bridge is unused prioritize the least efficient worker (who have picked up the box) on the right side to cross. If not, prioritize the least efficient worker on the left side to cross.
// 	If enough workers have already been dispatched from the left side to pick up all the remaining boxes, no more workers will be sent from the left side.
//
//
// Return the elapsed minutes at which the last box reaches the left side of the bridge.
//
// Example:
// Input: n = 1, k = 3, time = [[1,1,2,1],[1,1,3,1],[1,1,4,1]]
//
// Output: 6
//
// Explanation:
//
//
// From 0 to 1 minutes: worker 2 crosses the bridge to the right.
// From 1 to 2 minutes: worker 2 picks up a box from the right warehouse.
// From 2 to 6 minutes: worker 2 crosses the bridge to the left.
// From 6 to 7 minutes: worker 2 puts a box at the left warehouse.
// The whole process ends after 7 minutes. We return 6 because the problem asks for the instance of time at which the last worker reaches the left side of the bridge.
//
// Constraints:
// 1 <= n, k <= 104
// 	time.length == k
// 	time[i].length == 4
// 	1 <= lefti, picki, righti, puti <= 1000
//

class Solution {
    public int findCrossingTime(int n, int k, int[][] time) {
        PriorityQueue<int[]> left = new PriorityQueue<>((a, b) -> (time[b[0]][0] + time[b[0]][2] != time[a[0]][0] + time[a[0]][2]) ? (time[b[0]][0] + time[b[0]][2]) - (time[a[0]][0] + time[a[0]][2]) : b[0] - a[0]);
        PriorityQueue<int[]> right = new PriorityQueue<>((a, b) -> (time[b[0]][0] + time[b[0]][2] != time[a[0]][0] + time[a[0]][2]) ? (time[b[0]][0] + time[b[0]][2]) - (time[a[0]][0] + time[a[0]][2]) : b[0] - a[0]);
        PriorityQueue<int[]> busy = new PriorityQueue<>((a, b) -> a[1] - b[1]);

        for (int i = 0; i < k; i++) {
            left.offer(new int[]{i});
        }

        int currTime = 0;
        int boxesLeft = n;

        while (boxesLeft > 0 || !right.isEmpty() || !busy.isEmpty()) {
            while (!busy.isEmpty() && busy.peek()[1] <= currTime) {
                int[] worker = busy.poll();
                if (worker[2] == 0) {
                    right.offer(new int[]{worker[0]});
                } else {
                    left.offer(new int[]{worker[0]});
                }
            }

            if (!right.isEmpty()) {
                int[] worker = right.poll();
                currTime += time[worker[0]][2];
                busy.offer(new int[]{worker[0], currTime + time[worker[0]][3], 1});
            } else if (boxesLeft > 0 && !left.isEmpty()) {
                int[] worker = left.poll();
                currTime += time[worker[0]][0];
                busy.offer(new int[]{worker[0], currTime + time[worker[0]][1], 0});
                boxesLeft--;
            } else if (!busy.isEmpty()) {
                currTime = busy.peek()[1];
            }
        }

        return currTime;            
    }
}
