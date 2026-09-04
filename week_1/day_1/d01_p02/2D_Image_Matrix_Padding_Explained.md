# Padding a 2D Image Matrix for a Sliding Window

## 1. Why do we need padding?

When an algorithm applies a sliding window (kernel) to an image, the window normally needs pixels on all sides of the current pixel.

For example, with a `3 x 3` window:

```text
a b c
d e f
g h i
```

When the window is centered on a pixel, it needs:

- 1 row above
- 1 row below
- 1 column to the left
- 1 column to the right

For pixels near the image boundary, some of those positions do not exist.

For example, consider a `5 x 5` image:

```text
1  2  3  4  5
6  7  8  9 10
11 12 13 14 15
16 17 18 19 20
21 22 23 24 25
```

If we want to apply a `3 x 3` window around the top-left pixel `1`, the window would need positions outside the image:

```text
?  ?  ?
?  1  2
?  6  7
```

The `?` positions do not exist.

Padding solves this problem by adding extra rows and columns around the original image.

---

## 2. How much padding is required?

The important formula is:

```text
padding = floor(k / 2)
```

where `k` is the window size.

### Examples

| Window size | Padding on each side |
|---|---:|
| `1 x 1` | 0 |
| `3 x 3` | 1 |
| `5 x 5` | 2 |
| `7 x 7` | 3 |
| `9 x 9` | 4 |

So, for a `3 x 3` window:

```text
padding = 3 / 2 = 1
```

For a `5 x 5` window:

```text
padding = 5 / 2 = 2
```

This works naturally for odd-sized windows.

---

## 3. What does padding actually do?

Suppose the original image has dimensions:

```text
rows = 5
columns = 5
```

and:

```text
k = 3
```

Then:

```text
padding = k / 2
         = 3 / 2
         = 1
```

We add:

- 1 row at the top
- 1 row at the bottom
- 1 column on the left
- 1 column on the right

Therefore the padded image becomes:

```text
7 x 7
```

The original `5 x 5` image is located in the center.

---

## 4. General formula for the padded dimensions

If the original image is:

```text
rows x columns
```

and the padding on each side is `p`, then:

```text
paddedRows = rows + 2 * p
paddedCols = columns + 2 * p
```

Since:

```text
p = floor(k / 2)
```

we can also write:

```text
paddedRows = rows + 2 * floor(k / 2)
paddedCols = columns + 2 * floor(k / 2)
```

### Example

For:

```text
rows = 5
columns = 5
k = 3
```

we get:

```text
p = 1

paddedRows = 5 + 2(1) = 7
paddedCols = 5 + 2(1) = 7
```

So the padded image is `7 x 7`.

---

## 5. Where should the original image be placed?

The simplest approach is to create a larger matrix and copy the original image into its center.

For `5 x 5` with `k = 3`:

```text
Original:

1  2  3  4  5
6  7  8  9 10
11 12 13 14 15
16 17 18 19 20
21 22 23 24 25
```

With one layer of padding, conceptually:

```text
0  0  0  0  0  0  0
0  1  2  3  4  5  0
0  6  7  8  9 10  0
0 11 12 13 14 15  0
0 16 17 18 19 20  0
0 21 22 23 24 25  0
0  0  0  0  0  0  0
```

Here `0` is the padding value.

The original pixel at:

```text
image[0][0]
```

moves to:

```text
padded[1][1]
```

The original pixel at:

```text
image[4][4]
```

moves to:

```text
padded[5][5]
```

In general:

```text
padded[i + p][j + p] = image[i][j]
```

This is the key relationship to remember.

---

## 6. Why zero padding is commonly used

There are several ways to fill the padding.

### Zero padding

The newly added cells contain `0`.

```text
0 0 0
0 X X
0 X X
```

This is simple and is commonly used in DSA problems and image-processing algorithms.

### Other padding strategies

Depending on the problem, you might instead use:

- constant padding
- replicate/border padding
- reflection padding
- circular/wrap-around padding

For a typical DSA problem, if the problem statement does not specify another strategy, you should carefully check what value the boundary is supposed to have. Do not automatically assume zero padding if the problem defines another behavior.

---

## 7. Why `k / 2` is the important calculation

Suppose the window size is `k`.

For an odd-sized window, the window has a natural center.

For example, a `5 x 5` window:

```text
x x x x x
x x x x x
x x C x x
x x x x x
x x x x x
```

There are:

```text
2
```

positions on each side of the center.

Therefore:

```text
padding = 5 / 2 = 2
```

Similarly, for a `7 x 7` window:

```text
padding = 7 / 2 = 3
```

So the general rule is:

```cpp
int padding = k / 2;
```

For the usual centered sliding-window problem, `k` is generally expected to be odd.

---

## 8. Mapping original coordinates to padded coordinates

This is especially important when writing the C++ code.

Suppose:

```cpp
int p = k / 2;
```

The original matrix coordinate:

```text
(i, j)
```

is stored in the padded matrix at:

```text
(i + p, j + p)
```

### Example

For `k = 3`:

```text
p = 1
```

Therefore:

```text
image[0][0] -> padded[1][1]
image[0][1] -> padded[1][2]
image[2][3] -> padded[3][4]
image[4][4] -> padded[5][5]
```

The extra offset `p` creates enough space around the original image.

---

## 9. C++ implementation

The following function only performs the padding. It does **not** implement the actual DSA/sliding-window algorithm.

