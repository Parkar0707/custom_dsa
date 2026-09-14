# Day 22, Problem 9: Stream of Characters

## Problem Statement
Build a system that processes a stream of characters and detects if the stream ends with any word from a dictionary.

## Key Concepts

### Stateful Pattern Matching
- Characters arrive one at a time in a stream
- Must detect if stream ends with any dictionary word
- Can't store entire stream (unbounded size)
- Only maintain relevant suffix of stream

```
Dictionary: ["ab", "ba", "aaab", "abab", "baa"]
Stream: 'a' 'a' 'a' 'a' 'b'

After 'a': "a" → not a match
After 'a': "aa" → not a match
After 'a': "aaa" → not a match
After 'a': "aaaa" → not a match
After 'b': "aaab" → MATCH! (dictionary word)

Return: true
```

## Approach: Trie + Stream Buffer

1. **Build Trie**: Create Trie of dictionary words
2. **Maintain Buffer**: Store only last K characters (K = max word length)
3. **On New Character**:
   - Add character to buffer
   - Remove oldest if buffer exceeds K
   - Check if buffer ends with a dictionary word
4. **Buffer Check**: Traverse buffer from end using Trie

## Example Walkthrough

### Setup:
```
Dictionary: ["ab", "ba", "aaab"]
Max word length: 4
Trie:
       root
      /    \
     a      b
     |      |
     b      a
    (word)  (word)
    |
    a
    |
    a
    |
    b
   (word)
```

### Stream Processing:

```
Stream: 'a' 'a' 'a' 'b'
Buffer size: 4

Character 'a':
  Buffer: "a"
  Check from end: Trie has 'a', but not marked as word
  Continue, no match
  Return: false

Character 'a':
  Buffer: "aa"
  Check from end: Traverse back - no match
  Return: false

Character 'a':
  Buffer: "aaa"
  Check from end: no word ending here
  Return: false

Character 'b':
  Buffer: "aaab"
  Check from end:
    'b' exists in Trie from root ✓
    'a' exists in Trie from 'b' ✓
    'a' exists in Trie from 'a' ✓
    'a' exists in Trie from 'a' ✓
    This path represents "aaab" - which is in dictionary!
  Return: true
```

## Algorithm Detail: Checking if Buffer Ends with Word

```
For buffer = "xyzab" and searching for words ending at current position:

Method 1: Suffix-based Trie check
1. Start from last character 'b' in buffer
2. Work backwards, matching with Trie built for word reversal
   - Build Trie with reversed words
   - Match from end of buffer going left
3. Stop when can't match or reach start

Method 2: Traverse Trie from stream position
1. Keep pointer at buffer start
2. For each new character, check all possible words ending there
3. Use DFS or dynamic position tracking
```

### Efficient Implementation:

```python
# Pseudocode
class StreamChecker:
    def __init__(self, words):
        self.trie = build_trie(words)
        self.max_len = max(len(w) for w in words)
        self.buffer = deque(maxlen=self.max_len)
    
    def query(self, letter):
        self.buffer.append(letter)
        # Check all suffixes of current buffer
        for i in range(len(self.buffer)):
            suffix = self.buffer[i:]
            if self.is_word_in_trie(suffix):
                return True
        return False
```

## Optimization: Reverse Trie

Instead of checking all suffixes, use reverse Trie:

```
Dictionary: ["ab", "ba", "aaab"]
Reversed: ["ba", "ab", "baaa"]

Reverse Trie:
       root
      / \
     b   a
     |   |
     a   b
    (word)(word)
     |
     a
     |
     a
    (word)

On stream character:
- Keep track of Trie position
- On new char, follow Trie path backwards
- Or: traverse last few chars against reverse Trie
```

## Time & Space Complexity

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| Build Trie | O(k*m) | k words, m avg length |
| Buffer addition | O(1) | Deque push/pop |
| Stream query | O(L*m) | L = min(n, max_len), m = Trie depth |
| **Space** | **O(k*m + L)** | Trie + buffer storage |

Where:
- k = number of dictionary words
- m = average word length
- L = maximum word length
- n = current stream position

## Optimization Techniques

1. **Limited Buffer**: Only store up to max_word_length characters
2. **Reverse Trie**: Avoid checking all suffixes repeatedly
3. **Position Tracking**: Remember position in Trie from previous query
4. **Lazy Evaluation**: Don't traverse full Trie if match found early

## Edge Cases

```
1. Single character stream:
   Dictionary: ["a", "aa"]
   Stream: 'a'
   Buffer: "a" (full match)
   Return: true

2. Overlapping words:
   Dictionary: ["ab", "ba", "aaab"]
   Stream: "aab"
   At 'b': Could match "ab" (suffix) or continue to "aab"
   Return: true (matches "ab")

3. No matches:
   Dictionary: ["abc"]
   Stream: "xyz"
   Return: false (never matches)

4. Buffer exceeds max length:
   Dictionary: ["ab"] (max length 2)
   Stream: "xyzab"
   Buffer keeps only last 2: "ab"
   Can still detect match for "ab"
```

## Questions to Ask Yourself

- Why not just store the entire stream?
- Can you optimize if words have common suffixes?
- How would you handle queries about position of match?
- What if stream is infinite and you need continuous updates?

## Related Problems
- Stream Checker (LeetCode 1032)
- Pattern Matching in stream
- Trie with state persistence
- Real-time keyword detection
