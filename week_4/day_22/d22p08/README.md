# Day 22, Problem 8: Replace Words

## Problem Statement
Given a dictionary of root words and a sentence, replace each word with its root (if root exists in dictionary).

## Key Concepts

### Prefix Matching with Trie
- Build Trie of dictionary roots
- For each word in sentence, find shortest matching prefix
- Replace word with that prefix

```
Dictionary: ["cat", "bat", "rat"]
Sentence: "the cattle was rattled by the battery"

"cattle" → prefix "cat" found → replace with "cat"
"rattled" → prefix "rat" found → replace with "rat"
"battery" → prefix "bat" found → replace with "bat"

Result: "the cat was rat by the bat"
```

## Approach

1. **Build Trie**: Insert all dictionary roots
2. **Mark Word Nodes**: Mark nodes in Trie that complete a dictionary word
3. **Process Sentence**:
   - Split into words
   - For each word, traverse Trie
   - Stop at first marked node (shortest root found)
   - If no root found, keep original word
4. **Reconstruct Sentence**: Join replaced words

## Example Walkthrough

### Input:
```
Dictionary: ["cat", "cats", "dog", "catsdog"]
Sentence: "I have a cat. The cats are dogs."
```

### Build Trie:
```
         root
        /  |  \
       c   d   (others)
       |   |
       a   o
      / \  |
     t   t g
    (word)  (word)
    |
    s
   (word)
```

### Processing "cats":
```
Traverse Trie with "cats":
c → found
 a → found
  t → found, MARKED as word (root "cat")
   s → could continue to "cats"
   
Stop at 't' since it's marked.
Replace "cats" with "cat"
```

### Full Processing:
```
Original: "I have a cat. The cats are dogs."
Split: ["I", "have", "a", "cat.", "The", "cats", "are", "dogs."]

"I" → traverse Trie, no 'I' node → keep "I"
"have" → traverse Trie, no 'h' node → keep "have"
"a" → traverse Trie, no 'a' node → keep "a"
"cat." → extract word "cat", find root "cat", replace with "cat."
"The" → keep "The"
"cats" → extract word "cats", find root "cat", replace with "cat"
"are" → keep "are"
"dogs." → extract word "dogs", find root "dog", replace with "dog"

Result: "I have a cat. The cat are dog."
```

## Implementation Details

### Word Boundary Handling:
```
Original: "The cats-and-dogs are running."
Words: ["The", "cats", "and", "dogs", "are", "running"]

Need to handle:
- Punctuation: "cat." → extract "cat", process, keep punctuation
- Hyphenation: might split or keep together depending on requirements
- Case sensitivity: usually case-insensitive in roots
```

## Time & Space Complexity

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| Build Trie | O(k * m) | k roots, m avg length |
| Process sentence | O(n * L) | n words, L avg length |
| Traverse per word | O(L) | Max L chars per word |
| **Total** | **O(k*m + n*L)** | Linear in input size |

### vs Naive (HashMap lookup for each word):
```
HashMap: O(n*L) for hashing each word
Trie: O(n*L) for traversal (same asymptotic, but Trie can stop early)
Advantage: Trie stops at shortest prefix, avoiding full word comparison
```

## Edge Cases

```
1. Word is prefix of multiple roots:
   Word: "cat"
   Roots: ["cat", "catch", "catalogue"]
   → Choose "cat" (exact match, shortest)

2. No matching root:
   Word: "apple"
   Roots: ["cat", "dog"]
   → Keep "apple"

3. Root is longer than word:
   Word: "ca"
   Roots: ["cat", "dog"]
   → Keep "ca" (can't reach root in Trie)

4. Empty word or root:
   Dictionary: ["", "cat"]
   → Handle edge case in implementation
```

## Optimizations

1. **Early Termination**: Stop traversing Trie as soon as a root is found
2. **Case Normalization**: Convert to lowercase for comparison
3. **Punctuation Stripping**: Separate algorithm to handle punctuation

## Algorithm Variant: Multiple Replacements

If word could match multiple roots:
```
Greedy (implemented above): Always pick shortest root

Alternative: Pick longest root
Word: "cat"
Roots: ["c", "cat", "ca"]
- Greedy (shortest): "c"
- Alternative (longest): "cat"

Problem usually asks for shortest/fastest reduction.
```

## Questions to Ask Yourself

- Why is Trie better than HashMap for this problem?
- How would you handle case-insensitive matching?
- What if roots can overlap or be subsets of each other?
- Can you optimize for very long sentences?

## Related Problems
- Replace Words (LeetCode 648)
- Palindrome Prefix matching
- Trie applications
- Sentence processing

## Practical Note
This is similar to:
- Spell correction (root words)
- Stemming algorithms (NLP)
- Word normalization (text processing)
