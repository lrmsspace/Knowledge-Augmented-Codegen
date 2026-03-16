// Source: https://leetcode.com/problems/minimum-cost-to-hire-k-workers/   |   Difficulty: Hard
//
// Problem Description:
// There are n workers. You are given two integer arrays quality and wage where quality[i] is the quality of the ith worker and wage[i] is the minimum wage expectation for the ith worker.
//
// We want to hire exactly k workers to form a paid group. To hire a group of k workers, we must pay them according to the following rules:
//
//
// 	Every worker in the paid group must be paid at least their minimum wage expectation.
// 	In the group, each worker's pay must be directly proportional to their quality. This means if a worker’s quality is double that of another worker in the group, then they must be paid twice as much as the other worker.
//
//
// Given the integer k, return the least amount of money needed to form a paid group satisfying the above conditions. Answers within 10-5 of the actual answer will be accepted.
//
// Example:
// Input: quality = [10,20,5], wage = [70,50,30], k = 2
// Output: 105.00000
// Explanation: We pay 70 to 0th worker and 35 to 2nd worker.
//
// Constraints:
// n == quality.length == wage.length
// 	1 <= k <= n <= 104
// 	1 <= quality[i], wage[i] <= 104
//

double mincostToHireWorkers(int* quality, int qualitySize, int* wage, int wageSize, int k) {
    typedef struct {
        double ratio;
        int quality;
    } Worker;

    int n = qualitySize;
    Worker* workers = (Worker*)malloc(n * sizeof(Worker));
    for (int i = 0; i < n; ++i) {
        workers[i].ratio = (double)wage[i] / quality[i];
        workers[i].quality = quality[i];
    }

    // Sort workers by their wage-to-quality ratio
    qsort(workers, n, sizeof(Worker), [](const void* a, const void* b) {
        double r1 = ((Worker*)a)->ratio;
        double r2 = ((Worker*)b)->ratio;
        return (r1 > r2) - (r1 < r2);
    });

    // Max heap to keep track of the k smallest qualities
    int* maxHeap = (int*)malloc(k * sizeof(int));
    int heapSize = 0;
    double minCost = 1e9;
    int totalQuality = 0;

    for (int i = 0; i < n; ++i) {
        totalQuality += workers[i].quality;
        maxHeap[heapSize++] = workers[i].quality;

        // If we have more than k workers, remove the one with the highest quality
        if (heapSize > k) {
            // Find and remove max quality from heap
            int maxIndex = 0;
            for (int j = 1; j < heapSize; ++j) {
                if (maxHeap[j] > maxHeap[maxIndex]) {
                    maxIndex = j;
                }
            }
            totalQuality -= maxHeap[maxIndex];
            maxHeap[maxIndex] = maxHeap[--heapSize];
        }

        // If we have exactly k workers, calculate the cost
        if (heapSize == k) {
            double cost = totalQuality * workers[i].ratio;
            if (cost < minCost) {
                minCost = cost;
            }
        }
    }

    free(workers);
    free(maxHeap);
    return minCost;     
}
