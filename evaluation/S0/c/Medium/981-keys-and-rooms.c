// Source: https://leetcode.com/problems/keys-and-rooms/   |   Difficulty: Medium
//
// Problem Description:
// There are n rooms labeled from 0 to n - 1 and all the rooms are locked except for room 0. Your goal is to visit all the rooms. However, you cannot enter a locked room without having its key.
//
// When you visit a room, you may find a set of distinct keys in it. Each key has a number on it, denoting which room it unlocks, and you can take all of them with you to unlock the other rooms.
//
// Given an array rooms where rooms[i] is the set of keys that you can obtain if you visited room i, return true if you can visit all the rooms, or false otherwise.
//
// Example:
// Input: rooms = [[1],[2],[3],[]]
// Output: true
// Explanation: 
// We visit room 0 and pick up key 1.
// We then visit room 1 and pick up key 2.
// We then visit room 2 and pick up key 3.
// We then visit room 3.
// Since we were able to visit every room, we return true.
//
// Constraints:
// n == rooms.length
// 	2 <= n <= 1000
// 	0 <= rooms[i].length <= 1000
// 	1 <= sum(rooms[i].length) <= 3000
// 	0 <= rooms[i][j] < n
// 	All the values of rooms[i] are unique.
//

bool canVisitAllRooms(int** rooms, int roomsSize, int* roomsColSize) {
    bool visited[roomsSize];
    for (int i = 0; i < roomsSize; i++) {
        visited[i] = false;
    }
    
    visited[0] = true;
    int stack[roomsSize];
    int stackSize = 0;
    stack[stackSize++] = 0;
    
    while (stackSize > 0) {
        int room = stack[--stackSize];
        
        for (int i = 0; i < roomsColSize[room]; i++) {
            int key = rooms[room][i];
            if (!visited[key]) {
                visited[key] = true;
                stack[stackSize++] = key;
            }
        }
    }
    
    for (int i = 0; i < roomsSize; i++) {
        if (!visited[i]) {
            return false;
        }
    }
    
    return true;        
}
