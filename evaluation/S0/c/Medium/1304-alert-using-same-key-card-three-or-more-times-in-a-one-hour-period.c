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

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char** alertNames(char** keyName, int keyNameSize, char** keyTime, int keyTimeSize, int* returnSize) {
    // Create a structure to hold name and times
    typedef struct {
        char* name;
        int* times;
        int timesSize;
        int timesCapacity;
    } UserTimes;

    // Function to convert "HH:MM" to minutes
    int timeToMinutes(char* time) {
        int hours = (time[0] - '0') * 10 + (time[1] - '0');
        int minutes = (time[3] - '0') * 10 + (time[4] - '0');
        return hours * 60 + minutes;
    }

    // Hash map to store user times
    #define HASH_SIZE 100003
    UserTimes* hashMap[HASH_SIZE] = {0};

    // Hash function
    unsigned int hash(char* str) {
        unsigned int hash = 5381;
        int c;
        while ((c = *str++))
            hash = ((hash << 5) + hash) + c; // hash * 33 + c
        return hash % HASH_SIZE;
    }

    // Insert or get user times from hash map
    UserTimes* getUserTimes(char* name) {
        unsigned int idx = hash(name);
        while (hashMap[idx]) {
            if (strcmp(hashMap[idx]->name, name) == 0)
                return hashMap[idx];
            idx = (idx + 1) % HASH_SIZE;
        }
        UserTimes* userTimes = (UserTimes*)malloc(sizeof(UserTimes));
        userTimes->name = strdup(name);
        userTimes->times = (int*)malloc(10 * sizeof(int));
        userTimes->timesSize = 0;
        userTimes->timesCapacity = 10;
        hashMap[idx] = userTimes;
        return userTimes;
    }

    // Populate the hash map with times
    for (int i = 0; i < keyNameSize; i++) {
        UserTimes* userTimes = getUserTimes(keyName[i]);
        if (userTimes->timesSize == userTimes->timesCapacity) {
            userTimes->timesCapacity *= 2;
            userTimes->times = (int*)realloc(userTimes->times, userTimes->timesCapacity * sizeof(int));
        }
        userTimes->times[userTimes->timesSize++] = timeToMinutes(keyTime[i]);
    }

    // Check for alerts     
    char** alerts = (char**)malloc(keyNameSize * sizeof(char*));
    int alertCount = 0;
    for (int i = 0; i < HASH_SIZE; i++) {
        if (hashMap[i]) {
            UserTimes* userTimes = hashMap[i];
            // Sort times
            qsort(userTimes->times, userTimes->timesSize, sizeof(int), (int (*)(const void*, const void*))strcmp);
            // Check for any 3 times within 60 minutes
            for (int j = 0; j <= userTimes->timesSize - 3; j++) {
                if (userTimes->times[j + 2] - userTimes->times[j] <= 60) {
                    alerts[alertCount++] = userTimes->name;
                    break;
                }
            }
        }
    }
    // Sort alerts alphabetically
    qsort(alerts, alertCount, sizeof(char*), (int (*)(const void*, const void*))strcmp);
    *returnSize = alertCount;
    return alerts;
}
