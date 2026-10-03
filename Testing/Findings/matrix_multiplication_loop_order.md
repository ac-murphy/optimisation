# Matrix Multiplication
### Introduction
Matrix multiplication requires three loops. Two for each axis `i, j`, and one for the dot product used to calculate each new element `k`. Order matters here because of how matrices are represented in memory. I've used row-major matrices, which means in memory a 3x3 matrix will look like
$$
    \begin{pmatrix}
        0 & 1 & 2 \\
        3 & 4 & 5 \\
        6 & 7 & 8
    \end{pmatrix} 
    \implies 
    \texttt{[0 1 2][3 4 5][6 7 8]}.
$$

### Implementation
To test which methods are best for multiplying matrices, I've implemented two `matrix<T, M, N>` classes with different underlying structures; a "nested" 2D array (`c++ std::array<std::array<T, M>, N>`) and a "flat" 1D array (`std::array<T, M * N>`). My theory here was that a flat array involves fewer hoops to navigate and therefore fewer instructions are needed overall to complete the multiplication.

As a baseline, I used `i, j, k` as the first loop. As an algorithm, this looks like
```c++
matrix<T, L, N> operator*(matrix<T, L, M> A, matrix<T, M, N> B)
{
    matrix<T, L, N> result;
    
    for (size_t i = 0; i < L; ++i)
        for (size_t j = 0; i < N; ++j)
            for (size_t k = 0; k < M; ++k)
                result(i, j) = A(k, j) * B(i, k);
                
    return result;
}
```
so a different ordering would just rearrange the for loops. For the initial benchmark, and all subsequent runs, I used 64x64 matrices with `float` data type. Here is the first result:

|  order  | storage  | avg. time ($\mu$s) |  cv%   |
|:-------:|:--------:|:------------------:|:------:|
| $i-j-k$ |  `flat`  |      $60.948$      | $1.63$ |
| $i-j-k$ | `nested` |      $61.872$      | $1.13$ |

This alone however is inconclusive, so I decided to keep both versions and test all combinations of `i`, `j` and `k`.

### Loop ordering
The next step I took was to permute the indexing order and see what, if any, performance boosts there were. There was no particular order I did this and I wasn't expecting to see any patterns.

|  order  | storage  | avg. time ($\mu$s) |  cv%   |
|:-------:|:--------:|:------------------:|:------:|
| $j-i-k$ |  `flat`  |      $60.584$      | $1.70$ |
| $j-i-k$ | `nested` |      $61.532$      | $1.36$ |
| $k-i-j$ |  `flat`  |      $58.765$      | $1.44$ |
| $k-i-j$ | `nested` |      $61.785$      | $1.75$ |
| $k-j-i$ |  `flat`  |      $63.061$      | $1.99$ |
| $k-j-i$ | `nested` |      $63.189$      | $2.55$ |
| $i-k-j$ |  `flat`  |      $60.733$      | $2.86$ |
| $i-k-j$ | `nested` |      $59.186$      | $1.65$ |
| $j-k-i$ |  `flat`  |      $80.503$      | $1.64$ |
| $j-k-i$ | `nested` |      $77.188$      | $1.63$ |

The difference between the fastest and the slowest is ~20$\mu$s - definitely significant. From this it's clear the order of iteration matters. After stepping through the algorithms manually, I saw why $j-k-i$ performs so poorly. For each matrix `A`, `B`, `C` the elements are accessed row-first, column-second i.e.

$$
    \begin{array}{c}
        C & & A & & B \\
        \begin{pmatrix}
            1 & 4 & 7 \\
            2 & 5 & 8 \\
            3 & 6 & 9
        \end{pmatrix} & = &
        \begin{pmatrix}
            1 & 4 & 7 \\
            2 & 5 & 8 \\
            3 & 6 & 9
        \end{pmatrix} & * &
        \begin{pmatrix}
            1 & 4 & 7 \\
            2 & 5 & 8 \\
            3 & 6 & 9
        \end{pmatrix}
    \end{array}
$$

which means successive element accesses for $A$ and $C$ are non-contiguous. An overview of the algorithm's steps show why this is so poor from a memory standpoint.

$$
\begin{array}{|c|c|c|c|}
    \hline
    j-k-i & C & A & B \\
    \hline
    0~~ 0~~ 0 & c_{00} & a_{00} & b_{00} \\
    0~~ 0~~ 1 & c_{10} & a_{10} & b_{00} \\
    0~~ 0~~ 2 & c_{20} & a_{20} & b_{00} \\
    \hline
    0~~ 1~~ 0 & c_{00} & a_{01} & b_{10} \\
    0~~ 1~~ 1 & c_{10} & a_{11} & b_{10} \\
    0~~ 1~~ 2 & c_{20} & a_{21} & b_{10} \\
    \hline \vdots \\ \hline
    1~~ 0~~ 0 & c_{01} & a_{00} & b_{01} \\
    1~~ 0~~ 1 & c_{11} & a_{10} & b_{01} \\
    1~~ 0~~ 2 & c_{21} & a_{20} & b_{01} \\
    \hline
\end{array}
$$

Columns $C$ and $A$ are explicitly non-contiguous, requiring a stride of $N$ (in this case, 3) bytes each step. The value of $b_{ij}$ can be stored for 3 steps, but each consecutive value is also non-contiguous. For a large matrix, this could mean the required values do not fit on the L1 cache and will result in more latency when retrieving them. 

In contrast, the best performing order $k-i-j$ accessed each element as follows:

$$
    \begin{array}{c}
        C & & A & & B \\
        \begin{pmatrix}
            1 & 2 & 3 \\
            4 & 5 & 6 \\
            7 & 8 & 9
        \end{pmatrix} & = &
        \begin{pmatrix}
            1 & 4 & 7 \\
            2 & 5 & 8 \\
            3 & 6 & 9
        \end{pmatrix} & * &
        \begin{pmatrix}
        1 & 4 & 7 \\
        2 & 5 & 8 \\
        3 & 6 & 9
        \end{pmatrix}
    \end{array}
$$

So already this is better-aligned to the memory layout of the row-major matrices, as the access of $C$ and $B$ are now in the correct order. 

$$
\begin{array}{|c|c|c|c|}
\hline
k-i-j & C & A & B \\
\hline
0~~ 0~~ 0 & c_{00} & a_{00} & b_{00} \\
0~~ 0~~ 1 & c_{01} & a_{00} & b_{01} \\
0~~ 0~~ 2 & c_{02} & a_{00} & b_{02} \\
\hline
0~~ 1~~ 0 & c_{10} & a_{10} & b_{00} \\
0~~ 1~~ 1 & c_{11} & a_{10} & b_{01} \\
0~~ 1~~ 2 & c_{12} & a_{10} & b_{02} \\
\hline \vdots \\ \hline
1~~ 0~~ 0 & c_{00} & a_{01} & b_{10} \\
1~~ 0~~ 1 & c_{01} & a_{01} & b_{11} \\
1~~ 0~~ 2 & c_{02} & a_{01} & b_{12} \\
\hline
\end{array}
$$

From this, it's only more clear why it runs faster than $j-k-i$. Access of $C$ and $B$ is contiguous, and despite $A$ being indexed by column, access is only required every three steps which minimises its performance impact. This allows the CPU to more easily prefetch the next respective rows.

### Transposition
One potential further optimisation is to transpose $B$