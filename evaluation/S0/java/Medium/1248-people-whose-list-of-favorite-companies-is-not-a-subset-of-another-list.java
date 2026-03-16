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

class Solution {
    public List<Integer> peopleIndexes(List<List<String>> favoriteCompanies) {
        List<Integer> result = new ArrayList<>();
        int n = favoriteCompanies.size();
        List<Set<String>> companySets = new ArrayList<>();

        // Convert each list of favorite companies to a set for easier subset checking
        for (List<String> companies : favoriteCompanies) {
            companySets.add(new HashSet<>(companies));
        }

        // Check each person's favorite companies against all others
        for (int i = 0; i < n; i++) {
            boolean isSubset = false;
            Set<String> currentSet = companySets.get(i);

            for (int j = 0; j < n; j++) {
                if (i != j) {
                    Set<String> otherSet = companySets.get(j);
                    if (otherSet.containsAll(currentSet)) {
                        isSubset = true;
                        break;
                    }
                }
            }

            // If the current set is not a subset of any other, add its index to the result
            if (!isSubset) {
                result.add(i);
            }
        }

        return result;          
    }
}
