// Source: https://leetcode.com/problems/count-mentions-per-user/   |   Difficulty: Medium
//
// Problem Description:
// You are given an integer numberOfUsers representing the total number of users and an array events of size n x 3.
//
// Each events[i] can be either of the following two types:
//
//
// 	Message Event: ["MESSAGE", "timestampi", "mentions_stringi"]
//
// 	
// 		This event indicates that a set of users was mentioned in a message at timestampi.
// 		The mentions_stringi string can contain one of the following tokens:
// 		
// 			id<number>: where <number> is an integer in range [0,numberOfUsers - 1]. There can be multiple ids separated by a single whitespace and may contain duplicates. This can mention even the offline users.
// 			ALL: mentions all users.
// 			HERE: mentions all online users.
// 		
// 		
// 	
// 	
// 	Offline Event: ["OFFLINE", "timestampi", "idi"]
// 	
// 		This event indicates that the user idi had become offline at timestampi for 60 time units. The user will automatically be online again at time timestampi + 60.
// 	
// 	
//
//
// Return an array mentions where mentions[i] represents the number of mentions the user with id i has across all MESSAGE events.
//
// All users are initially online, and if a user goes offline or comes back online, their status change is processed before handling any message event that occurs at the same timestamp.
//
// Note that a user can be mentioned multiple times in a single message event, and each mention should be counted separately.
//
// Example:
// Input: numberOfUsers = 2, events = [["MESSAGE","10","id1 id0"],["OFFLINE","11","0"],["MESSAGE","71","HERE"]]
//
// Output: [2,2]
//
// Explanation:
//
// Initially, all users are online.
//
// At timestamp 10, id1 and id0 are mentioned. mentions = [1,1]
//
// At timestamp 11, id0 goes offline.
//
// At timestamp 71, id0 comes back online and "HERE" is mentioned. mentions = [2,2]
//
// Constraints:
// 1 <= numberOfUsers <= 100
// 	1 <= events.length <= 100
// 	events[i].length == 3
// 	events[i][0] will be one of MESSAGE or OFFLINE.
// 	1 <= int(events[i][1]) <= 105
// 	The number of id<number> mentions in any "MESSAGE" event is between 1 and 100.
// 	0 <= <number> <= numberOfUsers - 1
// 	It is guaranteed that the user id referenced in the OFFLINE event is online at the time the event occurs.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* countMentions(int numberOfUsers, char*** events, int eventsSize, int* eventsColSize, int* returnSize) {
    int* mentions = (int*)calloc(numberOfUsers, sizeof(int));
    int* online = (int*)calloc(numberOfUsers, sizeof(int));
    for (int i = 0; i < numberOfUsers; i++) {
        online[i] = 1; // All users are initially online
    }

    // To keep track of when users will come back online
    int* offlineUntil = (int*)calloc(numberOfUsers, sizeof(int));

    for (int i = 0; i < eventsSize; i++) {
        char* eventType = events[i][0];
        int timestamp = atoi(events[i][1]);

        // Update online status based on offlineUntil times
        for (int j = 0; j < numberOfUsers; j++) {
            if (offlineUntil[j] > 0 && timestamp >= offlineUntil[j]) {
                online[j] = 1; // User comes back online
                offlineUntil[j] = 0;
            }
        }

        if (strcmp(eventType, "OFFLINE") == 0) {
            int userId = atoi(events[i][2]);
            online[userId] = 0; // User goes offline
            offlineUntil[userId] = timestamp + 60; // Set when the user will come back online
        } else if (strcmp(eventType, "MESSAGE") == 0) {
            char* mentionsString = events[i][2];
            char* token = strtok(mentionsString, " ");
            while (token != NULL) {
                if (strcmp(token, "ALL") == 0) {
                    for (int j = 0; j < numberOfUsers; j++) {
                        mentions[j]++;
                    }
                } else if (strcmp(token, "HERE") == 0) {
                    for (int j = 0; j < numberOfUsers; j++) {
                        if (online[j]) {
                            mentions[j]++;
                        }
                    }
                } else if (strncmp(token, "id", 2) == 0) {
                    int userId = atoi(token + 2);
                    mentions[userId]++;
                }
                token = strtok(NULL, " ");
            }
        }
    }

    free(online);
    free(offlineUntil);

    *returnSize = numberOfUsers;
    return mentions;        
}
