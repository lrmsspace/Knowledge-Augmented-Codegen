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

/**
 * @param {number} n
 * @param {number} k
 * @param {number[][]} time
 * @return {number}
 */
var findCrossingTime = function(n, k, time) {
    const leftQueue = new MaxPriorityQueue({ priority: (i) => time[i][0] + time[i][2] });
    const rightQueue = new MaxPriorityQueue({ priority: (i) => time[i][0] + time[i][2] });
    const leftWaitQueue = new MinPriorityQueue({ priority: (i) => time[i][0] + time[i][2] });
    const rightWaitQueue = new MinPriorityQueue({ priority: (i) => time[i][0] + time[i][2] });
    for (let i = 0; i < k; i++) {
        leftQueue.enqueue(i);
    }

    let currentTime = 0;
    let boxesMoved = 0;
    while (boxesMoved < n) {
        while (!leftWaitQueue.isEmpty() && leftWaitQueue.front().element <= currentTime) {
            const worker = leftWaitQueue.dequeue().element;
            leftQueue.enqueue(worker);
        }
        while (!rightWaitQueue.isEmpty() && rightWaitQueue.front().element <= currentTime) {
            const worker = rightWaitQueue.dequeue().element;
            rightQueue.enqueue(worker);
        }
        if (!rightQueue.isEmpty()) {
            const worker = rightQueue.dequeue().element;
            currentTime += time[worker][2];
            leftWaitQueue.enqueue({ element: worker, priority: currentTime + time[worker][3] });
            boxesMoved++;
        }
        else if (!leftQueue.isEmpty()) {
            const worker = leftQueue.dequeue().element;
            currentTime += time[worker][0];
            rightWaitQueue.enqueue({ element: worker, priority: currentTime + time[worker][1] });
        }
    }
    return currentTime;
};
