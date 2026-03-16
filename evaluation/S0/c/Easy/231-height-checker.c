// Source: https://leetcode.com/problems/height-checker/   |   Difficulty: Easy
//
// Problem Description:
// A school is trying to take an annual photo of all the students. The students are asked to stand in a single file line in non-decreasing order by height. Let this ordering be represented by the integer array expected where expected[i] is the expected height of the ith student in line.
//
// You are given an integer array heights representing the current order that the students are standing in. Each heights[i] is the height of the ith student in line (0-indexed).
//
// Return the number of indices where heights[i] != expected[i].
//
// Example:
// Input: heights = [1,1,4,2,1,3]
// Output: 3
// Explanation: 
// heights:  [1,1,4,2,1,3]
// expected: [1,1,1,2,3,4]
// Indices 2, 4, and 5 do not match.
//
// Constraints:
// 1 <= heights.length <= 100
// 	1 <= heights[i] <= 100
//

int heightChecker(int* heights, int heightsSize) {
    int count[101] = {0};
    for (int i = 0; i < heightsSize; i++) {
        count[heights[i]]++;
    }
    
    int result = 0;
    int index = 0;
    
    for (int height = 1; height <= 100; height++) {
        while (count[height] > 0) {
            if (heights[index] != height) {
                result++;
            }
            index++;
            count[height]--;
        }
    }
    
    return result;      
}
