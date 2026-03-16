// Source: https://leetcode.com/problems/apple-redistribution-into-boxes/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array apple of size n and an array capacity of size m.
//
// There are n packs where the ith pack contains apple[i] apples. There are m boxes as well, and the ith box has a capacity of capacity[i] apples.
//
// Return the minimum number of boxes you need to select to redistribute these n packs of apples into boxes.
//
// Note that, apples from the same pack can be distributed into different boxes.
//
// Example:
// Input: apple = [1,3,2], capacity = [4,3,1,5,2]
// Output: 2
// Explanation: We will use boxes with capacities 4 and 5.
// It is possible to distribute the apples as the total capacity is greater than or equal to the total number of apples.
//
// Constraints:
// 1 <= n == apple.length <= 50
// 	1 <= m == capacity.length <= 50
// 	1 <= apple[i], capacity[i] <= 50
// 	The input is generated such that it's possible to redistribute packs of apples into boxes.
//

class Solution {
public:
    int minimumBoxes(vector<int>& apple, vector<int>& capacity) {
        int totalApples = 0;
        for (int a : apple) {
            totalApples += a;
        }

        sort(capacity.rbegin(), capacity.rend());

        int boxesUsed = 0;
        int currentCapacity = 0;

        for (int cap : capacity) {
            currentCapacity += cap;
            boxesUsed++;
            if (currentCapacity >= totalApples) {
                return boxesUsed;
            }
        }

        return boxesUsed; // This line should never be reached due to problem constraints           
    }
};
