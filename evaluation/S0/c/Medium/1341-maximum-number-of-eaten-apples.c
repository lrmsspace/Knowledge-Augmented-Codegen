// Source: https://leetcode.com/problems/maximum-number-of-eaten-apples/   |   Difficulty: Medium
//
// Problem Description:
// There is a special kind of apple tree that grows apples every day for n days. On the ith day, the tree grows apples[i] apples that will rot after days[i] days, that is on day i + days[i] the apples will be rotten and cannot be eaten. On some days, the apple tree does not grow any apples, which are denoted by apples[i] == 0 and days[i] == 0.
//
// You decided to eat at most one apple a day (to keep the doctors away). Note that you can keep eating after the first n days.
//
// Given two integer arrays days and apples of length n, return the maximum number of apples you can eat.
//
// Example:
// Input: apples = [1,2,3,5,2], days = [3,2,1,4,2]
// Output: 7
// Explanation: You can eat 7 apples:
// - On the first day, you eat an apple that grew on the first day.
// - On the second day, you eat an apple that grew on the second day.
// - On the third day, you eat an apple that grew on the second day. After this day, the apples that grew on the third day rot.
// - On the fourth to the seventh days, you eat apples that grew on the fourth day.
//
// Constraints:
// n == apples.length == days.length
// 	1 <= n <= 2 * 104
// 	0 <= apples[i], days[i] <= 2 * 104
// 	days[i] = 0 if and only if apples[i] = 0.
//

int eatenApples(int* apples, int applesSize, int* days, int daysSize) {
    typedef struct {
        int rot;
        int count;
    } AppleBatch;

    AppleBatch heap[applesSize + daysSize];
    int heapSize = 0;

    int totalEaten = 0;
    int day = 0;

    while (day < applesSize || heapSize > 0) {
        // Add new apples
        if (day < applesSize && apples[day] > 0) {
            int rotDay = day + days[day];
            heap[heapSize].rot = rotDay;
            heap[heapSize].count = apples[day];
            heapSize++;
        }

        // Remove rotten apples
        for (int i = 0; i < heapSize; ) {
            if (heap[i].rot <= day) {
                heap[i] = heap[heapSize - 1];
                heapSize--;
            } else {
                i++;
            }
        }

        // Eat an apple
        if (heapSize > 0) {
            // Find the batch with the earliest rot day
            int minIndex = 0;
            for (int i = 1; i < heapSize; i++) {
                if (heap[i].rot < heap[minIndex].rot) {
                    minIndex = i;
                }
            }

            // Eat one apple from that batch
            heap[minIndex].count--;
            totalEaten++;

            // If no apples left in that batch, remove it
            if (heap[minIndex].count == 0) {
                heap[minIndex] = heap[heapSize - 1];
                heapSize--;
            }
        }

        day++;
    }

    return totalEaten;      
}
