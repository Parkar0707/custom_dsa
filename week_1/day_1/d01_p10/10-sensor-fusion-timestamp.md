# Sensor Fusion Timestamp Alignment

## Problem Overview

A spacecraft or rover is equipped with multiple sensors (temperature, pressure, radiation, camera, etc.), each generating data at its own rate and with potential delays. To get a complete picture of the environment, you must **merge k sorted sensor data streams** while preserving chronological order.

Your task is to implement **k-way merge** to efficiently combine data from multiple sources into a single time-ordered stream.

## Context & Real-World Application

In multi-sensor systems (robotics, aerospace, scientific instruments):
- Each sensor produces timestamped readings
- Sensors report data at different frequencies (1 Hz, 10 Hz, 100 Hz)
- Some sensors have latency (time between event and reporting)
- Example: camera sends images every 0.1s, thermometer every 1s
- Must align in time to:
  - Create synchronized data for machine learning
  - Detect correlations between different measurements
  - React to critical events across multiple sensors
- Naive approach: combine all, then sort O(k×n×log(k×n))
- Better: k-way merge O(k×n×log k) using heaps

## Key Concepts to Understand

### Sorted Streams
- Each sensor produces data as a sorted stream (by timestamp)
- Stream 1: [t=1.0, t=2.5, t=4.2, ...]
- Stream 2: [t=0.5, t=1.5, t=3.7, ...]
- Stream 3: [t=0.8, t=2.2, t=3.5, ...]
- Goal: merge into single sorted stream: [t=0.5, t=0.8, t=1.0, t=1.5, t=2.2, t=2.5, t=3.5, t=3.7, t=4.2, ...]

### Min-Heap (Priority Queue) Approach
- Maintain a min-heap with one element from each stream (the front)
- Pop the smallest timestamp, add its data to output
- Advance the stream it came from, add the next element to heap
- Repeat until all streams exhausted
- Time: O(k×n×log k) where k = number of streams, n = total elements

### Two-Way Merge (Merge Sort Foundation)
- Merge two sorted streams: O(n₁ + n₂) with two pointers
- This builds intuition for k-way merge
- k-way: generalize to k pointers (or k stream iterators)

## Example Scenario

Three sensors on a Mars rover reporting simultaneously:

```
Sensor 1 (Thermometer): [1.0°C, 2.5°C, 4.2°C, 5.1°C] at times [0s, 1s, 2s, 3s]
Sensor 2 (Pressure):    [1.2atm, 1.5atm, 1.8atm] at times [0.5s, 1.5s, 2.5s]
Sensor 3 (Radiation):   [50Sv, 52Sv, 55Sv, 58Sv] at times [0.8s, 2.2s, 3.5s, 4.0s]

Merge by timestamp:
[0s:   Temp=1.0°C]
[0.5s: Pressure=1.2atm]
[0.8s: Rad=50Sv]
[1.0s: Temp=2.5°C]
[1.5s: Pressure=1.5atm]
[2.0s: Temp=4.2°C]
[2.2s: Rad=52Sv]
[2.5s: Pressure=1.8atm]
[3.0s: Temp=5.1°C]
[3.5s: Rad=55Sv]
[4.0s: Rad=58Sv]

Benefits:
- Scientist sees exact temporal relationships
- Can correlate: "Radiation spike at 0.8s, but temp still normal"
- Detects when sensor events co-occur (or don't)
```

## What You Should Explore

1. **Stream representation**:
   - Each stream as an array (pre-loaded)?
   - Each stream as an iterator/generator (streaming)?
   - Mix of both?
   - Assumes streams are already sorted by timestamp

2. **Data structure (heap)**:
   - Min-heap to efficiently get the smallest timestamp
   - Each heap element: (timestamp, stream_id, data)
   - Heap operations: O(log k) per push/pop
   - Alternative: use a heap library (Python's heapq, C++'s priority_queue)

3. **Comparison and ordering**:
   - Timestamps might be floats (0.1s, 0.5s)
   - What if two sensors report at same timestamp?
   - Tiebreaker: sensor ID? priority? data value?

4. **Output format**:
   - Sequence of (timestamp, sensor_id, data)?
   - Or just (timestamp, combined_data_dict)?
   - Example: {timestamp: 1.5, thermometer: 2.5, pressure: 1.5}?

5. **Memory efficiency**:
   - If one stream is huge (millions of readings) and another is small
   - Naive merge into single array: uses O(k×n) space
   - Streaming merge: uses O(k) space (just one element per stream in heap)

6. **Edge cases**:
   - Empty streams (sensor never sends data)?
   - Single stream (no merging needed)?
   - Streams with gaps (data at t=1 then t=3, nothing at t=2)?
   - Same timestamp on multiple sensors (deterministic tiebreaker)?

## Example Input/Output Format

**Input:**
- k streams, each already sorted by timestamp
- Each stream: list of (timestamp, value) pairs or objects
- Optionally: stream metadata (sensor name, type)

**Output:**
- Merged stream: list of (timestamp, stream_id, value) or similar
- Fully sorted by timestamp
- All elements from all streams included

## Hints on Approach

- Start by implementing two-way merge (simplest case)
- Generalize to k-way using a min-heap
- Test with: all equal-length streams, varying stream lengths
- Verify: output is sorted, has all input elements
- Consider: What if one stream is much larger than others?
  - Does k-way merge handle this well? (Yes, heap keeps heap size at k)

## Why This Matters in DSA

This problem teaches:
- **K-way merge** for combining multiple sorted inputs
- **Priority queue/heap** for efficient selection
- **Merging algorithm** foundation for merge sort and external sorting
- **Time-space tradeoffs**: O(k×n×log k) time, O(k) space
- **Streaming algorithms**: Handle large data without loading all
- **Real-world systems**: Multi-sensor fusion, distributed data aggregation

---

**Difficulty:** Medium to Hard  
**Primary Concept:** K-way Merge, Heap (Priority Queue)  
**Secondary Concepts:** Sorting, Merging algorithms, Streaming data
