# Day 22, Problem 3: Spell Checker

## Problem Statement
Build a spell checker that finds similar words to a given misspelled word. Should suggest corrections based on edit distance.

## Key Concepts

### Edit Distance (Levenshtein Distance)
Minimum number of single-character edits (insert, delete, replace) needed to transform one word into another.

```
"cat" → "car"  : 1 operation (replace 't' with 'r')
"kitten" → "sitting" : 3 operations
  kitten → sitten (replace 'k' → 's')
  sitten → sittin (replace 'e' → 'i')
  sittin → sitting (insert 'g')
```

### Trie + Edit Distance Approach
- Store dictionary words in Trie
- Use DFS with edit distance calculation
- Prune branches that exceed distance threshold
- Return words within edit distance threshold sorted by similarity

## Approach

1. **Build Trie**: Insert all dictionary words
2. **DFS Search**: Starting from root, explore paths
3. **Calculate Edit Distance**: Track edit operations as you traverse
4. **Prune Early**: Skip branches where distance already exceeds threshold
5. **Collect Results**: Gather words within acceptable distance
6. **Sort by Distance**: Return closest matches first

## Example Walkthrough

### Input:
```
Dictionary: ["cat", "car", "card", "care", "dog", "bat"]
Misspelled: "cate"
Threshold: 1 edit
```

### Process:
1. Build Trie with dictionary words
2. Search for words similar to "cate"
3. Traverse Trie while tracking edit distance:
   - "cat": distance = 1 (delete 'e' from "cate")
   - "car": distance = 2 (replace 't'→'r', delete 'e')
   - "card": distance = 3 (replace 't'→'r', delete 'e', insert 'd')
4. Filter by threshold = 1
5. Results: ["cat"]

### Edit Distance Computation:
```
For "cate" vs "cat":
- Match 'c': exact match
- Match 'a': exact match  
- Mismatch 't' vs 'e': 1 edit needed (replace)
- Remaining 'e' in "cate": 1 deletion needed
Total: 1 edit (delete 'e')
```

## Time & Space Complexity

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| Build Trie | O(n*m) | n words, m avg length |
| Edit distance (DP) | O(m*k) | m = word len, k = dict len |
| Search with pruning | O(m*k) | m = word len, k = nodes visited |
| **Total** | **O(n*m + m*k)** | Depends on threshold |

## Dynamic Programming for Edit Distance

```
DP[i][j] = edit distance between first i chars of word1 and first j chars of word2

Base cases:
- DP[0][j] = j (j insertions)
- DP[i][0] = i (i deletions)

Recurrence:
- If word1[i-1] == word2[j-1]: DP[i][j] = DP[i-1][j-1]
- Else: DP[i][j] = 1 + min(DP[i-1][j], DP[i][j-1], DP[i-1][j-1])
  - DP[i-1][j] + 1: delete from word1
  - DP[i][j-1] + 1: insert to word1
  - DP[i-1][j-1] + 1: replace
```

## Optimizations

1. **Pruning**: Skip DFS branches early if distance exceeds threshold
2. **Bidirectional Search**: Search from both word and dictionary simultaneously
3. **Character-level Filtering**: Quick rejection of words with different character sets
4. **Phonetic Similarity**: Combine edit distance with phonetic algorithms (Soundex)

## Questions to Ask Yourself

- How would you optimize if distance threshold is 1 or 2?
- Can you combine Trie pruning with DP optimization?
- How does edit distance relate to user typing errors?
- What about case sensitivity and special characters?

## Related Problems
- Edit Distance (LeetCode 72)
- Word Ladder problems
- Similar string matching
- Autocorrect systems
