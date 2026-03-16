// Source: https://leetcode.com/problems/couples-holding-hands/   |   Difficulty: Hard
//
// Problem Description:
// There are n couples sitting in 2n seats arranged in a row and want to hold hands.
//
// The people and seats are represented by an integer array row where row[i] is the ID of the person sitting in the ith seat. The couples are numbered in order, the first couple being (0, 1), the second couple being (2, 3), and so on with the last couple being (2n - 2, 2n - 1).
//
// Return the minimum number of swaps so that every couple is sitting side by side. A swap consists of choosing any two people, then they stand up and switch seats.
//
// Example:
// Input: row = [0,2,1,3]
// Output: 1
// Explanation: We only need to swap the second (row[1]) and third (row[2]) person.
//
// Constraints:
// 2n == row.length
// 	2 <= n <= 30
// 	n is even.
// 	0 <= row[i] < 2n
// 	All the elements of row are unique.
//

class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        int n = row.size();
        vector<int> pos(n);
        for (int i = 0; i < n; i++) {
            pos[row[i]] = i;
        }
        
        int swaps = 0;
        for (int i = 0; i < n; i += 2) {
            int first = row[i];
            int second = first ^ 1;  // Partner of the first person
            
            if (row[i + 1] != second) {
                // Swap needed
                int secondPos = pos[second];
                
                // Perform swap in row
                swap(row[i + 1], row[secondPos]);
                
                // Update positions
                pos[row[secondPos]] = secondPos;
                pos[row[i + 1]] = i + 1;
                
                swaps++;
            }
        }
        
        return swaps;           
    }
};