```cpp
#include <iostream>
#include <vector>
using namespace std;

// Adds padding around a 2D image.
//
// image  : original 2D matrix
// k      : size of the sliding window (for example, 3 for a 3x3 window)
// padVal : value used for the new padding cells
//
// Returns:
// A new padded matrix.
vector<vector<int>> addPadding(
    const vector<vector<int>>& image,
    int k,
    int padVal = 0
) {
    // Number of rows in the original image.
    int rows = image.size();

    // Number of columns in the original image.
    int cols = image[0].size();

    // For a centered odd-sized k x k window,
    // we need k/2 cells on each side.
    //
    // Example:
    // k = 3 -> padding = 1
    // k = 5 -> padding = 2
    // k = 7 -> padding = 3
    int padding = k / 2;

    // Calculate dimensions of the new padded matrix.
    //
    // We add 'padding' rows at the top
    // and 'padding' rows at the bottom.
    //
    // Similarly, we add 'padding' columns
    // on the left and right.
    int paddedRows = rows + 2 * padding;
    int paddedCols = cols + 2 * padding;

    // Create the padded matrix.
    //
    // Every newly created cell initially contains padVal.
    vector<vector<int>> padded(
        paddedRows,
        vector<int>(paddedCols, padVal)
    );

    // Copy the original image into the center.
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            // Shift both coordinates by 'padding'.
            //
            // If padding = 1:
            // image[0][0] -> padded[1][1]
            // image[0][1] -> padded[1][2]
            // ...
            padded[i + padding][j + padding] = image[i][j];
        }
    }

    return padded;
}


// Helper function to print a 2D matrix.
void printMatrix(const vector<vector<int>>& matrix) {

    for (const auto& row : matrix) {

        for (int value : row) {
            cout << value << " ";
        }

        cout << '\n';
    }
}


int main() {

    // Example 5 x 5 image.
    vector<vector<int>> image = {
        { 1,  2,  3,  4,  5},
        { 6,  7,  8,  9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25}
    };

    // Sliding-window size.
    int k = 3;

    // Create the padded image.
    vector<vector<int>> padded = addPadding(image, k, 0);

    // Print the result.
    printMatrix(padded);

    return 0;
}
```

### Output

```text
0  0  0  0  0  0  0
0  1  2  3  4  5  0
0  6  7  8  9 10  0
0 11 12 13 14 15  0
0 16 17 18 19 20  0
0 21 22 23 24 25  0
0  0  0  0  0  0  0
```

---

## 10. Understanding the code step by step

The most important part is:

```cpp
int padding = k / 2;
```

For:

```cpp
k = 3;
```

we get:

```cpp
padding = 1;
```

Then:

```cpp
int paddedRows = rows + 2 * padding;
int paddedCols = cols + 2 * padding;
```

For a `5 x 5` image:

```text
paddedRows = 5 + 2(1) = 7
paddedCols = 5 + 2(1) = 7
```

Next, we create:

```cpp
vector<vector<int>> padded(
    paddedRows,
    vector<int>(paddedCols, padVal)
);
```

This creates a `7 x 7` matrix filled with `0`.

Finally:

```cpp
padded[i + padding][j + padding] = image[i][j];
```

copies the original image into the center.

---

## 11. A useful mental model

Think of padding as creating a protective border around the image.

For a `3 x 3` window:

```text
        padding
    <------------>

    0 0 0 0 0 0 0
    0 X X X X X 0
    0 X X X X X 0
    0 X X X X X 0
    0 X X X X X 0
    0 X X X X X 0
    0 0 0 0 0 0 0
```

The `X` region is the original image.

The outer `0`s are the padding.

This allows a `3 x 3` window to be centered around pixels near the original boundary without accessing invalid indices.

---

## 12. Important edge cases

### Case 1: `k = 1`

```text
padding = 1 / 2 = 0
```

No padding is required.

The padded matrix has the same dimensions as the original.

### Case 2: `k = 3`

```text
padding = 3 / 2 = 1
```

One layer of padding is added.

### Case 3: `k = 5`

```text
padding = 5 / 2 = 2
```

Two layers of padding are added.

For example, a `5 x 5` image becomes:

```text
5 + 2(2) = 9
```

so the padded image is:

```text
9 x 9
```

### Case 4: Image is not square

Padding does not require a square image.

For example:

```text
image = 4 x 7
k = 3
```

Then:

```text
padding = 1

paddedRows = 4 + 2 = 6
paddedCols = 7 + 2 = 9
```

So the padded matrix is:

```text
6 x 9
```

The same formula works.

---

## 13. Important assumption about `k`

The formula:

```cpp
padding = k / 2;
```

is intended for a **centered sliding window**, normally with an **odd window size** such as:

```text
3 x 3
5 x 5
7 x 7
```

Even-sized windows such as:

```text
2 x 2
4 x 4
```

do not have one exact center cell, so the padding behavior depends on how the specific problem defines the window's position.

Therefore, for a DSA problem, first determine whether the window is centered and whether `k` is guaranteed to be odd.

---

## 14. The core idea to remember

For a centered `k x k` window:

```cpp
int padding = k / 2;
```

Then:

```cpp
int paddedRows = rows + 2 * padding;
int paddedCols = cols + 2 * padding;
```

Create the padded matrix with the desired padding value:

```cpp
vector<vector<int>> padded(
    paddedRows,
    vector<int>(paddedCols, 0)
);
```

Then copy the original matrix using:

```cpp
padded[i + padding][j + padding] = image[i][j];
```

That is the entire basic padding mechanism.

The padding step should be kept separate from the actual DSA algorithm. Once the image has been padded correctly, the main algorithm can operate on the padded matrix without needing special boundary checks for the original image edges.
