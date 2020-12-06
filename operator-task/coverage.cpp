#include "entry_point.h"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#define ASSERT_VECTOR_EQ(v1,v2) ASSERT_TRUE(\
        v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)

#define ASSERT_MATRIX_EQ(m1,m2) ASSERT_TRUE(\
        m1.x.x == m2.x.x && m1.x.y == m2.x.y && m1.x.z == m2.x.z &&\
        m1.y.x == m2.y.x && m1.y.y == m2.y.y && m1.y.z == m2.y.z &&\
        m1.z.x == m2.z.x && m1.z.y == m2.z.y && m1.z.z == m2.z.z)

#define V(f) Vector(f)
#define M(f1,f2,f3) Matrix(Vector(f1), Vector(f2), Vector(f3));

namespace Example {
    const auto zero = Vector();
    const auto one = Vector(1.f);

/* ------------------ Vector Tests --------------------*/
/* ------------------------------- --------------------*/

    TEST(Public, VectorCopy) {
        auto v = Vector(1.f, 2.f, 3.f);
        auto moved = std::move(v);

        ASSERT_VECTOR_EQ(v, moved);
    }

    TEST(Public, VectorSum) {
        auto a = Vector(1.f, 2.f, 3.f);

        auto actual = a + zero;
        auto expected  = a;
        ASSERT_VECTOR_EQ(actual, expected);

        actual = zero + a;
        expected  = a;
        ASSERT_VECTOR_EQ(actual, expected);

        actual = a + a;
        expected = Vector(2.f, 4.f, 6.f);
        ASSERT_VECTOR_EQ(actual, expected);

        actual += a;
        expected = Vector(3.f, 6.f, 9.f);
        ASSERT_VECTOR_EQ(actual, expected);
    }

    TEST(Public, VectorSub) {
        auto actual = one - zero;
        auto expected  = one;
        ASSERT_VECTOR_EQ(actual, expected);

        actual = zero - one;
        expected  = Vector(-1.f);
        ASSERT_VECTOR_EQ(actual, expected);

        actual = one - one;
        expected = zero;
        ASSERT_VECTOR_EQ(actual, expected);

        actual -= one;
        expected = Vector(-1.f);
        ASSERT_VECTOR_EQ(actual, expected);
    }

    TEST(Public, VectorBool) {
        ASSERT_TRUE(one);
        ASSERT_FALSE(zero);

        for (int x = -1; x < 3; ++x)
        for (int y = -1; y < 3; ++y)
        for (int z = -1; z < 3; ++z){
            if (x == y && y == z && z == 0)
                break;

            auto actual = Vector((float) x,(float) y,(float) z);
            ASSERT_TRUE(actual);
        }
    }

    TEST(Public, Vector_Vector_Mul) {
        auto actual = one * zero;
        auto expected  = zero;
        ASSERT_VECTOR_EQ(actual, expected);

        actual = zero * one;
        expected  = zero;
        ASSERT_VECTOR_EQ(actual, expected);

        actual = one * one;
        expected = one;
        ASSERT_VECTOR_EQ(actual, expected);

        actual = Vector(3.f, 2.f, 1.f) * Vector(1.f, 2.f, 3.f);
        expected = Vector(3.f, 4.f, 3.f);
        ASSERT_VECTOR_EQ(actual, expected);

        actual *= Vector(4.f, 3.f, 4.f);
        expected = Vector(12.f);
        ASSERT_VECTOR_EQ(actual, expected);
    }

    TEST(Public, Vector_Float_Mul) {
        auto actual = one * 42.f;
        auto expected = Vector(42.f);
        ASSERT_VECTOR_EQ(actual, expected);

        actual = 42.f * one;
        expected = Vector(42.f);
        ASSERT_VECTOR_EQ(actual, expected);

        actual = 3.f * Vector(1.f, 2.f, 3.f);
        expected = Vector(3.f, 6.f, 9.f);
        ASSERT_VECTOR_EQ(actual, expected);

        actual *= 3.f;
        expected = Vector(9.f, 18.f, 27.f);
        ASSERT_VECTOR_EQ(actual, expected);
    }

    TEST(Public, Negative) {
        auto actual = -one;
        auto expected = Vector(-1.f);
        ASSERT_VECTOR_EQ(actual, expected);

        actual = -actual;
        expected = one;
        ASSERT_VECTOR_EQ(actual, expected);

        actual = -Vector(1.f, 2.f, 3.f);
        expected = Vector(-1.f, -2.f, -3.f);
        ASSERT_VECTOR_EQ(actual, expected);
    }

/* ------------------ Matrix Tests --------------------*/
/* ------------------------------- --------------------*/

