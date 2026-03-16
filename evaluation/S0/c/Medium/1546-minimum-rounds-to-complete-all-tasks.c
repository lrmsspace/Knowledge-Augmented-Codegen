// Source: https://leetcode.com/problems/minimum-rounds-to-complete-all-tasks/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed integer array tasks, where tasks[i] represents the difficulty level of a task. In each round, you can complete either 2 or 3 tasks of the same difficulty level.
//
// Return the minimum rounds required to complete all the tasks, or -1 if it is not possible to complete all the tasks.
//
// Example:
// Input: tasks = [2,2,3,3,2,4,4,4,4,4]
// Output: 4
// Explanation: To complete all the tasks, a possible plan is:
// - In the first round, you complete 3 tasks of difficulty level 2. 
// - In the second round, you complete 2 tasks of difficulty level 3. 
// - In the third round, you complete 3 tasks of difficulty level 4. 
// - In the fourth round, you complete 2 tasks of difficulty level 4.  
// It can be shown that all the tasks cannot be completed in fewer than 4 rounds, so the answer is 4.
//
// Constraints:
// 1 <= tasks.length <= 105
// 	1 <= tasks[i] <= 109
//
//
//  
// Note: This question is the same as 2870: Minimum Number of Operations to Make Array Empty.
//

int minimumRounds(int* tasks, int tasksSize) {
    int freqMap[1000000000] = {0};
    for (int i = 0; i < tasksSize; i++) {
        freqMap[tasks[i]]++;
    }

    int rounds = 0;
    for (int i = 0; i < 1000000000; i++) {
        if (freqMap[i] == 0) {
            continue;
        }
        if (freqMap[i] == 1) {
            return -1;
        }
        rounds += (freqMap[i] + 2) / 3;
    }

    return rounds;      
}
