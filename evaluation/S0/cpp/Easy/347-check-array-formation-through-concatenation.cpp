// Source: https://leetcode.com/problems/check-array-formation-through-concatenation/   |   Difficulty: Easy
//
// Problem Description:
// You are given an array of distinct integers arr and an array of integer arrays pieces, where the integers in pieces are distinct. Your goal is to form arr by concatenating the arrays in pieces in any order. However, you are not allowed to reorder the integers in each array pieces[i].
//
// Return true if it is possible to form the array arr from pieces. Otherwise, return false.
//
// Example:
// Input: arr = [15,88], pieces = [[88],[15]]
// Output: true
// Explanation: Concatenate [15] then [88]
//
// Constraints:
// 1 <= pieces.length <= arr.length <= 100
// 	sum(pieces[i].length) == arr.length
// 	1 <= pieces[i].length <= arr.length
// 	1 <= arr[i], pieces[i][j] <= 100
// 	The integers in arr are distinct.
// 	The integers in pieces are distinct (i.e., If we flatten pieces in a 1D array, all the integers in this array are distinct).
//

class Solution {
public:
    bool canFormArray(vector<int>& arr, vector<vector<int>>& pieces) {
        unordered_map<int, vector<int>> pieceMap;
        for (const auto& piece : pieces) {
            pieceMap[piece[0]] = piece;
        }

        int i = 0;
        while (i < arr.size()) {
            if (pieceMap.find(arr[i]) == pieceMap.end()) {
                return false;
            }

            const auto& piece = pieceMap[arr[i]];
            for (int num : piece) {
                if (arr[i] != num) {
                    return false;
                }
                i++;
            }
        }

        return true;            
    }
};
