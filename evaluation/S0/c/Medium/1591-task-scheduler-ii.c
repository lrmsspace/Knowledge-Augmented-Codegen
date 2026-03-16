// Source: https://leetcode.com/problems/task-scheduler-ii/   |   Difficulty: Medium
//
// Problem Description:
// You are given a 0-indexed array of positive integers tasks, representing tasks that need to be completed in order, where tasks[i] represents the type of the ith task.
//
// You are also given a positive integer space, which represents the minimum number of days that must pass after the completion of a task before another task of the same type can be performed.
//
// Each day, until all tasks have been completed, you must either:
//
//
// 	Complete the next task from tasks, or
// 	Take a break.
//
//
// Return the minimum number of days needed to complete all tasks.
//
// Example:
// Input: tasks = [1,2,1,2,3,1], space = 3
// Output: 9
// Explanation:
// One way to complete all tasks in 9 days is as follows:
// Day 1: Complete the 0th task.
// Day 2: Complete the 1st task.
// Day 3: Take a break.
// Day 4: Take a break.
// Day 5: Complete the 2nd task.
// Day 6: Complete the 3rd task.
// Day 7: Take a break.
// Day 8: Complete the 4th task.
// Day 9: Complete the 5th task.
// It can be shown that the tasks cannot be completed in less than 9 days.
//
// Constraints:
// 1 <= tasks.length <= 105
// 	1 <= tasks[i] <= 109
// 	1 <= space <= tasks.length
//

long long taskSchedulerII(int* tasks, int tasksSize, int space) {
    long long day = 0;
    // Hash map to store the next available day for each task type
    // Using a simple array of structs to simulate a hash map
    #define HASH_SIZE 131071 // A large prime number for better distribution
    typedef struct Node {
        long long key;
        long long value;
        struct Node* next;
    } Node;

    Node* hashMap[HASH_SIZE] = {0};

    long long hash(long long key) {
        return key % HASH_SIZE;
    }

    void put(long long key, long long value) {
        long long idx = hash(key);
        Node* node = hashMap[idx];
        while (node) {
            if (node->key == key) {
                node->value = value;
                return;
            }
            node = node->next;
        }
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->value = value;
        newNode->next = hashMap[idx];
        hashMap[idx] = newNode;
    }

    long long get(long long key) {
        long long idx = hash(key);
        Node* node = hashMap[idx];
        while (node) {
            if (node->key == key) {
                return node->value;
            }
            node = node->next;
        }
        return -1; // Not found
    }

    for (int i = 0; i < tasksSize; i++) {
        day++;
        long long nextAvailableDay = get(tasks[i]);
        if (nextAvailableDay != -1 && day < nextAvailableDay) {
            day = nextAvailableDay;
        }
        put(tasks[i], day + space + 1);
    }

    // Free the hash map
    for (int i = 0; i < HASH_SIZE; i++) {
        Node* node = hashMap[i];
        while (node) {
            Node* temp = node;
            node = node->next;
            free(temp);
        }
    }

    return day;     
}
