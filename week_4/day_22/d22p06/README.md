# Day 22, Problem 6: Word Break Problem

## Problem Statement
Determine if a string can be segmented into words that exist in a given dictionary. Extended version: reconstruct the segmentation.

## Key Concepts

### Two Variants

**Variant 1: Boolean Check**
```
String: "catsandogs"
Dictionary: {"cats", "cat", "and", "sand", "dogs"}

Can be segmented? YES
Segmentation: "cats" + "and" + "dogs"
```

**Variant 2: All Segmentations**
```
String: "catsandcatsdog"
Dictionary: {"cat", "cats", "and", "sand", "dog", "catsdog"}

All segmentations:
1. "cat" + "sand" + "cat" + "s" + "dog" (NOT valid, 's' not in dict)
2. "cats" + "and" + "cats" + "dog"
3. "catsandcatsdog"
```

## Approach 1: Dynamic Programming (Bottom-up)

```
DP[i] = true if s[0:i] can be segmented

Base case: DP[0] = true (empty string)

Recurrence:
For i from 1 to n:
  For j from 0 to i-1:
    If DP[j] == true AND s[j:i] in dictionary:
      DP[i] = true
      Break
```

## Approach 2: Trie + DFS (Top-down with Memoization)

```
1. Build Trie of dictionary words
2. DFS from start of string
3. At each position, check if we can form a valid word from Trie
4. If word found, recurse on remaining string
5. Use memoization to avoid redundant computations
```

## Example Walkthrough - DP Approach

### Input:
```
String: "applepenapple"
Dictionary: {"apple", "pen", "ap", "appl", "le", "penapple"}
```

### Process:
```
String: a p p l e p e n a p p l e
Index:  0 1 2 3 4 5 6 7 8 9 10 11 12

DP[0] = true (base case)

DP[1]: s[0:1] = "a"     → Not in dict → DP[1] = false
DP[2]: s[0:2] = "ap"    → In dict, DP[0]=true → DP[2] = true
DP[3]: s[0:3] = "app"   → Not in dict
       s[2:3] = "p"     → Not in dict → DP[3] = false
DP[4]: s[0:4] = "appl"  → In dict, DP[0]=true → DP[4] = true
DP[5]: s[0:5] = "apple" → In dict, DP[0]=true → DP[5] = true
DP[6]: s[5:6] = "p"     → Not in dict
       s[4:6] = "ep"    → Not in dict
       ... continuing ...
       → DP[6] = false
DP[7]: s[5:7] = "pe"    → Not in dict
       ... continuing ...
       → DP[7] = false
DP[8]: s[5:8] = "pen"   → In dict, DP[5]=true → DP[8] = true
...continuing...
DP[12]: Eventually checks s[9:12] = "app", s[8:12] = "apen", etc.
        s[11:12] = "e"  → Not in dict
        ... → DP[12] = false

Final: DP[13] → check previous states
       s[5:13] = "penapple" → In dict, DP[5]=true → DP[13] = true

Answer: YES, string can be segmented
```

## Example Walkthrough - Trie + DFS Approach

### Trie Structure:
```
Dictionary: {"apple", "pen", "ap", "le"}

        root
       / |  \
      a  p  (others)
      |
      p
     / \
    p   l
   /     \
  l       e(word)
  |
  e(word)
```

### DFS Process:
```
dfs("applepenapple", 0):
  Traverse Trie: 'a' → 'p' → 'p' → 'l' → 'e' (found "apple")
  Recurse: dfs(remaining="penapple", 5)
  
  dfs("penapple", 5):
    Traverse Trie: 'p' → 'e' → 'n' (no match, backtrack)
    Traverse: 'p' → 'e' → 'n' → 'a' → 'p' → 'p' → 'l' → 'e' 
              (found "penapple" but not in our dict example)
    Actually: Can't find match, return false (or try other paths)

Alternative path through DP would succeed as shown above.
```

## Time & Space Complexity

### DP Approach:
| Metric | Complexity | Notes |
|--------|-----------|-------|
| Time | O(n² * m) | n = string length, m = avg word length |
| Space | O(n) | DP array of size n |
| Word lookup | O(m) | String comparison per word |

### Trie + DFS Approach:
| Metric | Complexity | Notes |
|--------|-----------|-------|
| Time | O(n² * L) | L = Trie depth (word length) |
| Space | O(n + k*m) | n = recursion depth, k = words, m = avg length |
| Trie operations | O(L) | Follow pointers, not string comparison |

## Optimization Techniques

1. **Trie over HashMap**: O(m) per character vs O(m) per whole word comparison
2. **Early termination**: Stop if substring too long for any dictionary word
3. **Memoization**: Cache results for substrings already evaluated
4. **Word length filtering**: Only check lengths that exist in dictionary

## Reconstruction

To get actual segmentation (not just boolean):

```
1. Use DP but also track parent pointers
2. Or use Trie with DFS that returns full path

Path tracking:
- DP[i] stores not just true/false
- Also stores the word used: DP[i] = (true, "word_ending_at_i")
- Backtrack from end to start to reconstruct

Backtracking from DP[13]:
DP[13] came from DP[5] + "penapple" (if it were in dict)
DP[5] came from DP[0] + "apple"
Path: ["apple", "penapple"]
```

## Questions to Ask Yourself

- Can you optimize using a Trie vs HashMap?
- How would you return all possible segmentations?
- What if you want to minimize number of words used?
- Can you handle overlapping dictionary words efficiently?

## Related Problems
- Word Break I & II (LeetCode 139, 140)
- Concatenated Words
- Regex matching
- Sentence segmentation
