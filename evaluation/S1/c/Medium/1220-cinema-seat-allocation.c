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
// Helpful references (internal KB):
// - Submask Enumeration
//  (number, bitset, enumeration, bitmask-dp)
//   • When to use: When a problem requires iterating through all possible submasks for each given mask. This is common in bitmask dynamic programming problems where relationships between a set and its subsets are crucial.
//   • Idea: This algorithm efficiently iterates through all submasks for every mask from 0 to 2^N - 1. It has a total time complexity of O(3^N) for all masks and their submasks.
//   • Invariants: For a given `mask`, `submask` always represents a subset of `mask`.; Each `submask` is visited exactly once for its corresponding `mask`.
//   • Tips: The `submask = (submask - 1) & mask` trick is crucial for efficient iteration.; Ensure the outer loop iterates through all masks from 0 to 2^N - 1.
//   • Pitfalls: Forgetting the `& mask` part in the inner loop can lead to incorrect submasks or infinite loops.; Misunderstanding the O(3^N) total complexity, leading to Time Limit Exceeded for large N.
// - Dynamic Programming on Broken Profile. Problem "Parquet" (matrix, bitset, dp-2d, bitmask-dp)
//   • When to use: When problems involve tiling a grid or area with specific shapes, and the state can be represented by the 'profile' or boundary between processed and unprocessed cells, often using a bitmask.
//   • Idea: Dynamic Programming on Broken Profile is a technique used to solve tiling problems on grids by iterating through cells and maintaining the 'profile' of the boundary between filled and unfilled regions using a bitmask. This approach typically has a time complexity of O(N * M * 2^M) or O(N * M * 2^N), depending on the smaller dimension.
//   • Invariants: dp[row][mask] correctly stores the count of ways to tile the grid up to row-1, with mask representing the profile of row `row`.; All cells in rows 0 through `row-1` are completely and non-overlappingly tiled.
//   • Tips: Represent the profile as a bitmask where each bit indicates the state of a cell on the boundary.; Process the grid cell by cell, usually row by row, then column by column within a row.
//   • Pitfalls: Incorrectly defining the bitmask or its interpretation (e.g., which direction it represents).; Handling boundary conditions and edge cases for the grid dimensions.
// - Sparse Table (array, sparse-table, dp-2d)
//   • When to use: Use when you need to answer range queries, especially Range Minimum/Maximum Queries, on an immutable array very quickly. It is ideal for scenarios where the data does not change and query performance is critical.
//   • Idea: Sparse Table is a data structure that precomputes answers for all range queries of power-of-two lengths. It allows O(1) query time for idempotent operations like Range Minimum/Maximum Queries on a static array, with O(N log N) precomputation.
//   • Invariants: st[k][i] holds the result for the segment starting at index i with length 2^k.; For any k > 0, st[k][i] combines the results of two adjacent segments of length 2^(k-1).
//   • Tips: Precompute log2 values to find the largest power of two in O(1).; Best suited for idempotent operations like minimum, maximum, or GCD.
//   • Pitfalls: Does not support array updates; any modification invalidates the structure.; Inefficient for non-idempotent operations like range sum or XOR in O(1).
//
// Notes:
// - Keep the given function signature unchanged.
// - Use the C standard library only; no external packages.
// - Do not change input/output formats or return value semantics.
// - Conformance: ISO C (C89/C99/C11). Do NOT use GNU C extensions (nested functions, statement expressions, typeof, __auto_type, etc.). Avoid VLAs and non-standard builtins.
// - If you introduce any helper functions, include their full implementations in this file; no hidden helpers.

int maxNumberOfFamilies(int n, int** reservedSeats, int reservedSeatsSize, int* reservedSeatsColSize) {
    #define LEFT_MASK   0b0000001111000
    #define MIDDLE_MASK 0b0000111100000
    #define RIGHT_MASK  0b0011110000000

    #define FULL_MASK (LEFT_MASK | RIGHT_MASK)

    #define CAN_PLACE(mask, place_mask) (((mask) & (place_mask)) == 0)

    #define ROW_KEY(row) (row)

    #define INITIAL_FOUR_PER_ROW 2

    #define MIN(a, b) ((a) < (b) ? (a) : (b))

    #include <stdlib.h>

    typedef struct SeatNode {
        int row;
        int seat_mask;
        struct SeatNode* next;
    } SeatNode;

    #define HASH_MAP_SIZE 10007

    SeatNode* hash_map[HASH_MAP_SIZE] = {0};

    int hash_function(int row) {
        return row % HASH_MAP_SIZE;
    }

    for (int i = 0; i < reservedSeatsSize; ++i) {
        int row = reservedSeats[i][0];
        int seat = reservedSeats[i][1];

        int key = ROW_KEY(row);
        int hash_index = hash_function(key);

        SeatNode* node = hash_map[hash_index];
        while (node) {
            if (node->row == row) {
                node->seat_mask |= (1 << seat);
                break;
            }
            node = node->next;
        }
        if (!node) {
            SeatNode* new_node = (SeatNode*)malloc(sizeof(SeatNode));
            new_node->row = row;
            new_node->seat_mask = (1 << seat);
            new_node->next = hash_map[hash_index];
            hash_map[hash_index] = new_node;
        }
    }

    int total_groups = n * INITIAL_FOUR_PER_ROW;

    for (int i = 0; i < HASH_MAP_SIZE; ++i) {
        SeatNode* node = hash_map[i];
        while (node) {
            int reserved_mask = node->seat_mask;
            int can_place_count = 0;

            if (CAN_PLACE(reserved_mask, FULL_MASK)) {
                can_place_count = 2;
            } else if (CAN_PLACE(reserved_mask, LEFT_MASK) ||
                       CAN_PLACE(reserved_mask, MIDDLE_MASK) ||
                       CAN_PLACE(reserved_mask, RIGHT_MASK)) {
                can_place_count = 1;
            }

            total_groups -= (INITIAL_FOUR_PER_ROW - can_place_count);

            SeatNode* temp = node;
            node = node->next;
            free(temp);
        }
    }
    return total_groups;
}
