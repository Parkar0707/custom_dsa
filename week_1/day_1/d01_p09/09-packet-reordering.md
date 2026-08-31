# Network Packet Reordering

## Problem Overview

When data is transmitted over networks, packets may arrive out of order due to different network paths, retransmissions, and latency variations. A receiving system must **reorder out-of-sequence packets into their original order** efficiently.

Your task is to **reorder packets** using a **cyclic array (circular buffer)** approach, which is memory-efficient and suitable for streaming data.

## Context & Real-World Application

In network communication (TCP/IP, video streaming, real-time systems):
- Each packet has a sequence number indicating its order
- Packets 1, 2, 3 might arrive as 3, 1, 2 or 1, 3, 2
- Must reassemble in original order before delivering to application
- Packets have a valid window (e.g., sequence numbers 100-199)
- Cyclic array: efficient for handling wrap-around in sequence numbers
- Used in: TCP buffers, multimedia streaming, spacecraft data transmission

## Key Concepts to Understand

### Sequence Numbers and Windows
- Packets labeled with sequence numbers (e.g., 100, 101, 102, ...)
- Only accept packets within a "receive window" (e.g., [100, 119])
- Sequence numbers are finite precision: wrap around (0, 1, ..., max, 0, 1, ...)
- Example: 16-bit sequence space: 0 to 65535, then wraps to 0

### Cyclic Array (Circular Buffer)
- A fixed-size array used as if it wraps around
- Index wrapping: if array size is 10, index 10 wraps to 0, index 11 wraps to 1
- Formula: actual_index = sequence_number % array_size
- Efficient space: don't allocate new array for each sequence range

### Reordering Algorithm
1. Maintain a circular buffer of size `window_size`
2. For each incoming packet: calculate its position in the buffer
3. Place packet at that position
4. Deliver all packets starting from the current sequence number until a gap is found
5. Slide the window forward

## Example Scenario

Receiving data stream with sequence numbers and a window size of 5:

```
Receive window: [0, 4] (size 5)
Current expected sequence: 0

Cyclic array (size 5):
Index:  [0, 1, 2, 3, 4]
Value:  [_, _, _, _, _]  (empty initially)

Incoming packets (order received):
Packet seq=2, data="C"  → place at index 2
Packet seq=0, data="A"  → place at index 0
Packet seq=1, data="B"  → place at index 1
Packet seq=4, data="E"  → place at index 4
Packet seq=3, data="D"  → place at index 3

After all packets received:
Index:  [0, 1, 2, 3, 4]
Value:  [A, B, C, D, E]

Deliver sequence: A, B, C, D, E (in correct order!)

Next window: [5, 9]
Cyclic array reuses same indices:
Packet seq=5, data="F"  → place at index 0 (5 % 5)
Packet seq=6, data="G"  → place at index 1 (6 % 5)
...

Example with gaps:
Incoming: seq=0, seq=1, seq=2, seq=4 (seq=3 missing)
Buffer: [A, B, C, _, E]
Deliver: A, B, C (stop at gap, seq=3 not received yet)
Wait for seq=3...
Receive seq=3, data="D"
Buffer: [A, B, C, D, E]
Deliver: D, E
```

## What You Should Explore

1. **Window size and sequence space**:
   - How large should the cyclic array be?
   - Typically: related to the receive window size
   - Constraint: Must be large enough to handle reordering
   - Trade-off: Larger buffer = more memory, but handles more out-of-order cases

2. **Sequence number overflow**:
   - How do you handle wrap-around?
   - Modulo arithmetic: position = seq % array_size
   - Be careful: Distinguish between two different data packets at "same" modulo position
   - Example: seq=5 and seq=10005 both map to index 0 (mod 10), but are different
   - Solution: Track a base or epoch to disambiguate

3. **In-order delivery**:
   - What defines "delivery"?
   - Deliver as soon as you have an in-order chunk? (streaming)
   - Deliver only after a timeout? (buffering)
   - Deliver when you reach the end of the window? (batching)

4. **Gap handling**:
   - If packet 3 is missing, hold packets 4, 5, ... until 3 arrives
   - If packet 3 never arrives (lost), do you timeout?
   - Real systems: Retransmit requests or discard after timeout

5. **Edge cases**:
   - Duplicate packets (arrive twice)
   - Out-of-window packets (seq too old or too new)
   - Empty/null data packets
   - Packets arriving in perfect order (buffer not needed)

## Example Input/Output Format

**Input:**
- Sequence of packets, each with: sequence number and data
- Window size parameter
- Starting sequence number expected

**Output:**
- Ordered sequence of data payloads
- Report any gaps or missing packets
- Optionally: which packets were out-of-order

## Hints on Approach

- Use modulo to map sequence numbers to array indices
- Keep track of the current expected sequence number
- Deliver contiguous packets; pause at gaps
- Consider: separate tracking of "which packets we have" (bitmap or counter)
- Simulate manually first with small window size to understand flow

## Why This Matters in DSA

This problem teaches:
- **Circular buffers** for efficient memory reuse
- **Modulo arithmetic** for handling wrap-around
- **Sequence number management** in systems
- **Data structure design** for streaming/online algorithms
- **Real-world constraints**: Network protocols need efficient reordering

---

**Difficulty:** Medium  
**Primary Concept:** Circular Array, Cyclic buffer, Array manipulation  
**Secondary Concepts:** Modulo arithmetic, Streaming algorithms
