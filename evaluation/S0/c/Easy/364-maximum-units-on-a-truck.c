// Source: https://leetcode.com/problems/maximum-units-on-a-truck/   |   Difficulty: Easy
//
// Problem Description:
// You are assigned to put some amount of boxes onto one truck. You are given a 2D array boxTypes, where boxTypes[i] = [numberOfBoxesi, numberOfUnitsPerBoxi]:
//
//
// 	numberOfBoxesi is the number of boxes of type i.
// 	numberOfUnitsPerBoxi is the number of units in each box of the type i.
//
//
// You are also given an integer truckSize, which is the maximum number of boxes that can be put on the truck. You can choose any boxes to put on the truck as long as the number of boxes does not exceed truckSize.
//
// Return the maximum total number of units that can be put on the truck.
//
// Example:
// Input: boxTypes = [[1,3],[2,2],[3,1]], truckSize = 4
// Output: 8
// Explanation: There are:
// - 1 box of the first type that contains 3 units.
// - 2 boxes of the second type that contain 2 units each.
// - 3 boxes of the third type that contain 1 unit each.
// You can take all the boxes of the first and second types, and one box of the third type.
// The total number of units will be = (1 * 3) + (2 * 2) + (1 * 1) = 8.
//
// Constraints:
// 1 <= boxTypes.length <= 1000
// 	1 <= numberOfBoxesi, numberOfUnitsPerBoxi <= 1000
// 	1 <= truckSize <= 106
//

int maximumUnits(int** boxTypes, int boxTypesSize, int* boxTypesColSize, int truckSize) {
    // Sort boxTypes by numberOfUnitsPerBox in descending order
    for (int i = 0; i < boxTypesSize - 1; i++) {
        for (int j = 0; j < boxTypesSize - i - 1; j++) {
            if (boxTypes[j][1] < boxTypes[j + 1][1]) {
                int* temp = boxTypes[j];
                boxTypes[j] = boxTypes[j + 1];
                boxTypes[j + 1] = temp;
            }
        }
    }

    int totalUnits = 0;
    for (int i = 0; i < boxTypesSize && truckSize > 0; i++) {
        int boxesToTake = boxTypes[i][0] < truckSize ? boxTypes[i][0] : truckSize;
        totalUnits += boxesToTake * boxTypes[i][1];
        truckSize -= boxesToTake;
    }

    return totalUnits;      
}
