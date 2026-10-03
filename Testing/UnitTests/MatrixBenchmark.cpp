#include "benchmark/benchmark.h"
#include "Matrix.h"

template <size_t N, bool Transpose>
static void BM_MatrixMultiplication_ijk_flat(benchmark::State& state)
{
    auto A = random<matrix_flat<float, N, N>>(0.0f, 1.0f);
    auto B = random<matrix_flat<float, N, N>>(0.0f, 1.0f);

    for (auto _ : state)
    {
        auto C = multiply_ijk(A, B);
        benchmark::DoNotOptimize(C);
    }
}
template <size_t N, bool Transpose>
static void BM_MatrixMultiplication_jik_flat(benchmark::State& state)
{
    auto A = random<matrix_flat<float, N, N>>(0.0f, 1.0f);
    auto B = random<matrix_flat<float, N, N>>(0.0f, 1.0f);

    for (auto _ : state)
    {
        auto C = multiply_jik(A, B);
        benchmark::DoNotOptimize(C);
    }
}
template <size_t N, bool Transpose>
static void BM_MatrixMultiplication_kji_flat(benchmark::State& state)
{
    auto A = random<matrix_flat<float, N, N>>(0.0f, 1.0f);
    auto B = random<matrix_flat<float, N, N>>(0.0f, 1.0f);

    for (auto _ : state)
    {
        auto C = multiply_kji(A, B);
        benchmark::DoNotOptimize(C);
    }
}
template <size_t N, bool Transpose>
static void BM_MatrixMultiplication_kij_flat(benchmark::State& state)
{
    auto A = random<matrix_flat<float, N, N>>(0.0f, 1.0f);
    auto B = random<matrix_flat<float, N, N>>(0.0f, 1.0f);

    for (auto _ : state)
    {
        auto C = multiply_kij(A, B);
        benchmark::DoNotOptimize(C);
    }
}
template <size_t N, bool Transpose>
static void BM_MatrixMultiplication_ikj_flat(benchmark::State& state)
{
    auto A = random<matrix_flat<float, N, N>>(0.0f, 1.0f);
    auto B = random<matrix_flat<float, N, N>>(0.0f, 1.0f);

    for (auto _ : state)
    {
        auto C = multiply_ikj(A, B);
        benchmark::DoNotOptimize(C);
    }
}
template <size_t N, bool Transpose>
static void BM_MatrixMultiplication_jki_flat(benchmark::State& state)
{
    auto A = random<matrix_flat<float, N, N>>(0.0f, 1.0f);
    auto B = random<matrix_flat<float, N, N>>(0.0f, 1.0f);

    for (auto _ : state)
    {
        auto C = multiply_jki(A, B);
        benchmark::DoNotOptimize(C);
    }
}
template <size_t N, bool Transpose>
static void BM_MatrixMultiplication_ijk_nested(benchmark::State& state)
{
    auto A = random<matrix_nested<float, N, N>>(0.0f, 1.0f);
    auto B = random<matrix_nested<float, N, N>>(0.0f, 1.0f);

    for (auto _ : state)
    {
        auto C = multiply_ijk(A, B);
        benchmark::DoNotOptimize(C);
    }
}
template <size_t N, bool Transpose>
static void BM_MatrixMultiplication_jik_nested(benchmark::State& state)
{
    auto A = random<matrix_nested<float, N, N>>(0.0f, 1.0f);
    auto B = random<matrix_nested<float, N, N>>(0.0f, 1.0f);

    for (auto _ : state)
    {
        auto C = multiply_jik(A, B);
        benchmark::DoNotOptimize(C);
    }
}
template <size_t N, bool Transpose>
static void BM_MatrixMultiplication_kij_nested(benchmark::State& state)
{
    auto A = random<matrix_nested<float, N, N>>(0.0f, 1.0f);
    auto B = random<matrix_nested<float, N, N>>(0.0f, 1.0f);

    for (auto _ : state)
    {
        auto C = multiply_kij(A, B);
        benchmark::DoNotOptimize(C);
    }
}
template <size_t N, bool Transpose>
static void BM_MatrixMultiplication_kji_nested(benchmark::State& state)
{
    auto A = random<matrix_nested<float, N, N>>(0.0f, 1.0f);
    auto B = random<matrix_nested<float, N, N>>(0.0f, 1.0f);

    for (auto _ : state)
    {
        auto C = multiply_kji(A, B);
        benchmark::DoNotOptimize(C);
    }
}
template <size_t N, bool Transpose>
static void BM_MatrixMultiplication_ikj_nested(benchmark::State& state)
{
    auto A = random<matrix_nested<float, N, N>>(0.0f, 1.0f);
    auto B = random<matrix_nested<float, N, N>>(0.0f, 1.0f);

    for (auto _ : state)
    {
        auto C = multiply_ikj(A, B);
        benchmark::DoNotOptimize(C);
    }
}
template <size_t N, bool Transpose>
static void BM_MatrixMultiplication_jki_nested(benchmark::State& state)
{
    auto A = random<matrix_nested<float, N, N>>(0.0f, 1.0f);
    auto B = random<matrix_nested<float, N, N>>(0.0f, 1.0f);

    for (auto _ : state)
    {
        auto C = multiply_jki(A, B);
        benchmark::DoNotOptimize(C);
    }
}


BENCHMARK_TEMPLATE(BM_MatrixMultiplication_ijk_flat, 64, false);
BENCHMARK_TEMPLATE(BM_MatrixMultiplication_jik_flat, 64, false);
BENCHMARK_TEMPLATE(BM_MatrixMultiplication_kij_flat, 64, false);
BENCHMARK_TEMPLATE(BM_MatrixMultiplication_kji_flat, 64, false);
BENCHMARK_TEMPLATE(BM_MatrixMultiplication_ikj_flat, 64, false);
BENCHMARK_TEMPLATE(BM_MatrixMultiplication_jki_flat, 64, false);
BENCHMARK_TEMPLATE(BM_MatrixMultiplication_ijk_nested, 64, false);
BENCHMARK_TEMPLATE(BM_MatrixMultiplication_jik_nested, 64, false);
BENCHMARK_TEMPLATE(BM_MatrixMultiplication_kij_nested, 64, false);
BENCHMARK_TEMPLATE(BM_MatrixMultiplication_kji_nested, 64, false);
BENCHMARK_TEMPLATE(BM_MatrixMultiplication_ikj_nested, 64, false);
BENCHMARK_TEMPLATE(BM_MatrixMultiplication_jki_nested, 64, false);
BENCHMARK_MAIN();