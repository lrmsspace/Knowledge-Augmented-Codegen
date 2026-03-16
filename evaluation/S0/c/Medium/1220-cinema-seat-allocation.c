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

int maxNumberOfFamilies(int n, int** reservedSeats, int reservedSeatsSize, int* reservedSeatsColSize) {
    // Use a hash map to store the reserved seats for each row
    // Each row can be represented by a 10-bit integer where each bit indicates whether a seat is reserved
    #define LEFT_MASK  0b00000011110000  // Seats 2,3,4,5
    #define MIDDLE_MASK 0b00001111000000 // Seats 4,5,6,7
    #define RIGHT_MASK 0b00111100000000  // Seats 6,7,8,9

    #define MAX_ROWS 10000
    int row_map[MAX_ROWS] = {0};
    int row_count = 0;

    for (int i = 0; i < reservedSeatsSize; i++) {
        int row = reservedSeats[i][0];
        int seat = reservedSeats[i][1];

        if (row_map[row] == 0) {
            row_count++;
        }

        // Mark the seat as reserved in the corresponding row
        row_map[row] |= (1 << seat);
    }

    int total_groups = (n - row_count) * 2; // Each unreserved row can accommodate 2 groups

    for (int i = 1; i <= MAX_ROWS; i++) {
        if (row_map[i] != 0) {
            int reserved = row_map[i];
            int groups_in_row = 0;

            // Check left block
            if ((reserved & LEFT_MASK) == 0) {
                groups_in_row++;
            }

            // Check right block
            if ((reserved & RIGHT_MASK) == 0) {
                groups_in_row++;
            }

            // Check middle block only if no groups were assigned yet
            if (groups_in_row == 0 && (reserved & MIDDLE_MASK) == 0) {
                groups_in_row++;
            }

            total_groups += groups_in_row;
        }
    }

    return total_groups;        
}
