// Source: https://leetcode.com/problems/course-schedule-iii/   |   Difficulty: Hard
//
// Problem Description:
// There are n different online courses numbered from 1 to n. You are given an array courses where courses[i] = [durationi, lastDayi] indicate that the ith course should be taken continuously for durationi days and must be finished before or on lastDayi.
//
// You will start on the 1st day and you cannot take two or more courses simultaneously.
//
// Return the maximum number of courses that you can take.
//
// Example:
// Input: courses = [[100,200],[200,1300],[1000,1250],[2000,3200]]
// Output: 3
// Explanation: 
// There are totally 4 courses, but you can take 3 courses at most:
// First, take the 1st course, it costs 100 days so you will finish it on the 100th day, and ready to take the next course on the 101st day.
// Second, take the 3rd course, it costs 1000 days so you will finish it on the 1100th day, and ready to take the next course on the 1101st day. 
// Third, take the 2nd course, it costs 200 days so you will finish it on the 1300th day. 
// The 4th course cannot be taken now, since you will finish it on the 3300th day, which exceeds the closed date.
//
// Constraints:
// 1 <= courses.length <= 104
// 	1 <= durationi, lastDayi <= 104
//

int scheduleCourse(int** courses, int coursesSize, int* coursesColSize) {
    /* Sort courses by their end day */
    qsort(courses, coursesSize, sizeof(int*), 
          (int (*)(const void*, const void*)) (int (*)(int*, int*)) [](int* a, int* b) {
              return a[1] - b[1];
          });

    /* Max-heap to store durations of selected courses */
    int *heap = (int*)malloc(coursesSize * sizeof(int));
    int heapSize = 0;
    int currentTime = 0;

    for (int i = 0; i < coursesSize; i++) {
        int duration = courses[i][0];
        int lastDay = courses[i][1];

        if (currentTime + duration <= lastDay) {
            /* Add course to the schedule */
            currentTime += duration;
            heap[heapSize++] = duration;

            /* Maintain max-heap property */
            int idx = heapSize - 1;
            while (idx > 0) {
                int parent = (idx - 1) / 2;
                if (heap[parent] >= heap[idx]) break;
                int temp = heap[parent];
                heap[parent] = heap[idx];
                heap[idx] = temp;
                idx = parent;
            }
        } else if (heapSize > 0 && heap[0] > duration) {
            /* Replace the longest duration course with the current one */
            currentTime += duration - heap[0];
            heap[0] = duration;

            /* Maintain max-heap property */
            int idx = 0;
            while (true) {
                int left = 2 * idx + 1;
                int right = 2 * idx + 2;
                int largest = idx;

                if (left < heapSize && heap[left] > heap[largest]) largest = left;
                if (right < heapSize && heap[right] > heap[largest]) largest = right;

                if (largest == idx) break;
                int temp = heap[idx];
                heap[idx] = heap[largest];
                heap[largest] = temp;
                idx = largest;
            }
        }
    }

    free(heap);
    return heapSize;        
}
