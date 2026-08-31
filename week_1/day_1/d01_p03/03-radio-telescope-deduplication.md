# Radio Telescope Signal Deduplication

## Problem Overview

Radio telescopes receive continuous streams of electromagnetic signals from space. Due to atmospheric interference, equipment limitations, and natural cosmic phenomena, the same astronomical signal often arrives multiple times in the data stream with slight variations or exact duplicates.

Your task is to identify and extract **unique astronomical signals** from a noisy data stream using **two-pointer technique combined with hashing**.

## Context & Real-World Application

In radio astronomy (e.g., SETI, pulsar detection, space exploration):
- Signals may be duplicated due to signal reflection or instrumental artifacts
- The data stream can be enormous (terabytes from a single observation)
- Need efficient real-time or near-real-time deduplication
- Preserving order of first occurrence may be important for temporal analysis

## Key Concepts to Understand

### Hash-Based Deduplication
- Use a hash set to track which signals you've already seen
- Query the set before processing each signal (O(1) average)
- Eliminates duplicates without sorting (if order matters)

### Two-Pointer Technique
- Maintain two pointers in an array:
  - One pointer scans all elements
  - Another pointer marks where unique elements should go
- After passing through, elements [0...second_pointer] contain unique values
- No extra space needed (in-place modification)
- **Caveat**: Works efficiently only on **sorted** arrays

### Combining Both Approaches
- **If array is unsorted**: Hash set for uniqueness; pointer to build result
- **If array is sorted**: Two pointers to skip duplicates in-place
- **If order of first occurrence matters**: Hash set to track seen; use original indices

## Example Scenario

Imagine radio signals arriving as a stream:

```
Raw incoming signal log:
Signal: [A001, B042, A001, C999, B042, A001, D123, C999]
                ↑ duplicate A001 at index 2
                            ↑ duplicate B042 at index 4
                                      ↑ duplicate C999 at index 7

Deduplicated (preserving order of first occurrence):
[A001, B042, C999, D123]
```

## What You Should Explore

1. **Order preservation**: Does the problem require keeping signals in the order they first appeared?
   - If yes: Hash set tracks seen signals, collect in original order
   - If no: More flexibility in approach

2. **In-place modification**: Can you modify the input array directly, or must you return a new structure?
   - In-place: Two-pointer technique on sorted data
   - Extra space allowed: Hash set is simpler and works on unsorted data

3. **Signal comparison**: How do you determine if two signals are identical?
   - Exact match? (Signal codes are strings or IDs)
   - Fuzzy match? (Signals within threshold of each other)
   - For this problem, assume exact match

4. **Efficiency trade-offs**:
   - Hash set + linear scan: O(n) time, O(n) space
   - Two-pointer on sorted array: O(n) time, O(1) space
   - Without sorting first: Different time costs

## Example Input/Output Format

**Input:**
- An array of signal identifiers (strings, integers, or objects)
- Optionally, a requirement about order preservation

**Output:**
- An array containing only unique signals
- Order preserved from input (typically)

## Hints on Approach

- If the input is already sorted, the two-pointer technique shines
- If unsorted and order must be preserved, hash set + linear scan is cleaner
- Think about what "signal deduplication" really means in your algorithm:
  - Remove the duplicate? Keep only the first occurrence?
- Don't overthink: Often the simplest approach (hash set) is best for real problems
- Consider: What if signals are complex objects, not just strings/integers?

## Why This Matters in DSA

This problem teaches:
- **Hash-based deduplication** for handling large streams
- **Two-pointer technique** for in-place array manipulation
- **Space vs. time trade-offs** (memory to save computation)
- **Real-world constraints**: Streaming data, memory limits, order preservation

---

**Difficulty:** Easy to Medium  
**Primary Concept:** Hashing, Two-Pointer Technique  
**Secondary Concepts:** Deduplication, Array manipulation