    TEST(Public, MatrixMove) {
        auto m = Matrix(3.f);
        auto moved = std::move(m);
        ASSERT_MATRIX_EQ(m, moved);
    }

    TEST(Public, MatrixMultiplication) {
        Matrix m = Matrix(3.f);
        const Vector v9f = Vector(9.f);

        Matrix a = m * 3.f;
        ASSERT_VECTOR_EQ(a.x, v9f);
        ASSERT_VECTOR_EQ(a.y, v9f);
        ASSERT_VECTOR_EQ(a.z, v9f);

        Matrix b = 3.f * m;
        ASSERT_VECTOR_EQ(b.x, v9f);
        ASSERT_VECTOR_EQ(b.y, v9f);
        ASSERT_VECTOR_EQ(b.z, v9f);
    }

    auto zeroMatrix = Matrix(0.f);
    auto oneMatrix = Matrix(1.f);

    TEST(Public, MatrixSum) {
        auto a = M(1.f, 2.f, 3.f);

        auto actual = a + zeroMatrix;
        auto expected  = a;
        ASSERT_MATRIX_EQ(actual, expected);

        actual = zeroMatrix + a;
        expected  = a;
        ASSERT_MATRIX_EQ(actual, expected);

        actual = a + a;
        expected = M(2.f, 4.f, 6.f);
        ASSERT_MATRIX_EQ(actual, expected);

        actual += a;
        expected = M(3.f, 6.f, 9.f);
        ASSERT_MATRIX_EQ(actual, expected);
    }

    TEST(Public, MatrixNegative) {
        auto actual = -oneMatrix;
        auto expected = Matrix(-1.f);
        ASSERT_MATRIX_EQ(actual, expected);

        actual = -actual;
        expected = oneMatrix;
        ASSERT_MATRIX_EQ(actual, expected);

        actual = -M(1.f, 2.f, 3.f);
        expected = M(-1.f, -2.f, -3.f);
        ASSERT_MATRIX_EQ(actual, expected);
    }

    TEST(Public, Matrix_Float_Mul) {
        auto actual = oneMatrix * 42.f;
        auto expected = Matrix(42.f);
        ASSERT_MATRIX_EQ(actual, expected);

        actual = 42.f * oneMatrix;
        expected = Matrix(42.f);
        ASSERT_MATRIX_EQ(actual, expected);

        actual = 3.f * M(1.f, 2.f, 3.f);
        expected = M(3.f, 6.f, 9.f);
        ASSERT_MATRIX_EQ(actual, expected);

        actual *= 3.f;
        expected = M(9.f, 18.f, 27.f);
        ASSERT_MATRIX_EQ(actual, expected);
    }

    TEST(Public, MatrixSub) {
        auto actual = oneMatrix - zeroMatrix;
        auto expected  = oneMatrix;
        ASSERT_MATRIX_EQ(actual, expected);

        actual = zeroMatrix - oneMatrix;
        expected  = Matrix(-1.f);
        ASSERT_MATRIX_EQ(actual, expected);

        actual = oneMatrix - oneMatrix;
        expected = zeroMatrix;
        ASSERT_MATRIX_EQ(actual, expected);

        actual -= oneMatrix;
        expected = Matrix(-1.f);
        ASSERT_MATRIX_EQ(actual, expected);
    }

    TEST(Public, Matrix_Matrix_Mul) {
        auto actual = oneMatrix * zeroMatrix;
        auto expected  = zeroMatrix;
        ASSERT_MATRIX_EQ(actual, expected);

        actual = zeroMatrix * oneMatrix;
        expected  = zeroMatrix;
        ASSERT_MATRIX_EQ(actual, expected);

        actual = oneMatrix * oneMatrix;
        expected = oneMatrix;
        ASSERT_MATRIX_EQ(actual, expected);

        auto a =  M(3.f, 2.f, 1.f);
        auto b = M(1.f, 2.f, 3.f);
        actual = a * b;
        expected = M(3.f, 4.f, 3.f);
        ASSERT_MATRIX_EQ(actual, expected);

        actual *= M(4.f, 3.f, 4.f);
        expected = Matrix(12.f);
        ASSERT_MATRIX_EQ(actual, expected);
    }

    //TEST(Public, Matrix_Vector_Mul) {
    //    auto actual = oneMatrix * one;
    //    auto expected  = one;
    //    ASSERT_VECTOR_EQ(actual, expected);

    //    auto a =  M(3.f, 2.f, 1.f);
    //    auto b = Vector(1.f, 2.f, 3.f);
    //    actual = a * b;
    //    expected = Vector(18.f, 12.f, 6.f);
    //    ASSERT_VECTOR_EQ(actual, expected);
    //}
}
