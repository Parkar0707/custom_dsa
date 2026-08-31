# Spacecraft Memory Compaction

## Problem Overview

A spacecraft's onboard computer has limited RAM. After running many processes, memory becomes fragmented: allocated data blocks are scattered with gaps (free space) in between. This fragmentation reduces the size of the largest contiguous free block available for new processes.

Your task is to **defragment the memory in O(1) space** — rearrange memory blocks to remove gaps while using essentially no extra memory.

This is a classic **array manipulation** problem testing your ability to rearrange elements in-place.

## Context & Real-World Application

In embedded systems and spacecraft computing:
- Memory is physically limited and expensive to upgrade
- Fragmentation happens naturally: allocate, deallocate, allocate again
- Need compaction without using extra memory (can't afford temporary buffers)
- Must be fast: compaction happens while spacecraft is operating
- O(1) space constraint is critical for safety-critical systems

## Key Concepts to Understand

### Memory Representation
- Array indices represent memory addresses
- Values represent the memory content:
  - Positive values: allocated memory (process data)
  - Zero or negative: free space
  - Typical representation: 0 = free, non-zero = allocated

### In-Place Rearrangement
- Two-pointer or fill approach:
  - One pointer identifies blocks to move
  - Another pointer marks where they should go
  - Swap or fill as you go
- No auxiliary arrays, stacks, or queues (O(1) space)

### Compaction Goal
- Move all allocated (non-zero) blocks to the beginning
- Consolidate free space at the end
- Minimize or eliminate gaps within allocated region

## Example Scenario

A spacecraft's 16-byte memory after several processes:

```
Memory state (0 = free, letters = data):
[A, A, 0, B, B, 0, C, C, C, 0, 0, 0, D, D, 0, 0]
 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15

Fragmentation:
- Process A occupies indices 0-1 (2 bytes)
- Gap at 2
- Process B occupies indices 3-4 (2 bytes)
- Gap at 5
- Process C occupies indices 6-8 (3 bytes)
- Gap at 9-11
- Process D occupies indices 12-13 (2 bytes)
- Gap at 14-15

Total allocated: 9 bytes, but largest free contiguous block: 1 byte

After compaction (O(1) space, in-place):
[A, A, B, B, C, C, C, D, D, 0, 0, 0, 0, 0, 0, 0]
 0  1  2  3  4  5  6  7  8  9  10 11 12 13 14 15

Result:
- All allocated blocks contiguous (indices 0-8)
- All free space contiguous (indices 9-15)
- Largest free block: 7 bytes (much better!)
```

## What You Should Explore

1. **Representation of "allocated" vs "free"**:
   - Zero = free, non-zero = allocated? (or vice versa)
   - Does the data value matter, or just presence/absence?

2. **Approach options**:
   - Two-pointer technique: One scans, one writes
   - Single-pass vs. multi-pass
   - Shift-in-place vs. swap-in-place

3. **Correctness concerns**:
   - Preserve the order of allocated blocks?
   - Handle edge cases: all free, all allocated, single allocation
   - What if input is already compacted?

4. **Efficiency**:
   - O(1) space is the hard constraint
   - Can you do it in a single pass? Or multiple?
   - Time complexity: O(n) is achievable; is it O(n) for your approach?

5. **Output verification**:
   - After compaction, how do you verify correctness?
   - All non-free elements should be at the start
   - No gaps between allocated blocks

## Example Input/Output Format

**Input:**
- An array representing memory (0 for free, non-zero for allocated)
- Optionally: what counts as "free" (0, -1, empty spot, etc.)

**Output:**
- The same array, modified in-place, compacted
- The array should have all allocated blocks at the start, free space at end
- No auxiliary data structure used

## Hints on Approach

- Think of the problem like moving all non-zero elements to the front
- Two pointers: one for reading, one for writing
- As you identify an allocated block, move it forward if needed
- Consider: Do you need to preserve order? Does order matter for "compaction"?

## Why This Matters in DSA

This problem teaches:
- **In-place array manipulation** without extra space
- **Two-pointer technique** for efficient rearrangement
- **Practical constraints**: Real systems can't afford extra memory
- **Problem variants**: Similar patterns apply to moving zeros, duplicates, etc.

---

**Difficulty:** Easy to Medium  
**Primary Concept:** In-place array manipulation, Two-pointer technique  
**Secondary Concepts:** Memory management, Array shifting
