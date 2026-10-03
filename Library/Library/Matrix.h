#pragma once
#include <array>
#include <random>
#include <stdexcept>

// Typing.
enum matrix_structure
{
    nested,
    flat
};
template <typename T, size_t M, size_t N, matrix_structure S> class matrix {};
template <typename T, size_t M, size_t N> using matrix_nested = matrix<T, M, N, nested>;
template <typename T, size_t M, size_t N> using matrix_flat   = matrix<T, M, N, flat>;
template <typename T>                     struct matrix_type_trait                         : std::false_type {};
template <typename T, size_t M, size_t N> struct matrix_type_trait<matrix_nested<T, M, N>> : std::true_type {};
template <typename T, size_t M, size_t N> struct matrix_type_trait<matrix_flat<T, M, N>>   : std::true_type {};
template <typename T> concept matrix_type = matrix_type_trait<T>::value;

template <typename T, size_t M, size_t N>
class matrix<T, M, N, nested>
{
public:
    static constexpr size_t rows = M;
    static constexpr size_t cols = N;
    static constexpr matrix_structure structure = nested;
    static_assert(rows > 0);
    static_assert(cols > 0);

public:
    using value_type      = T;
    using reference       = value_type&;
    using const_reference = const value_type&;

public:
    matrix()
    : _data{}
    {}
    matrix(std::initializer_list<std::initializer_list<T>> data)
    {
        if (data.size() != rows)
            throw std::invalid_argument("matrix_nested::matrix_nested; data-rows do not match template");

        size_t row_idx = 0;
        for (const auto& row : data)
        {
            size_t col_idx = 0;
            if (row.size() != cols)
                throw std::invalid_argument("matrix_nested::matrix_nested; data-cols do not match template");

            for (const auto& value : row)
                _data[row_idx][col_idx++] = value;

            ++row_idx;
        }
    }

public:
    reference operator()(const size_t& i, const size_t& j)
    {
        return _data[i][j];
    }
    const_reference operator()(const size_t& i, const size_t& j) const
    {
        return _data[i][j];
    }

private:
    std::array<std::array<T, M>, N> _data;
};

template <typename T, size_t M, size_t N>
class matrix<T, M, N, flat>
{
public:
    static constexpr size_t rows = M;
    static constexpr size_t cols = N;
    static constexpr matrix_structure structure = nested;
    static_assert(rows > 0);
    static_assert(cols > 0);

public:
    using value_type      = T;
    using reference       = value_type&;
    using const_reference = const value_type&;

public:
    matrix()
    : _data{}
    {}
    template <typename... Args>
    requires (sizeof...(Args) == rows * cols && !(matrix_type<Args> && ...))
    matrix(Args&&... args)
    : _data{ std::forward<Args>(args)... }
    {}

public:
    reference operator()(const size_t& i, const size_t& j)
    {
        return _data[i * cols + j];
    }
    const_reference operator()(const size_t& i, const size_t& j) const
    {
        return _data[i * cols + j];
    }
    reference operator[](const size_t& i)
    {
        return _data[i];
    }
    const_reference operator[](const size_t& i) const
    {
        return _data[i];
    }

private:
    std::array<T, M * N> _data;
};

template <matrix_type M, matrix_type N>
requires (M::cols == N::rows && M::structure == N::structure)
auto multiply_ijk(const M& m, const N& n)
{
    using T = typename M::value_type;
    matrix<T, M::rows, N::cols, M::structure> result;

    for (size_t i = 0; i < M::rows; ++i)
        for (size_t j = 0; j < M::cols; ++j)
            for (size_t k = 0; k < M::cols; ++k)
                result(i, j) += m(i, k) * n(k, j);

    return result;
}
template <matrix_type M, matrix_type N>
requires (M::cols == N::rows && M::structure == N::structure)
auto multiply_jik(const M& m, const N& n)
{
    using T = typename M::value_type;
    matrix<T, M::rows, N::cols, M::structure> result;

    for (size_t j = 0; j < M::cols; ++j)
        for (size_t i = 0; i < M::rows; ++i)
            for (size_t k = 0; k < M::cols; ++k)
                result(i, j) += m(i, k) * n(k, j);

    return result;
}
template <matrix_type M, matrix_type N>
requires (M::cols == N::rows && M::structure == N::structure)
auto multiply_kij(const M& m, const N& n)
{
    using T = typename M::value_type;
    matrix<T, M::rows, N::cols, M::structure> result;

    for (size_t k = 0; k < M::cols; ++k)
        for (size_t i = 0; i < M::rows; ++i)
            for (size_t j = 0; j < M::cols; ++j)
                result(i, j) += m(i, k) * n(k, j);

    return result;
}
template <matrix_type M, matrix_type N>
requires (M::cols == N::rows && M::structure == N::structure)
auto multiply_kji(const M& m, const N& n)
{
    using T = typename M::value_type;
    matrix<T, M::rows, N::cols, M::structure> result;

    for (size_t k = 0; k < M::cols; ++k)
        for (size_t j = 0; j < M::cols; ++j)
            for (size_t i = 0; i < M::rows; ++i)
                result(i, j) += m(i, k) * n(k, j);

    return result;
}
template <matrix_type M, matrix_type N>
requires (M::cols == N::rows && M::structure == N::structure)
auto multiply_ikj(const M& m, const N& n)
{
    using T = typename M::value_type;
    matrix<T, M::rows, N::cols, M::structure> result;

    for (size_t i = 0; i < M::rows; ++i)
        for (size_t k = 0; k < M::cols; ++k)
            for (size_t j = 0; j < M::cols; ++j)
                result(i, j) += m(i, k) * n(k, j);

    return result;
}
template <matrix_type M, matrix_type N>
requires (M::cols == N::rows && M::structure == N::structure)
auto multiply_jki(const M& m, const N& n)
{
    using T = typename M::value_type;
    matrix<T, M::rows, N::cols, M::structure> result;

    for (size_t j = 0; j < M::cols; ++j)
        for (size_t k = 0; k < M::cols; ++k)
            for (size_t i = 0; i < M::rows; ++i)
                result(i, j) += m(i, k) * n(k, j);

    return result;
}

template <matrix_type M>
auto transpose(const M& m)
{
    matrix<typename M::value_type, M::cols, M::rows, M::structure> result;

    for (size_t i = 0; i < M::rows; ++i)
        for (size_t j = 0; j < M::cols; ++j)
            result(i, j) = m(j, i);

    return result;
}

template <matrix_type M, matrix_type N>
requires (M::rows == N::rows && M::cols == N::cols)
bool operator==(const M& m, const N& n)
{
    for (size_t i = 0; i < M::rows; ++i)
        for (size_t j = 0; j < M::cols; ++j)
            if (m(i, j) != n(i, j))
                return false;

    return true;
}

template <typename T>
requires (std::is_arithmetic_v<T>)
T random(T min, T max)
{
    thread_local std::default_random_engine generator;
    std::uniform_real_distribution<T> distribution(min, max);
    return distribution(generator);
}

template <matrix_type M>
auto random(const typename M::value_type& min, const typename M::value_type& max)
{
    M result;
    for (size_t i = 0; i < M::rows; ++i)
        for (size_t j = 0; j < M::cols; ++j)
            result(i, j) = random(min, max);

    return result;
}


