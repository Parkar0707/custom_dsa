# Day 3 Problem 1: Distributed Cache Consistency

## Problem Statement
Design an LRU (Least Recently Used) cache with time-based invalidation for distributed systems, using hashmap and doubly linked list to maintain both fast access and ordering.

## Core Concepts

### Cache Fundamentals
- **Purpose**: Reduce latency by storing frequently accessed data locally
- **Limited Size**: Can't store everything, must evict when full
- **LRU Policy**: Remove least recently used item when capacity exceeded
- **Invalidation**: Data expires after certain time

### Data Structure Requirements
- **Fast Lookup**: Hashmap (O(1) access)
- **Ordering Maintenance**: Doubly Linked List (O(1) insertion/deletion)
- **Timestamp Tracking**: For time-based expiry

### Why Hashmap + Linked List?
```
Hashmap alone:
- Fast lookup ✓
- Slow ordering ✗

Linked List alone:
- Maintains order ✓
- Slow lookup ✗

Combined:
- Fast lookup ✓
- Maintains order ✓
- Can delete/reorder in O(1) ✓
```

## Understanding the Problem

### Cache Operations
1. **Get(key)**: Return value and mark as recently used
2. **Put(key, value)**: Store or update value
3. **Eviction**: Remove LRU item when full
4. **Expiry**: Remove expired items based on time

### Key Challenges
- **Thread Safety**: Multiple readers/writers
- **Time Tracking**: When was item accessed/stored?
- **Invalidation**: Different items have different TTL
- **Consistency**: Cache reflects current data

### Example Usage
```
Cache size: 3 items
Items: {key1→value1, key2→value2, key3→value3}

Access sequence:
Get(key1): key1 moved to front (most recent)
Get(key2): key2 moved to front
Put(key4, value4): key3 evicted (least recent), key4 added
Get(key1): key1 moved to front
```

## Algorithm Intuition

### Doubly Linked List Structure
```
Each node contains:
- key
- value
- timestamp (access or creation time)
- prev/next pointers

List maintained in order:
MostRecent ← → LeastRecent
  head        ...        tail
```

### LRU Eviction Strategy
1. On capacity full: evict tail (least recently used)
2. On access: move node to head (most recently used)
3. On insert: add to head
4. On update: delete and re-insert at head

### Time-Based Invalidation
```
Algorithm:
1. Store access_time with each item
2. On each access: check if expired
   - current_time - access_time > TTL
3. If expired: remove from cache
4. If not expired: update access_time and move to head
```

## Implementation Considerations

### Hashmap Storage
```
HashMap<Key, Node>

Where Node = {key, value, timestamp, prev, next}

For fast lookup by key
For fast update/deletion by reference
```

### Linked List Maintenance
```
Doubly linked list for:
- O(1) insertion at head
- O(1) deletion of any node (with reference)
- O(1) finding least recently used (tail)

Never need to traverse to find position
```

### Time Tracking
```
Option 1: Store timestamp on each access
  - Accurate but requires clock calls
  
Option 2: Use counter (access order)
  - Faster than timestamps
  - Doesn't need actual time

Hybrid: Check real time periodically
  - Reduces clock overhead
```

## What You Should Think About

1. **Eviction Policy**:
   - LRU: Last accessed removed
   - LFU: Least frequently used removed
   - FIFO: First in, first out
   - Random: Random removal

2. **Expiry Handling**:
   - Active expiry (check on access)
   - Passive expiry (background cleanup)
   - Time granularity (seconds vs. milliseconds)

3. **Concurrency**:
   - Multiple threads accessing cache
   - Lock-free vs. locked implementations
   - Atomic operations

4. **Performance Optimization**:
   - Batch expiry checks
   - Adaptive TTL based on access pattern
   - Prefetching hot items

5. **Edge Cases**:
   - Cache size = 1
   - TTL = 0 (expires immediately)
   - Rapid repeated access
   - Clock skew/adjustment

## Implementation Hints (Without Code)

- Create Node class with key, value, timestamp, prev, next
- Create HashMap to store key→Node mapping
- Maintain head (most recent) and tail (least recent)
- On access: check expiry, move to head
- On put: check capacity, evict if needed

## Practice Questions

1. How would you handle different TTLs for different items?
2. Can you optimize for workloads with many reads vs. writes?
3. How would you measure cache hit rate?
4. What about coordinating cache across multiple servers?

## Distributed Cache Considerations

```
Single Machine:
- Local cache
- Simple consistency

Distributed:
- Multiple caches per data item
- Coherence protocols needed
- Invalidation broadcast

Consistency models:
- Strong: All see same data
- Weak: May see stale data
- Eventual: Converge to consistent state
```

## Real-World Applications
- **CPU Caches**: L1, L2, L3 caches in processors
- **Database Caches**: Query result caching (Redis, Memcached)
- **HTTP Caches**: Browser and server caching
- **CDN Caches**: Content delivery networks
- **Distributed Systems**: Cache coherence (MESI protocol)

## Performance Analysis
- Get: O(1) lookup + O(1) move
- Put: O(1) insert + O(1) eviction
- Memory: O(capacity)
- Expiry check: O(1) per access
