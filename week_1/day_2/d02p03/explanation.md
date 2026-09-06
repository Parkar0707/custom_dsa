# Day 2 Problem 3: Gene Expression Autocomplete

## Problem Statement
Build a trie data structure for gene name suggestions, allowing users to get autocomplete suggestions as they type gene names from a database.

## Core Concepts

### What is Autocomplete?
- Start with partial input: "TP"
- Return all gene names beginning with "TP": ["TP53", "TPM1", "TPM2", ...]
- Sorted by frequency or alphabetically
- Real-time suggestions as user types

### Why Trie (Prefix Tree)?
- **Trie Structure**: Tree where each path from root to node represents a prefix
- **Time Complexity**: O(m) to find all completions where m = length of prefix
- **Space Efficient**: Shared prefixes stored once
- Better than Hash Set: O(n) for all keys starting with prefix

### Advantages of Trie
```
Hash Set Search: SLOW - O(n) must check all genes
Trie Search: FAST - O(m + k) where m = prefix length, k = results
```

## Example Scenario

```
Gene Database: ["TP53", "TPM1", "TPM2", "BRCA1", "BRCA2", "GAPDH"]

User types "TP":
  Suggestions: ["TP53", "TPM1", "TPM2"]

User types "TPM":
  Suggestions: ["TPM1", "TPM2"]

User types "BR":
  Suggestions: ["BRCA1", "BRCA2"]
```

## Understanding the Problem

### Input
- List of gene names
- Prefix query from user

### Output
- All genes starting with prefix (usually top-k most frequent)
- Suggestions sorted appropriately

### Operations
1. **Insert**: Add gene name to trie
2. **Search**: Find all genes with given prefix
3. **DFS Traversal**: Explore subtrie under prefix node

### Why DFS?
- Once at prefix node, need to explore all descendants
- DFS traverses all complete gene names in subtrie
- Collect results as you traverse

## Trie Structure Understanding

```
              root
             /  |  \
            T   B   G
           /    |   |
          P     R   A
         /|     |   |
        5 M     C   P
        | /\    |   |
        3 1 2   A   D
              / \   |
             1   2  H
```

Each node contains:
- Reference to children (one per possible character)
- Boolean flag: "Is this a complete gene name?"
- Optional: Frequency/popularity count

## Algorithm Intuition

### Building Trie
1. For each gene name, start at root
2. For each character:
   - If child doesn't exist, create it
   - Move to child node
3. Mark final node as "end of word"

### Autocomplete with DFS
1. Traverse to prefix node using normal search
2. If prefix doesn't exist, return empty
3. From prefix node, perform DFS to find all descendants
4. Collect all marked nodes (complete genes)
5. Sort by frequency/name

## What You Should Think About

1. **Case Sensitivity**:
   - Gene names case-sensitive?
   - Should "TP53" match "tp53"?

2. **Prefix Matching Strategies**:
   - Exact prefix only?
   - Fuzzy matching?
   - Wildcard support?

3. **Performance Optimization**:
   - Should you cache results?
   - What if 100 genes start with prefix?
   - Rank by frequency for top-k results?

4. **Data Structure Details**:
   - Character encoding (ASCII/Unicode)?
   - Memory constraints?
   - Dynamic updates (add/remove genes)?

5. **Edge Cases**:
   - Empty prefix (return all genes)
   - Prefix longer than any gene
   - Single character search
   - Duplicate gene names

## Implementation Hints (Without Code)

- Design a Node class with children and end-of-word marker
- Think about how to represent children (array vs. dict)
- For DFS, you need to accumulate results while traversing
- Consider backtracking or passing results through recursion

## Practice Questions

1. How would you implement top-k autocomplete (return only k most frequent)?
2. Can you find all genes containing substring (not just prefix)?
3. How would you handle dynamic insertion/deletion?
4. What if you needed spell-check (one typo allowed)?

## Space-Time Tradeoff

```
Approach          | Time (search) | Space   | Notes
Trie              | O(m+k)        | O(n*m)  | m=prefix, k=results, n=genes
Hash Set + Sort   | O(n log n)    | O(n)    | Must check all genes
Prefix Hash Table | O(k)          | O(m*n)  | Precompute all prefixes
```

## Real-World Applications
- Gene database search (NCBI, Ensembl)
- Protein name lookup
- Medical terminology suggestions
- Drug name suggestions
- DNA sequence database queries
