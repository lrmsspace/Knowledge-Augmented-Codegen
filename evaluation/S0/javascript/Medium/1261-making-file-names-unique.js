// Source: https://leetcode.com/problems/making-file-names-unique/   |   Difficulty: Medium
//
// Problem Description:
// Given an array of strings names of size n. You will create n folders in your file system such that, at the ith minute, you will create a folder with the name names[i].
//
// Since two files cannot have the same name, if you enter a folder name that was previously used, the system will have a suffix addition to its name in the form of (k), where, k is the smallest positive integer such that the obtained name remains unique.
//
// Return an array of strings of length n where ans[i] is the actual name the system will assign to the ith folder when you create it.
//
// Example:
// Input: names = ["pes","fifa","gta","pes(2019)"]
// Output: ["pes","fifa","gta","pes(2019)"]
// Explanation: Let's see how the file system creates folder names:
// "pes" --> not assigned before, remains "pes"
// "fifa" --> not assigned before, remains "fifa"
// "gta" --> not assigned before, remains "gta"
// "pes(2019)" --> not assigned before, remains "pes(2019)"
//
// Constraints:
// 1 <= names.length <= 5 * 104
// 	1 <= names[i].length <= 20
// 	names[i] consists of lowercase English letters, digits, and/or round brackets.
//

/**
 * @param {string[]} names
 * @return {string[]}
 */
var getFolderNames = function(names) {
    
    const nameCount = new Map();
    const result = [];

    for (const name of names) {
        if (!nameCount.has(name)) {
            nameCount.set(name, 0);
            result.push(name);
        }
        else {
            let k = nameCount.get(name) + 1;
            let newName = `${name}(${k})`;
            while (nameCount.has(newName)) {
                k++;
                newName = `${name}(${k})`;
            }
            nameCount.set(name, k);
            nameCount.set(newName, 0);
            result.push(newName);
        }
    }

    return result;      
};
