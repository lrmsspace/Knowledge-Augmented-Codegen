// Source: https://leetcode.com/problems/cinema-seat-allocation/   |   Difficulty: Medium
//
// Problem Description:
// A cinema has n rows of seats, numbered from 1 to n and there are ten seats in each row, labelled from 1 to 10 as shown in the figure above.
//
// Given the array reservedSeats containing the numbers of seats already reserved, for example, reservedSeats[i] = [3,8] means the seat located in row 3 and labelled with 8 is already reserved.
//
// Return the maximum number of four-person groups you can assign on the cinema seats. A four-person group occupies four adjacent seats in one single row. Seats across an aisle (such as [3,3] and [3,4]) are not considered to be adjacent, but there is an exceptional case on which an aisle split a four-person group, in that case, the aisle split a four-person group in the middle, which means to have two people on each side.
//
// Example:
// Input: n = 3, reservedSeats = [[1,2],[1,3],[1,8],[2,6],[3,1],[3,10]]
// Output: 4
// Explanation: The figure above shows the optimal allocation for four groups, where seats mark with blue are already reserved and contiguous seats mark with orange are for one group.
//
// Constraints:
// 1 <= n <= 10^9
// 	1 <= reservedSeats.length <= min(10*n, 10^4)
// 	reservedSeats[i].length == 2
// 	1 <= reservedSeats[i][0] <= n
// 	1 <= reservedSeats[i][1] <= 10
// 	All reservedSeats[i] are distinct.
//

class Solution {
public:
    int maxNumberOfFamilies(int n, vector<vector<int>>& reservedSeats) {
        unordered_map<int, int> seatMap;
        for (const auto& seat : reservedSeats) {
            int row = seat[0];
            int col = seat[1];
            seatMap[row] |= (1 << (col - 1));
        }

        int totalFamilies = 0;
        for (const auto& entry : seatMap) {
            int seats = entry.second;
            int familiesInRow = 0;

            // Check left block (seats 2,3,4,5)
            if ((seats & 0b00000011110) == 0) {
                familiesInRow++;
                seats |= 0b00000011110; // Mark these seats as occupied
            }

            // Check right block (seats 6,7,8,9)
            if ((seats & 0b01111000000) == 0) {
                familiesInRow++;
                seats |= 0b01111000000; // Mark these seats as occupied
            }

            // Check middle block (seats 4,5,6,7)
            if (familiesInRow == 0 && (seats & 0b00011110000) == 0) {
                familiesInRow++;
            }

            totalFamilies += familiesInRow;
        }

        // Each row without any reserved seats can accommodate 2 families
        totalFamilies += (n - seatMap.size()) * 2;

        return totalFamilies;           
    }
};
