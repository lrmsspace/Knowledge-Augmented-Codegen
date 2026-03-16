// Source: https://leetcode.com/problems/minimum-number-of-moves-to-seat-everyone/   |   Difficulty: Easy
//
// Problem Description:
// There are n availabe seats and n students standing in a room. You are given an array seats of length n, where seats[i] is the position of the ith seat. You are also given the array students of length n, where students[j] is the position of the jth student.
//
// You may perform the following move any number of times:
//
//
// 	Increase or decrease the position of the ith student by 1 (i.e., moving the ith student from position x to x + 1 or x - 1)
//
//
// Return the minimum number of moves required to move each student to a seat such that no two students are in the same seat.
//
// Note that there may be multiple seats or students in the same position at the beginning.
//
// Example:
// Input: seats = [3,1,5], students = [2,7,4]
// Output: 4
// Explanation: The students are moved as follows:
// - The first student is moved from position 2 to position 1 using 1 move.
// - The second student is moved from position 7 to position 5 using 2 moves.
// - The third student is moved from position 4 to position 3 using 1 move.
// In total, 1 + 2 + 1 = 4 moves were used.
//
// Constraints:
// n == seats.length == students.length
// 	1 <= n <= 100
// 	1 <= seats[i], students[j] <= 100
//

int minMovesToSeat(int* seats, int seatsSize, int* students, int studentsSize) {
    // Sort both arrays to minimize the total distance
    for (int i = 0; i < seatsSize - 1; i++) {
        for (int j = 0; j < seatsSize - i - 1; j++) {
            if (seats[j] > seats[j + 1]) {
                int temp = seats[j];
                seats[j] = seats[j + 1];
                seats[j + 1] = temp;
            }
            if (students[j] > students[j + 1]) {
                int temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }

    int totalMoves = 0;
    for (int i = 0; i < seatsSize; i++) {
        totalMoves += abs(seats[i] - students[i]);
    }

    return totalMoves;      
}
