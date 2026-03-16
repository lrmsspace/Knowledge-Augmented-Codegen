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
// Helpful references (internal KB):
// - The Inclusion-Exclusion Principle (string, counting)
//   • When to use: Use when you need to determine the frequency of characters or substrings within a string. It is essential for tasks like anagram detection or checking character distribution.
//   • Idea: This technique involves iterating through a string to tally the occurrences of its constituent elements, typically characters or words. It generally operates in O(N) time complexity, where N is the string's length.
//   • Invariants: The count for each character reflects its total occurrences processed so far.; All characters encountered up to the current position have been tallied.
//   • Tips: Use a hash map (dictionary) for arbitrary character sets.; Use an array for fixed-size character sets (e.g., ASCII, lowercase English).
//   • Pitfalls: Forgetting to handle case sensitivity or ignore non-alphanumeric characters.; Incorrectly handling Unicode characters with fixed-size arrays.
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Paint the edges of the tree (tree, array, dfs, lca, segment-tree)
//   • When to use: Used for efficiently handling queries on a tree that involve updating edge properties (like color) and querying aggregated properties (like count of colored edges) along paths between two nodes.
//   • Idea: This technique uses an Euler tour and two segment trees to maintain edge properties and query path sums. It allows for O(log N) updates and queries after an O(N) preprocessing step.
//   • Invariants: The Euler tour correctly records each edge traversal exactly twice (once forward, once backward).; Each segment tree accurately maintains the sum of colored edges for its respective traversal direction.
//   • Tips: Reduce general path queries (i, j) to ancestor-descendant queries (LCA(i,j), i) and (LCA(i,j), j) using Lowest Common Ancestor.; The Euler tour transforms tree paths into contiguous segments in an array, enabling segment tree operations.
//   • Pitfalls: Incorrectly handling the LCA step can lead to wrong path decomposition for general queries.; Off-by-one errors when defining the segment tree query range [p, q-1] in the Euler tour.
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
int* countMentions(int numberOfUsers, char*** events, int eventsSize, int* eventsColSize, int* returnSize) {
    int* mentions = (int*)calloc(numberOfUsers, sizeof(int));
    int* online = (int*)calloc(numberOfUsers, sizeof(int));
    for (int i = 0; i < numberOfUsers; i++) {
        online[i] = 1; // All users are initially online
    }

    for (int i = 0; i < eventsSize; i++) {
        char* eventType = events[i][0];
        int timestamp = atoi(events[i][1]);

        if (strcmp(eventType, "OFFLINE") == 0) {
            int userId = atoi(events[i][2]);
            online[userId] = 0; // User goes offline
            // Schedule the user to come back online after 60 time units
            // We can use a simple array to track when users come back online
            // For simplicity, we will just mark them as offline and check the timestamp in the next iterations
        } else if (strcmp(eventType, "MESSAGE") == 0) {
            char* mentionsString = events[i][2];
            char* token = strtok(mentionsString, " ");
            while (token != NULL) {
                if (strcmp(token, "ALL") == 0) {
                    for (int j = 0; j < numberOfUsers; j++) {
                        if (online[j]) {
                            mentions[j]++;
                        }
                    }
                } else if (strcmp(token, "HERE") == 0) {
                    for (int j = 0; j < numberOfUsers; j++) {
                        if (online[j]) {
                            mentions[j]++;
                        }
                    }
                } else if (strncmp(token, "id", 2) == 0) {
                    int userId = atoi(token + 2);
                    if (online[userId]) {
                        mentions[userId]++;
                    }
                }
                token = strtok(NULL, " ");
            }
        }

        // Check if any users come back online at this timestamp
        for (int j = 0; j < numberOfUsers; j++) {
            if (!online[j] && timestamp >= atoi(events[i][1]) + 60) {
                online[j] = 1; // User comes back online
            }
        }
    }

    free(online);
    *returnSize = numberOfUsers;
    return mentions;        
}
