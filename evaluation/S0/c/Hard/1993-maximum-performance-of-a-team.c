// Source: https://leetcode.com/problems/maximum-performance-of-a-team/   |   Difficulty: Hard
//
// Problem Description:
// You are given two integers n and k and two integer arrays speed and efficiency both of length n. There are n engineers numbered from 1 to n. speed[i] and efficiency[i] represent the speed and efficiency of the ith engineer respectively.
//
// Choose at most k different engineers out of the n engineers to form a team with the maximum performance.
//
// The performance of a team is the sum of its engineers' speeds multiplied by the minimum efficiency among its engineers.
//
// Return the maximum performance of this team. Since the answer can be a huge number, return it modulo 109 + 7.
//
// Example:
// Input: n = 6, speed = [2,10,3,1,5,8], efficiency = [5,4,3,9,7,2], k = 2
// Output: 60
// Explanation: 
// We have the maximum performance of the team by selecting engineer 2 (with speed=10 and efficiency=4) and engineer 5 (with speed=5 and efficiency=7). That is, performance = (10 + 5) * min(4, 7) = 60.
//
// Constraints:
// 1 <= k <= n <= 105
// 	speed.length == n
// 	efficiency.length == n
// 	1 <= speed[i] <= 105
// 	1 <= efficiency[i] <= 108
//

int maxPerformance(int n, int* speed, int speedSize, int* efficiency, int efficiencySize, int k) {
    typedef struct {
        int speed;
        int efficiency;
    } Engineer;

    int MOD = 1000000007;

    Engineer* engineers = (Engineer*)malloc(n * sizeof(Engineer));
    for (int i = 0; i < n; ++i) {
        engineers[i].speed = speed[i];
        engineers[i].efficiency = efficiency[i];
    }

    // Sort engineers by efficiency in descending order
    qsort(engineers, n, sizeof(Engineer), [](const void* a, const void* b) {
        return ((Engineer*)b)->efficiency - ((Engineer*)a)->efficiency;
    });

    // Min-heap for speeds
    int* speedHeap = (int*)malloc(k * sizeof(int));
    int heapSize = 0;
    long long speedSum = 0;
    long long maxPerf = 0;

    for (int i = 0; i < n; ++i) {
        if (heapSize == k) {
            // Remove the smallest speed from the heap
            speedSum -= speedHeap[0];
            speedHeap[0] = speedHeap[heapSize - 1];
            --heapSize;
            // Heapify down
            int idx = 0;
            while (true) {
                int left = 2 * idx + 1;
                int right = 2 * idx + 2;
                int smallest = idx;
                if (left < heapSize && speedHeap[left] < speedHeap[smallest]) smallest = left;
                if (right < heapSize && speedHeap[right] < speedHeap[smallest]) smallest = right;
                if (smallest == idx) break;
                int temp = speedHeap[idx];
                speedHeap[idx] = speedHeap[smallest];
                speedHeap[smallest] = temp;
                idx = smallest;
            }
        }
        // Add current engineer's speed to the heap
        speedHeap[heapSize++] = engineers[i].speed;
        // Heapify up
        int idx = heapSize - 1;
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (speedHeap[parent] <= speedHeap[idx]) break;
            int temp = speedHeap[parent];
            speedHeap[parent] = speedHeap[idx];
            speedHeap[idx] = temp;
            idx = parent;
        }
        speedSum += engineers[i].speed;
        long long perf = speedSum * engineers[i].efficiency;
        if (perf > maxPerf) {
            maxPerf = perf;
        }
        
    }
    free(engineers);
    free(speedHeap);
    return maxPerf % MOD;
}
