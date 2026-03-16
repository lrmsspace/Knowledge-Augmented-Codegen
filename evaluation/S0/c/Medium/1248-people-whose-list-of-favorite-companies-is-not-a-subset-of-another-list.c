// Source: https://leetcode.com/problems/people-whose-list-of-favorite-companies-is-not-a-subset-of-another-list/   |   Difficulty: Medium
//
// Problem Description:
// Given the array favoriteCompanies where favoriteCompanies[i] is the list of favorites companies for the ith person (indexed from 0).
//
// Return the indices of people whose list of favorite companies is not a subset of any other list of favorites companies. You must return the indices in increasing order.
//
// Example:
// Input: favoriteCompanies = [["leetcode","google","facebook"],["google","microsoft"],["google","facebook"],["google"],["amazon"]]
// Output: [0,1,4] 
// Explanation: 
// Person with index=2 has favoriteCompanies[2]=["google","facebook"] which is a subset of favoriteCompanies[0]=["leetcode","google","facebook"] corresponding to the person with index 0. 
// Person with index=3 has favoriteCompanies[3]=["google"] which is a subset of favoriteCompanies[0]=["leetcode","google","facebook"] and favoriteCompanies[1]=["google","microsoft"]. 
// Other lists of favorite companies are not a subset of another list, therefore, the answer is [0,1,4].
//
// Constraints:
// 1 <= favoriteCompanies.length <= 100
// 	1 <= favoriteCompanies[i].length <= 500
// 	1 <= favoriteCompanies[i][j].length <= 20
// 	All strings in favoriteCompanies[i] are distinct.
// 	All lists of favorite companies are distinct, that is, If we sort alphabetically each list then favoriteCompanies[i] != favoriteCompanies[j].
// 	All strings consist of lowercase English letters only.
//

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* peopleIndexes(char*** favoriteCompanies, int favoriteCompaniesSize, int* favoriteCompaniesColSize, int* returnSize) {
    int* result = (int*)malloc(favoriteCompaniesSize * sizeof(int));
    *returnSize = 0;

    for (int i = 0; i < favoriteCompaniesSize; i++) {
        int isSubset = 0;
        for (int j = 0; j < favoriteCompaniesSize; j++) {
            if (i != j) {
                int allFound = 1;
                for (int k = 0; k < favoriteCompaniesColSize[i]; k++) {
                    int found = 0;
                    for (int l = 0; l < favoriteCompaniesColSize[j]; l++) {
                        if (strcmp(favoriteCompanies[i][k], favoriteCompanies[j][l]) == 0) {
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        allFound = 0;
                        break;
                    }
                }
                if (allFound) {
                    isSubset = 1;
                    break;
                }
            }
        }
        if (!isSubset) {
            result[(*returnSize)++] = i;
        }
    }

    return result;      
}
