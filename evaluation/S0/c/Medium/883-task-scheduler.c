// Source: https://leetcode.com/problems/task-scheduler/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array of CPU tasks, each labeled with a letter from A to Z, and a number n. Each CPU interval can be idle or allow the completion of one task. Tasks can be completed in any order, but there's a constraint: there has to be a gap of at least n intervals between two tasks with the same label.
//
// Return the minimum number of CPU intervals required to complete all tasks.
//
// Example:
// Input: tasks = ["A","A","A","B","B","B"], n = 2
//
// Output: 8
//
// Explanation: A possible sequence is: A -> B -> idle -> A -> B -> idle -> A -> B.
//
// After completing task A, you must wait two intervals before doing A again. The same applies to task B. In the 3rd interval, neither A nor B can be done, so you idle. By the 4th interval, you can do A again as 2 intervals have passed.
//
// Constraints:
// 1 <= tasks.length <= 104
// 	tasks[i] is an uppercase English letter.
// 	0 <= n <= 100
//

int leastInterval(char* tasks, int tasksSize, int n) {
    int freq[26] = {0};
    for (int i = 0; i < tasksSize; i++) {
        freq[tasks[i] - 'A']++;
    }

    int max_freq = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] > max_freq) {
            max_freq = freq[i];
        }
    }

    int max_count = 0;
    for (int i = 0; i < 26; i++) {
        if (freq[i] == max_freq) {
            max_count++;
        }
    }

    int part_count = max_freq - 1;
    int part_length = n - (max_count - 1);
    int empty_slots = part_count * part_length;
    int available_tasks = tasksSize - (max_freq * max_count);
    int idles = empty_slots > available_tasks ? empty_slots - available_tasks : 0;

    return tasksSize + idles;       
}
