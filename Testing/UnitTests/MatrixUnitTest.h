#pragma once
#include "gtest/gtest.h"
#include "benchmark/benchmark.h"
#include "Matrix.h"

// class MatrixUnitTest : public ::testing::Test {};

TEST(MatrixUnitTest, MatrixMultiplication)
{
    matrix_nested<float, 2, 2> M_nested({{ 1.0f, 2.0f },
                                         { 3.0f, 4.0f }});
    matrix_nested<float, 2, 2> N_nested({{ 5.0f, 6.0f },
                                         { 7.0f, 8.0f }});
    matrix_nested<float, 2, 2> O_nested({{ 19.0f, 22.0f },
                                         { 43.0f, 50.0f }});
    matrix_flat<float, 2, 2> M_flat( 1.0f, 2.0f,
                                     3.0f, 4.0f );
    matrix_flat<float, 2, 2> N_flat( 5.0f, 6.0f,
                                     7.0f, 8.0f );
    matrix_flat<float, 2, 2> O_flat( 19.0f, 22.0f,
                                     43.0f, 50.0f );

    ASSERT_EQ(multiply_ijk(M_nested, N_nested), O_nested);
    ASSERT_EQ(multiply_ijk(M_flat, N_flat), O_flat);
    ASSERT_EQ(multiply_jik(M_nested, N_nested), O_nested);
    ASSERT_EQ(multiply_jik(M_flat, N_flat), O_flat);
    ASSERT_EQ(multiply_kij(M_nested, N_nested), O_nested);
    ASSERT_EQ(multiply_kij(M_flat, N_flat), O_flat);
}