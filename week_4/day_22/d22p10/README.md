# Day 22, Problem 10: Concatenated Words

## Problem Statement
Find all words in a dictionary that can be formed by concatenating other words from the same dictionary.

## Key Concepts

### Problem Variants

**Variant 1: Simple concatenation**
```
Dictionary: ["cat", "cats", "catcats", "ratcatgoatcats"]

"catcats" = "cat" + "cats" ✓ (concatenated)
"cats" = not concatenated (only one word)
"ratcatgoatcats" = can't form from other words ✗

Result: ["catcats"]
```

**Variant 2: Multiple concatenations**
```
Dictionary: ["a", "b", "ab", "abc", "abcd"]

"ab" = "a" + "b" ✓
"abc" = "a" + "bc" (bc not in dict) ✗
       = "ab" + "c" (c not in dict) ✗
       → "abc" is not concatenated

"abcd" might = "ab" + "cd" (cd not in dict) ✗
```

## Approach: Trie + DFS + Recursion

```
1. Build Trie with all dictionary words
2. For each word:
   - Try to decompose it using other words
   - DFS to check if word can be formed
   - Count how many words used in decomposition
3. If word uses ≥ 2 dictionary words, it's concatenated
4. Return all such words
```

### Decomposition Check:

For word "catcats", check if it can be split:
```
c|atcats       → "c" not in dict
ca|tcats       → "ca" not in dict
cat|cats       → "cat" in dict, recurse on "cats"
                 → "cats" in dict (found!)
                 → "catcats" = "cat" + "cats" ✓

catc|ats       → "catc" not in dict
catca|ts       → "catca" not in dict
catcat|s       → "catcat" not in dict
catcats|       → "catcats" not in dict (can't recurse on empty)
```

## Example Walkthrough

### Input:
```
Dictionary: ["a", "b", "ab", "abc", "abcd", "abcde"]
```

### Process:

**Word "a":**
- Can't form from other words
- Count: 1 word used (only itself)
- Result: NOT concatenated

**Word "b":**
- Can't form from other words
- Count: 1
- Result: NOT concatenated

**Word "ab":**
- Split at 1: "a" + "b"
  - "a" in dict ✓
  - Recurse on "b"
  - "b" in dict ✓ (without using "ab")
- Count: 2 words ("a", "b")
- Result: CONCATENATED ✓

**Word "abc":**
- Split at 1: "a" + "bc"
  - "a" in dict ✓
  - Recurse on "bc" (not in dict) ✗
- Split at 2: "ab" + "c"
  - "ab" in dict ✓
  - Recurse on "c" (not in dict) ✗
- Result: NOT concatenated

**Word "abcd":**
- Split at 1: "a" + "bcd"
  - "a" in dict ✓
  - Recurse on "bcd" (check "bcd" against dict) → fail
- Split at 2: "ab" + "cd"
  - "ab" in dict ✓
  - Recurse on "cd" → fail
- Split at 3: "abc" + "d"
  - "abc" in dict ✓
  - Recurse on "d" → fail
- Result: NOT concatenated

**Word "abcde":**
- Split at 1: "a" + "bcde"
  - Recurse on "bcde" (doesn't match any pattern)
- Split at 2: "ab" + "cde"
  - Recurse on "cde" → fail
- Split at 3: "abc" + "de"
  - Recurse on "de" → fail
- ...
- Result: NOT concatenated

**Final Result: ["ab"]**

## Algorithm: Trie-based Word Decomposition

```
function canForm(word, trie, start, count):
  if start == len(word):
    return count > 1  # Must use at least 2 words
  
  node = trie.root
  for i from start to len(word)-1:
    char = word[i]
    if char not in node.children:
      return false
    node = node.children[char]
    
    if node.isWordEnd:
      # Found a word from start to i
      # Recurse on remaining part
      if canForm(word, trie, i+1, count+1):
        return true
  
  return false
```

## Time & Space Complexity

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| Build Trie | O(k*m) | k words, m avg length |
| Check one word | O(m²) | DFS explores all positions |
| All words | O(k*m²) | Check each word |
| **Total** | **O(k*m²)** | Depends on dictionary size |

### Optimization: Memoization

```
Cache results for substrings:
memo[i] = can substring from i onwards be formed?

This reduces repeated computation.
Time with memo: O(k*m²) → O(k*m) with DP
```

## Optimization: Sort by Length

```
1. Sort dictionary by word length (ascending)
2. Process shorter words first
3. Longer words can use shorter words in concatenation
4. Skip words that can't possibly be concatenated

Example:
["a", "b", "ab", "abc"]  (sorted)

Process "a", "b" (single char, can't be concatenated)
Then check "ab" (can use "a", "b")
Then check "abc" (can use "ab", "c" if "c" exists)
```

## Pruning Optimization

```
1. Skip words shorter than other two smallest words
   (Can't concatenate if too short)

2. Skip words longer than sum of two largest words
   (Can't reach by concatenation)

3. If word uses same word twice:
   Dictionary: ["a", "aa", "aaa"]
   "aaa" might be "a" + "aa" or "aa" + "a"
   Need to handle this carefully
```

## Edge Cases

```
1. Single word dictionary:
   ["abc"]
   → No concatenation possible
   Result: []

2. Empty string:
   ["", "a", "b", "ab"]
   → Handle empty string carefully
   Can "" be concatenated? Usually excluded.

3. Duplicate processing:
   ["ab", "ab"]
   → Usually assume unique words in dictionary

4. Circular dependencies:
   ["ab", "ba"]
   → "ab" needs "a" + "b", not other words
   → No circular issue here

5. Word uses itself multiple times:
   ["aa", "aaa", "aaaa"]
   "aaaa" = "aa" + "aa" ✓ (same word twice is okay)
```

## Questions to Ask Yourself

- Why not just use HashMap instead of Trie?
- How would you optimize with sorting?
- What if you need to count distinct decompositions?
- Can you return the actual concatenation breakdown?

## Related Problems
- Concatenated Words (LeetCode 472)
- Word Break II (get all decompositions)
- Compound words
- Trie + recursion patterns
