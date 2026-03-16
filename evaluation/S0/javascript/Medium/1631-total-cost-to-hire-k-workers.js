// Source: https://leetcode.com/problems/total-cost-to-hire-k-workers/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array costs where costs[i] is the cost of hiring the ith worker.
//
// You are also given two integers k and candidates. We want to hire exactly k workers according to the following rules:
//
//
// 	You will run k sessions and hire exactly one worker in each session.
// 	In each hiring session, choose the worker with the lowest cost from either the first candidates workers or the last candidates workers. Break the tie by the smallest index.
// 	
// 		For example, if costs = [3,2,7,7,1,2] and candidates = 2, then in the first hiring session, we will choose the 4th worker because they have the lowest cost [3,2,7,7,1,2].
// 		In the second hiring session, we will choose 1st worker because they have the same lowest cost as 4th worker but they have the smallest index [3,2,7,7,2]. Please note that the indexing may be changed in the process.
// 	
// 	
// 	If there are fewer than candidates workers remaining, choose the worker with the lowest cost among them. Break the tie by the smallest index.
// 	A worker can only be chosen once.
//
//
// Return the total cost to hire exactly k workers.
//
// Example:
// Input: costs = [17,12,10,2,7,2,11,20,8], k = 3, candidates = 4
// Output: 11
// Explanation: We hire 3 workers in total. The total cost is initially 0.
// - In the first hiring round we choose the worker from [17,12,10,2,7,2,11,20,8]. The lowest cost is 2, and we break the tie by the smallest index, which is 3. The total cost = 0 + 2 = 2.
// - In the second hiring round we choose the worker from [17,12,10,7,2,11,20,8]. The lowest cost is 2 (index 4). The total cost = 2 + 2 = 4.
// - In the third hiring round we choose the worker from [17,12,10,7,11,20,8]. The lowest cost is 7 (index 3). The total cost = 4 + 7 = 11. Notice that the worker with index 3 was common in the first and last four workers.
// The total hiring cost is 11.
//
// Constraints:
// 1 <= costs.length <= 105 
// 	1 <= costs[i] <= 105
// 	1 <= k, candidates <= costs.length
//

/**
 * @param {number[]} costs
 * @param {number} k
 * @param {number} candidates
 * @return {number}
 */
var totalCost = function(costs, k, candidates) {
    const n = costs.length;
    let total = 0;
    let left = 0;
    let right = n - 1;
    const minHeap = [];
    const heapPush = (heap, val) => {
        heap.push(val);
        let idx = heap.length - 1;
        while (idx > 0) {
            const parentIdx = Math.floor((idx - 1) / 2);
            if (heap[parentIdx] <= heap[idx]) break;
            [heap[parentIdx], heap[idx]] = [heap[idx], heap[parentIdx]];
            idx = parentIdx;
        }
    };
    const heapPop = (heap) => {
        const top = heap[0];
        const last = heap.pop();
        if (heap.length === 0) return top;
        heap[0] = last;
        let idx = 0;
        const length = heap.length;
        while (true) {
            let leftIdx = 2 * idx + 1;
            let rightIdx = 2 * idx + 2;
            let smallestIdx = idx;
            if (leftIdx < length && heap[leftIdx] < heap[smallestIdx]) {
                smallestIdx = leftIdx;
            }
            if (rightIdx < length && heap[rightIdx] < heap[smallestIdx]) {
                smallestIdx = rightIdx;
            }
            if (smallestIdx === idx) break;
            [heap[idx], heap[smallestIdx]] = [heap[smallestIdx], heap[idx]];
            idx = smallestIdx;
        }
        return top;
    };

    for (let i = 0; i < candidates; i++) {
        if (left <= right) {
            heapPush(minHeap, costs[left]);
            left++;
        }
        if (left <= right) {
            heapPush(minHeap, costs[right]);
            right--;
        }
    }
    for (let hire = 0; hire < k; hire++) {
        const cost = heapPop(minHeap);
        total += cost;
        if (left <= right) {
            if (costs[left] <= costs[right]) {
                heapPush(minHeap, costs[left]);
                left++;
            } else {
                heapPush(minHeap, costs[right]);
                right--;
            }
        }
    }
    return total;   
};
