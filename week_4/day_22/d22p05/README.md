# Day 22, Problem 5: URL Shortener

## Problem Statement
Design a URL shortener system that converts long URLs to short codes and can decode them back. Must handle collisions and ensure uniqueness.

## Key Concepts

### Encoding Schemes

**Base62 Encoding** (62 characters: 0-9, a-z, A-Z)
```
Advantages:
- URL-safe (no special characters)
- Compact representation
- Human-readable

Counter: 1 → "a"
Counter: 62 → "10"
Counter: 100 → "1c"
```

**Hash-based** with Collision Handling
```
MD5/SHA1 hash shortened to fixed length
Pro: Deterministic (same URL always gets same code)
Con: Need collision resolution strategy
```

## Approach 1: Counter-based (Simple)

```
1. Maintain global counter
2. For each new URL:
   - Increment counter
   - Convert counter to base62
   - Store mapping: shortCode → originalURL
3. For retrieval:
   - Decode base62 to counter
   - Lookup in database
```

### Example:
```
URL: "https://www.example.com/very/long/path?id=123"
Counter: 12345
Base62: "3d7"
Short URL: "https://short.url/3d7"
```

## Approach 2: Hash-based with Collision Handling

```
1. Hash the long URL (MD5/SHA256)
2. Take first N characters as short code
3. If collision detected:
   - Add salt or counter
   - Rehash until unique code found
4. Store mapping in database and cache
```

### Collision Handling Strategies:
- Linear probing: Try short_code + "a", short_code + "b", etc.
- Quadratic probing: Try short_code_v2, short_code_v3, etc.
- Double hashing: Apply second hash function

## Data Structures Needed

```
1. Counter (for counter-based):
   - Atomic integer (thread-safe)

2. Primary Storage (Database):
   - HashMap: shortCode → originalURL
   - HashMap: originalURL → shortCode (for deduplication)

3. Cache Layer:
   - LRU cache for hot URLs
   - Reduces database queries

4. Trie (Optional):
   - For collision detection
   - Prefix-based analytics
```

## Example Walkthrough

### Counter-based System:

```
Insert Operations:
1. Input: "https://github.com/user/repo"
   Counter: 1
   Base62: "1"
   Store: {"1" → "https://github.com/user/repo"}
   Return: "short.url/1"

2. Input: "https://leetcode.com/problems"
   Counter: 2
   Base62: "2"
   Store: {"2" → "https://leetcode.com/problems"}
   Return: "short.url/2"

3. Input: "https://github.com/user/repo" (same URL)
   Check dedup cache first
   Return: "short.url/1" (already exists)

Query Operations:
1. Input: "short.url/1"
   Decode "1" → counter 1
   Lookup: {"1"} → "https://github.com/user/repo"
   Redirect to original URL
```

## Time & Space Complexity

| Operation | Complexity | Notes |
|-----------|-----------|-------|
| Generate short code | O(log n) | n = counter value |
| Store mapping | O(1) | HashMap insertion |
| Lookup | O(1) | HashMap retrieval |
| Deduplication check | O(1) | Hash lookup |
| **Space** | **O(m)** | m = unique URLs |

## Advantages & Trade-offs

### Counter-based:
✓ Sequential, predictable
✓ No collisions
✓ Simple logic
✗ Sequential guessing possible
✗ Requires global counter (single point of contention)

### Hash-based:
✓ No central counter needed
✓ Non-sequential (better security)
✗ Collision handling complexity
✗ Non-deterministic short codes

## Real-World Considerations

1. **Distributed System**: Use consistent hashing for scale
2. **Expiration**: URLs may need TTL (time to live)
3. **Analytics**: Track clicks, geographic data, referrer
4. **Custom Codes**: Allow users to specify custom short code
5. **Rate Limiting**: Prevent abuse of shortener
6. **Database Sharding**: Partition by short code prefix

## Questions to Ask Yourself

- How would you make this distributed across multiple servers?
- Can you use Trie for collision detection? Why or why not?
- What's the capacity? (How many URLs can you shorten?)
- How to handle duplicate long URLs?
- How to implement custom URL codes?

## Related Problems
- Design a URL shortening service (system design)
- Codec problems
- Hash table design
- Base conversion problems
