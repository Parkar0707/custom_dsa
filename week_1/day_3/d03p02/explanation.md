# Day 3 Problem 2: Load Balancer Request Routing

## Problem Statement
Use consistent hashing to distribute requests across servers such that adding/removing servers minimally disrupts routing.

## Core Concepts

### Load Balancing Challenge
- **Problem**: Distribute requests fairly across multiple servers
- **Naive Hash**: hash(request) % num_servers breaks when servers change
- **Effect**: 1 server added = all requests rehashed (cache thrashing)
- **Solution**: Consistent hashing

### Consistent Hashing
- **Hash Ring**: Map both requests and servers to circle
- **Request Routing**: Route to next server clockwise on ring
- **Adding Server**: Only 1/n requests need rehashing
- **Server Failure**: Requests redistribute minimally

### Why It's Optimal
```
Traditional hashing: hash(key) % n
- Adding 1 server (n → n+1): All n/(n+1) requests rehash (~100%)

Consistent hashing:
- Adding 1 server: Only 1/n requests rehash (~3% for 30 servers)
- Minimal disruption to cache coherence
```

## Understanding the Problem

### Input
- Set of servers
- Incoming requests
- Operations: add/remove servers, route request

### Output
- Which server to handle request
- Predictable across clients (same request → same server)
- Stable when topology changes

### Key Requirements
1. **Balance**: Distribute evenly
2. **Consistency**: Same request always routes same
3. **Resilience**: Server failures don't cascade
4. **Scalability**: Add servers without rebuilding

## Algorithm Intuition

### Hash Ring Concept
```
Servers hashed onto circle [0, 2^32):

         Server_A (hash: 10)
       /                    \
    Key_X (25) →→→→→→ Server_B (30)
     (routes to B)          |
                          Key_Y (50)
                       (routes to C)
                            |
                      Server_C (60)
```

### Routing Algorithm
```
1. Hash request → position on ring
2. Find first server ≥ request position (clockwise)
3. If no server found, wrap to first server (ring property)
4. Route to that server
```

### Example Routing
```
Hash function: return (sum of bytes) % 360

Request "user:123" → hash = 45
Servers: A(10), B(30), C(60), D(100)
Next server ≥ 45 = B(30) ✓ NO, 30 < 45
Next = C(60) ✓ YES, route to C

Request "user:999" → hash = 99
Next ≥ 99 = D(100) ✓ YES, route to D
```

## Virtual Nodes Optimization

### Problem: Uneven Load
```
3 servers on ring might be at:
- Server_A: position 10
- Server_B: position 200
- Server_C: position 350

Uneven spacing = uneven load distribution
```

### Solution: Virtual Nodes
```
Each server replicated multiple times (e.g., 150 replicas):
- Server_A: 10, 11, 12, ..., 159
- Server_B: 200, 201, ..., 349
- Server_C: 350, 351, ..., 499

More uniform spacing = balanced load
Failure of Server_A distributes to all others
```

## What You Should Think About

1. **Hash Function Choice**:
   - Consistent: Same input always same output
   - Uniform: Distribute evenly across range
   - Fast: Quick computation
   - 32-bit vs 128-bit vs 160-bit hashes

2. **Virtual Nodes**:
   - Tradeoff: More replicas = more balanced but more storage
   - Typical: 100-300 virtual nodes per physical server

3. **Server Failures**:
   - Detection: Heartbeat/health checks
   - Recovery: Failover to next server
   - Replication: Data on multiple servers

4. **Dynamic Topology**:
   - Adding servers: O(log n) servers rehash
   - Removing servers: Similar distribution
   - Maintaining ring order: Can use sorted list

5. **Edge Cases**:
   - Single server (always chosen)
   - All servers fail (graceful degradation)
   - Hash collisions (unlikely with good hash)

## Implementation Hints (Without Code)

- Create sorted structure of hashed server positions
- Binary search to find next server for request hash
- Map each request hash to server position
- Handle wraparound (use modulo or ring logic)
- Virtual nodes: hash(server_name + virtual_index)

## Practice Questions

1. How would you handle server weights (some servers more powerful)?
2. Can you measure load distribution fairness?
3. How to implement replication strategy?
4. What if network latency varies by server?

## Real-World Systems
- **Memcached**: Distributed caching
- **Redis Cluster**: Database sharding
- **Cassandra**: NoSQL distributed database
- **DynamoDB**: AWS distributed storage
- **Kafka**: Message broker partitioning

## Time Complexity
- Hash position: O(1)
- Find next server: O(log m) where m = virtual nodes
- Add server: O(log m)
- Remove server: O(log m)
