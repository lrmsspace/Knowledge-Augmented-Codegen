// Source: https://leetcode.com/problems/boats-to-save-people/   |   Difficulty: Medium
//
// Problem Description:
// You are given an array people where people[i] is the weight of the ith person, and an infinite number of boats where each boat can carry a maximum weight of limit. Each boat carries at most two people at the same time, provided the sum of the weight of those people is at most limit.
//
// Return the minimum number of boats to carry every given person.
//
// Example:
// Input: people = [1,2], limit = 3
// Output: 1
// Explanation: 1 boat (1, 2)
//
// Constraints:
// 1 <= people.length <= 5 * 104
// 	1 <= people[i] <= limit <= 3 * 104
//

int numRescueBoats(int* people, int peopleSize, int limit) {
    // Sort the array of people's weights
    qsort(people, peopleSize, sizeof(int), (int (*)(const void*, const void*))strcmp);

    int left = 0;                     // Pointer to the lightest person
    int right = peopleSize - 1;      // Pointer to the heaviest person
    int boats = 0;                   // Counter for boats used

    while (left <= right) {
        // If the lightest and heaviest person can share a boat
        if (people[left] + people[right] <= limit) {
            left++;  // Move to the next lightest person
        }
        // Always move the pointer for the heaviest person
        right--;
        boats++;  // One boat is used
    }

    return boats;  // Return the total number of boats used     
}
