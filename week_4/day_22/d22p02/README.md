# Day 22, Problem 2: IP Router Longest Prefix Match

## Problem Statement
Implement an IP router that finds the longest matching prefix for a given IP address. Used in network packet routing to determine which interface to send packets to.

## Key Concepts

### Longest Prefix Match (LPM)
Given a routing table with IP prefixes and their associated destinations, find the most specific (longest) matching prefix for a given IP.

```
Routing Table:
192.168.0.0/24  → Route A
192.168.0.128/25 → Route B
10.0.0.0/8      → Route C

Query: 192.168.0.150
Match: 192.168.0.128/25 (longer prefix wins)
```

### Trie Structure for Binary IPs
- Build a binary trie (tree with 0 and 1 branches)
- Each node represents a bit position
- Path from root represents an IP prefix
- Store destination at leaf nodes

## Approach

1. **Convert IP to Binary**: Convert each IP address to 32-bit binary string
2. **Build Binary Trie**: Insert all routing table prefixes into Trie
3. **Traverse for Query**: For query IP, traverse the Trie as far as possible
4. **Track Best Match**: Remember the last node where a destination was defined
5. **Return Route**: Return the destination of the longest matching prefix

## Example Walkthrough

### Input:
```
Routing Table:
192.168.0.0/24    (Binary: 11000000.10101000.00000000.xxxxxxxx)
192.168.0.128/25  (Binary: 11000000.10101000.00000000.1xxxxxxx)
10.0.0.0/8        (Binary: 00001010.xxxxxxxx.xxxxxxxx.xxxxxxxx)

Query: 192.168.0.150
Binary: 11000000.10101000.00000000.10010110
```

### Process:
1. Traverse Trie matching query bits one by one
2. At bit 24 (first bit of last octet): matches /24 route
3. At bit 25 (second bit of last octet): matches /25 route (1 = 128-255 range)
4. Continue traversing with query IP
5. Last matching prefix found: /25 route
6. Return: Route to 192.168.0.128/25

## Time & Space Complexity

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| Insert prefix | O(32) | Fixed to IP length |
| Search query | O(32) | Fixed to IP length |
| **Total** | **O(1)** | Constant for IP routing |

## Key Differences from Standard Trie

- Fixed depth (32 bits for IPv4, 128 for IPv6)
- Binary branching only (0 or 1)
- Prefix notation with CIDR (e.g., /24)
- Store data at intermediate nodes, not just leaves

## Practical Considerations

1. **CIDR Notation**: /24 means first 24 bits are network portion
2. **Default Route**: 0.0.0.0/0 catches all unmatched packets
3. **Route Priority**: Longest prefix always wins (most specific)
4. **Real-World**: Hardware uses specialized data structures for millions of routes

## Questions to Ask Yourself

- What happens if there's no matching route?
- How do you handle IPv6 addresses (128 bits)?
- Can you optimize using bit manipulation instead of strings?
- How would you handle dynamic route insertion/deletion?

## Related Problems
- IP to CIDR notation conversion
- Trie-based routing algorithms
- Bitwise operations on IP addresses
