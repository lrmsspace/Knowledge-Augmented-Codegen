// Source: https://leetcode.com/problems/jump-game-iv/   |   Difficulty: Hard
//
// Problem Description:
// Given an array of integers arr, you are initially positioned at the first index of the array.
//
// In one step you can jump from index i to index:
//
//
// 	i + 1 where: i + 1 < arr.length.
// 	i - 1 where: i - 1 >= 0.
// 	j where: arr[i] == arr[j] and i != j.
//
//
// Return the minimum number of steps to reach the last index of the array.
//
// Notice that you can not jump outside of the array at any time.
//
// Example:
// Input: arr = [100,-23,-23,404,100,23,23,23,3,404]
// Output: 3
// Explanation: You need three jumps from index 0 --> 4 --> 3 --> 9. Note that index 9 is the last index of the array.
//
// Constraints:
// 1 <= arr.length <= 5 * 104
// 	-108 <= arr[i] <= 108
//

class Solution {
public:
    int minJumps(vector<int>& arr) {
        int n = arr.size();
        unordered_map<int, vector<int>> valueIndices;
        for (int i = 0; i < n; ++i) {
            valueIndices[arr[i]].push_back(i);
        }
        
        vector<bool> visited(n, false);
        visited[0] = true;
        
        queue<int> q;
        q.push(0);
        
        int steps = 0;
        
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                int index = q.front();
                q.pop();
                
                if (index == n - 1) {
                    return steps;
                }
                
                // Jump to index + 1
                if (index + 1 < n && !visited[index + 1]) {
                    visited[index + 1] = true;
                    q.push(index + 1);
                }
                
                // Jump to index - 1
                if (index - 1 >= 0 && !visited[index - 1]) {
                    visited[index - 1] = true;
                    q.push(index - 1);
                }
                
                // Jump to all indices with the same value
                if (valueIndices.count(arr[index])) {
                    for (int nextIndex : valueIndices[arr[index]]) {
                        if (nextIndex != index && !visited[nextIndex]) {
                            visited[nextIndex] = true;
                            q.push(nextIndex);
                        }
                    }
                    // Clear the list to prevent future redundant checks
                    valueIndices.erase(arr[index]);
                }
            }
            ++steps;
        }
        
        return -1; // Should never reach here for valid input           
    }
};
