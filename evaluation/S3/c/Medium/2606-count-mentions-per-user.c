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
// - Length of the union of segments (array, interval, sweep-line, counting)
//   • When to use: Use when calculating the total length or measure of the union of multiple one-dimensional intervals or segments. It efficiently handles overlapping regions to avoid double-counting.
//   • Idea: This algorithm calculates the total length of the union of given line segments by processing sorted endpoints as events. It maintains a counter for active segments, adding the length of intervals where the counter is positive, achieving O(N log N) time complexity.
//   • Invariants: The `active_segments_count` accurately reflects the number of segments covering the interval `[prev_x, current_x]`.; The `total_union_length` accumulates the length of all intervals where `active_segments_count > 0`.
//   • Tips: Represent endpoints as (coordinate, type) pairs, where type indicates start (+1) or end (-1).; Sort event points primarily by coordinate, then by type (e.g., start events before end events for same coordinate).
//   • Pitfalls: Incorrect sorting order for event points, especially for coincident endpoints.; Forgetting to update the active segment counter when processing an event.
// - Finding the rank of a matrix (matrix, simulation, enumeration)
//   • When to use: Use when needing to determine the maximum number of linearly independent rows or columns in a matrix. It's also applicable for understanding the dimension of the vector space spanned by the matrix's rows or columns.
//   • Idea: Determines the rank of a matrix by transforming it into row echelon form using Gaussian elimination. The rank is the number of non-zero rows in the echelon form, with a time complexity of O(N^3).
//   • Invariants: The number of non-zero rows processed so far equals the current rank.; All elements below the pivot in the current column are zeroed out.
//   • Tips: Always choose the largest absolute value pivot for numerical stability.; Swap rows to bring a non-zero element to the pivot position.
//   • Pitfalls: Floating point precision issues can lead to incorrect zero checks.; Forgetting to increment rank only when a valid pivot is found.
// - bucket-sort (array, bucket-sort)
//   • When to use: Use when sorting elements with a known, uniform distribution over a specific range. It is efficient for numbers that are uniformly distributed across a range, often achieving linear time complexity.
//   • Idea: Bucket sort distributes elements into a fixed number of buckets, sorts each bucket individually, and then concatenates them. It can achieve O(N+K) average time complexity for uniformly distributed data.
//   • Invariants: After distributing elements, each element `x` is in bucket `floor(N * x)`.; After sorting buckets, every bucket `buckets[i]` contains its elements in sorted order.
//   • Tips: Choose the number of buckets appropriately based on data distribution and range.; Normalize input data to a [0, 1) range for simpler bucket indexing.
//   • Pitfalls: Poor performance with non-uniform data distribution, potentially degrading to O(N^2).; Requires extra space for the buckets, proportional to N+K.
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
    // Initialize the mentions array to store the count of mentions for each user
    int* mentions = (int*)calloc(numberOfUsers, sizeof(int));
    
    // Create an array to track the online status of each user (1 for online, 0 for offline)
    int* onlineStatus = (int*)calloc(numberOfUsers, sizeof(int));
    for (int i = 0; i < numberOfUsers; i++) {
        onlineStatus[i] = 1; // All users are initially online
    }
    
    // Process each event in chronological order
    for (int i = 0; i < eventsSize; i++) {
        char* eventType = events[i][0];
        int timestamp = atoi(events[i][1]);
        
        if (strcmp(eventType, "OFFLINE") == 0) {
            // Handle OFFLINE event
            int userId = atoi(events[i][2]);
            onlineStatus[userId] = 0; // Mark the user as offline
            
            // Schedule the user to come back online after 60 time units
            // We can use a simple approach to mark the user as online again after processing all events
            // by storing the timestamp when the user will come back online.
            // However, since we only need to check the status during MESSAGE events, we can directly handle it in the loop.
        } else if (strcmp(eventType, "MESSAGE") == 0) {
            // Handle MESSAGE event
            char* mentionsString = events[i][2];
            char* token = strtok(mentionsString, " ");
            
            while (token != NULL) {
                if (strcmp(token, "ALL") == 0) {
                    // Mention all users
                    for (int j = 0; j < numberOfUsers; j++) {
                        if (onlineStatus[j] == 1) { // Only count mentions for online users
                            mentions[j]++;
                        }
                    }
                } else if (strcmp(token, "HERE") == 0) {
                    // Mention all online users
                    for (int j = 0; j < numberOfUsers; j++) {
                        if (onlineStatus[j] == 1) { // Only count mentions for online users
                            mentions[j]++;
                        }
                    }
                } else if (strncmp(token, "id", 2) == 0) {
                    // Mention specific user by id      
                    int userId = atoi(token + 2); // Extract the user ID from the token
                    if (userId >= 0 && userId < numberOfUsers) {
                        if (onlineStatus[userId] == 1) { // Only count mentions for online users
                            mentions[userId]++;
                        }
                    }
                }
                token = strtok(NULL, " "); // Get the next token
            }
        }
        
    }
    
    *returnSize = numberOfUsers;
    free(onlineStatus);
    return mentions;
}
