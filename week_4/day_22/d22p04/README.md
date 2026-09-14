# Day 22, Problem 4: Genome Pattern Matching

## Problem Statement
Find all occurrences of multiple patterns in a DNA/text sequence efficiently. Used in genomics to identify genetic patterns, viruses, or markers.

## Key Concepts

### Aho-Corasick Algorithm
A multi-pattern string matching algorithm that finds all occurrences of multiple patterns in a text in a single pass.

```
Text: "AABAAB"
Patterns: ["A", "AB", "B"]

Matches:
- "A" at positions [0, 1, 3, 4]
- "AB" at positions [1, 4]
- "B" at positions [2, 5]
```

### Algorithm Components

1. **Trie Construction**: Build a Trie of all patterns
2. **Failure Links**: Create shortcuts to handle mismatches
3. **Output Links**: Mark which patterns end at each node
4. **Linear Scan**: Traverse text once, following Trie and failure links

## Approach

### Step 1: Build Trie with Patterns
```
Patterns: ["he", "she", "his", "hers"]

Trie Structure:
       root
      / | \
     h  s  (others)
     |  |
     e  h
     |  |
    (he)(she)
```

### Step 2: Build Failure Links
For each node, failure link points to the longest proper suffix that is also a prefix in Trie.

### Step 3: Traverse Text
- Start at root
- For each character:
  - Follow Trie edge if exists
  - Otherwise, follow failure links until edge exists or reach root
  - Check output links for pattern matches

## Example Walkthrough

### Input:
```
Text: "ushers"
Patterns: ["he", "she", "her", "hers"]
```

### Process:
```
Text: u  s  h  e  r  s
      0  1  2  3  4  5

Position 0 ('u'): No match, stay at root
Position 1 ('s'): Go to 's' node
Position 2 ('h'): From 's', follow edge to 'h' (sh...)
Position 3 ('e'): From 'sh', follow edge to 'e' (she) - MATCH "she"
Position 4 ('r'): Follow to 'r' (sher)
Position 5 ('s'): From 'sher', look for 's' - not found
             Use failure link to find match
             Eventually match "hers" and "her"

Results:
- "she" at position [1]
- "her" at position [2]
- "hers" at position [2]
```

## Time & Space Complexity

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| Build Trie | O(k*m) | k patterns, m avg length |
| Build failure links | O(k*m) | BFS through Trie |
| Text scan | O(n) | n = text length, single pass |
| **Total** | **O(k*m + n)** | Linear in text size! |

### vs Naive Approach: O(n*k*m)
Search each pattern separately in text

## Failure Link Construction

```
For node representing "ab":
- Longest proper suffix that's a prefix: "b"
- Failure link → node representing "b"

For node representing "she":
- Longest proper suffix that's a prefix: "he"
- Failure link → node representing "he"
```

## Practical Applications

1. **Virus Detection**: Find multiple virus signatures in files
2. **Gene Sequencing**: Identify multiple genetic patterns in DNA
3. **Plagiarism Detection**: Find multiple suspicious phrases
4. **Spam Filtering**: Match multiple blacklist keywords

## Optimization Techniques

1. **Output Compression**: Store only longest matching patterns
2. **Pattern Preprocessing**: Remove subsumed patterns (if "she" is pattern, "he" is redundant for output)
3. **Space Optimization**: Use hash maps instead of full arrays for Trie

## Questions to Ask Yourself

- How would you modify to count total matches without storing positions?
- Can you optimize memory if patterns have common prefixes?
- How does this compare to regex matching?
- What if patterns can overlap?

## Related Problems
- Multiple string search
- Trie applications
- KMP (Knuth-Morris-Pratt) algorithm
- String matching variations
