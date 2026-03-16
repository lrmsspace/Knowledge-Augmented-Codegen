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
// - kth-largest-element-in-an-array (heap, array, heap-select)
//   • When to use: Use this when you need to find the k-th largest (or smallest) element in an unsorted array efficiently without fully sorting it. It is particularly effective when k is much smaller than N.
//   • Idea: This algorithm uses a min-heap of size k to store the k largest elements encountered so far. It iterates through the array, comparing each element with the heap's minimum; if larger, it replaces the minimum, resulting in O(N log K) time complexity and O(K) space complexity.
//   • Invariants: The min-heap always contains at most k elements.; Every element in the min-heap is greater than or equal to any element that has been processed and discarded.
//   • Tips: Use a min-heap to find the k-th largest element, and a max-heap for the k-th smallest.; Initialize the heap with the first k elements from the input array.
//   • Pitfalls: Incorrectly using a max-heap when trying to find the k-th largest element.; Failing to handle edge cases such as k=1 or k equal to the array's length.
// - Scheduling jobs on two machines (array, number, simulation, enumeration)
//   • When to use: Use when determining the optimal sequence of jobs to minimize the total completion time (makespan) on two machines, with a fixed processing order (machine 1 then machine 2) for all jobs.
//   • Idea: This problem involves ordering N jobs, each with two processing times (one for each machine), to minimize the overall makespan. Johnson's rule provides an optimal greedy solution for this specific two-machine flow shop problem in O(N log N) or O(N) time.
//   • Invariants: All jobs processed so far maintain the optimal relative order determined by Johnson's rule.; The current makespan is the minimum possible for the jobs already scheduled.
//   • Tips: Sort jobs based on Johnson's rule criteria: jobs with min(a_i, b_i).; Prioritize jobs with shorter machine 1 times or longer machine 2 times for early scheduling.
//   • Pitfalls: Applying Johnson's rule to problems with more than two machines, where it is not optimal.; Incorrectly sorting jobs within the two partitioned sets.
// - The Inclusion-Exclusion Principle (array, number, counting, sieve)
//   • When to use: Use when direct counting of elements satisfying specific conditions is difficult due to overlaps, and you need to find the count of elements satisfying at least one, exactly k, or none of several properties.
//   • Idea: The Inclusion-Exclusion Principle counts the size of a union of sets by alternately adding and subtracting the sizes of intersections of increasing numbers of sets. Its complexity is often exponential in the number of properties.
//   • Invariants: At the start of processing subsets of size k, the running total correctly accounts for all intersections of size less than k.; For every element x, its contribution to the total sum is 1 if it satisfies the target condition, and 0 otherwise.
//   • Tips: Clearly define the properties (P1, P2, ..., Pn) for which elements are counted.; Systematically calculate the sizes of all relevant intersections of properties.
//   • Pitfalls: Incorrectly defining the properties or the universe of elements being counted.; Errors in calculating the sizes of specific intersections of properties.
//
// Notes:
// - Keep the given function signature unchanged.
// - Use standard C++ only; do NOT rely on non-standard extensions or platform-specific APIs.
// - Do not change input/output formats or return value semantics.
// - Conformance: Prefer modern standard C++ (C++11/14/17) features that are portable; avoid compiler-specific extensions (e.g., __int128 unless necessary and supported).
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

class Solution {
public:
    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
        vector<int> mentions(numberOfUsers, 0);
        vector<int> onlineUntil(numberOfUsers, 0); // timestamp until which each user is offline

        for (const auto& event : events) {
            const string& type = event[0];
            int timestamp = stoi(event[1]);

            if (type == "OFFLINE") {
                int userId = stoi(event[2].substr(2)); // extract id from "id<number>"
                onlineUntil[userId] = timestamp + 60; // user goes offline for 60 time units
            } else if (type == "MESSAGE") {
                const string& mentionsStr = event[2];
                if (mentionsStr == "ALL") {
                    for (int i = 0; i < numberOfUsers; ++i) {
                        if (timestamp >= onlineUntil[i]) {
                            mentions[i]++;
                        }
                    }
                } else if (mentionsStr == "HERE") {
                    for (int i = 0; i < numberOfUsers; ++i) {
                        if (timestamp >= onlineUntil[i]) {
                            mentions[i]++;
                        }
                    }
                } else {
                    size_t pos = 0;
                    size_t nextPos;
                    while (pos < mentionsStr.size()) {
                        nextPos = mentionsStr.find(' ', pos);
                        string token = (nextPos == string::npos) ? mentionsStr.substr(pos) : mentionsStr.substr(pos, nextPos - pos);
                        if (token.substr(0, 2) == "id") {
                            int userId = stoi(token.substr(2));
                            if (timestamp >= onlineUntil[userId]) {
                                mentions[userId]++;
                            }
                        }
                        if (nextPos == string::npos) break;
                        pos = nextPos + 1;
                    }
                }
            }
        }

        return mentions;            
    }
};
