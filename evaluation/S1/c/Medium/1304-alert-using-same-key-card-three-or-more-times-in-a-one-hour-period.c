// Source: https://leetcode.com/problems/alert-using-same-key-card-three-or-more-times-in-a-one-hour-period/   |   Difficulty: Medium
//
// Problem Description:
// LeetCode company workers use key-cards to unlock office doors. Each time a worker uses their key-card, the security system saves the worker's name and the time when it was used. The system emits an alert if any worker uses the key-card three or more times in a one-hour period.
//
// You are given a list of strings keyName and keyTime where [keyName[i], keyTime[i]] corresponds to a person's name and the time when their key-card was used in a single day.
//
// Access times are given in the 24-hour time format "HH:MM", such as "23:51" and "09:49".
//
// Return a list of unique worker names who received an alert for frequent keycard use. Sort the names in ascending order alphabetically.
//
// Notice that "10:00" - "11:00" is considered to be within a one-hour period, while "22:51" - "23:52" is not considered to be within a one-hour period.
//
// Example:
// Input: keyName = ["daniel","daniel","daniel","luis","luis","luis","luis"], keyTime = ["10:00","10:40","11:00","09:00","11:00","13:00","15:00"]
// Output: ["daniel"]
// Explanation: "daniel" used the keycard 3 times in a one-hour period ("10:00","10:40", "11:00").
//
// Constraints:
// 1 <= keyName.length, keyTime.length <= 105
// 	keyName.length == keyTime.length
// 	keyTime[i] is in the format "HH:MM".
// 	[keyName[i], keyTime[i]] is unique.
// 	1 <= keyName[i].length <= 10
// 	keyName[i] contains only lowercase English letters.
//
// Helpful references (internal KB):
// - String Hashing (string, array, hashing, enumeration)
//   • When to use: Use string hashing to efficiently compare substrings or patterns within a larger text, or to quickly check for duplicate strings. It's ideal for problems requiring fast equality checks on string segments.
//   • Idea: String hashing converts a string or substring into a numerical hash value, allowing for O(1) comparison of substrings after O(N) precomputation. It typically uses polynomial hashing with a prime base and modulus to minimize collisions.
//   • Invariants: The hash value for the prefix S[0...i] is correctly computed and stored, based on the chosen polynomial hashing scheme.; The base 'p' and modulus 'm' remain constant throughout the hash computation for consistent results.
//   • Tips: Choose a large prime number for the base 'p' (e.g., 31, 53) to reduce collisions.; Select a large prime number for the modulus 'm' (e.g., 10^9+7, 10^9+9) to further minimize collision probability.
//   • Pitfalls: Avoid using 2^64 as a modulus, as specific collision-generating strings exist for this choice.; A small modulus 'm' or base 'p' drastically increases the likelihood of hash collisions.
// - Sqrt Decomposition (array, ds, sliding-window, two-pointers)
//   • When to use: Use when performing frequent range queries and point updates on an array, especially when a segment tree is too complex or memory-intensive, or when query types are diverse. It offers a balanced time complexity for both operations.
//   • Idea: Sqrt decomposition divides an array into blocks of size approximately sqrt(N) to optimize range queries and point updates. It achieves O(sqrt(N)) time complexity for both operations.
//   • Invariants: Each element `arr[i]` belongs to exactly one block `block[i / block_size]`.; The summary for each block `block_summary[j]` accurately reflects the state of elements within block `j`.
//   • Tips: Choose block size carefully, typically sqrt(N) for balanced performance.; Precompute block summaries (e.g., sum, min, max) for efficient queries.
//   • Pitfalls: Off-by-one errors when calculating block indices or boundaries.; Forgetting to update the block's summary after a point update.
// - Scheduling jobs on one machine (array, number, greedy, merge-sort)
//   • When to use: Use when scheduling a set of jobs on a single machine to minimize the total weighted completion time, where each job has a processing time and a linear penalty coefficient.
//   • Idea: This algorithm finds an optimal schedule for jobs on a single machine with linear penalty functions by sorting jobs based on a specific ratio. It achieves an optimal solution in O(N log N) time complexity.
//   • Invariants: The partial schedule constructed so far is optimal for the jobs included.; For any two adjacent jobs 'j' and 'k' in the final schedule, if 'j' precedes 'k', then 'c_j/t_j >= c_k/t_k'.
//   • Tips: Derive the sorting criterion using an exchange argument for adjacent jobs.; The optimal order is determined by the ratio of cost coefficient to processing time.
//   • Pitfalls: Incorrectly applying the sorting criterion, especially the ratio order.; Overlooking edge cases like zero processing times or zero penalty coefficients.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** alertNames(char** keyName, int keyNameSize, char** keyTime, int keyTimeSize, int* returnSize) {
    #define MAX_NAME_LENGTH 10
    #define MAX_TIME_LENGTH 5

    typedef struct {
        char name[MAX_NAME_LENGTH + 1];
        int times[100]; // Assuming a maximum of 100 entries per person
        int timeCount;
    } Person;

    Person persons[10000]; // Assuming a maximum of 10000 unique persons
    int personCount = 0;

    // Helper function to convert "HH:MM" to minutes
    int timeToMinutes(const char* time) {
        int hours = (time[0] - '0') * 10 + (time[1] - '0');
        int minutes = (time[3] - '0') * 10 + (time[4] - '0');
        return hours * 60 + minutes;
    }

    // Populate persons array
    for (int i = 0; i < keyNameSize; i++) {
        int j;
        for (j = 0; j < personCount; j++) {
            if (strcmp(persons[j].name, keyName[i]) == 0) {
                break;
            }
        }
        if (j == personCount) {
            strcpy(persons[personCount].name, keyName[i]);
            persons[personCount].timeCount = 0;
            personCount++;
        }
        persons[j].times[persons[j].timeCount++] = timeToMinutes(keyTime[i]);
    }

    // Check for alerts
    char** alerts = (char**)malloc(personCount * sizeof(char*));
    int alertCount = 0;

    for (int i = 0; i < personCount; i++) {
        // Sort times
        qsort(persons[i].times, persons[i].timeCount, sizeof(int), (int (*)(const void*, const void*))strcmp);

        // Check for three times within one hour
        for (int j = 0; j <= persons[i].timeCount - 3; j++) {
            if (persons[i].times[j + 2] - persons[i].times[j] <= 60) {
                alerts[alertCount] = (char*)malloc((strlen(persons[i].name) + 1) * sizeof(char));
                strcpy(alerts[alertCount], persons[i].name);
                alertCount++;
                break;
            }
        }
    }

    // Sort alerts alphabetically
    qsort(alerts, alertCount, sizeof(char*), (int (*)(const void*, const void*))strcmp);
    *returnSize = alertCount;
    return alerts;
            
}
