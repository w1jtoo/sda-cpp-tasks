#include "entry_point.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace Task03 {
    TEST(Public, VectorConstructAndAssign) {
        Vector v;
        EXPECT_NEAR(v.x, float{}, 1e-10f);

        Vector v2(3.1f);
        ASSERT_FLOAT_EQ(v2.x, 3.1f);

        v2.x = v2.y = 4.2f;
        ASSERT_FLOAT_EQ(v2.x, 4.2f);

        const Vector v3 = v2;
        ASSERT_FLOAT_EQ(v3.x, 4.2f);

        v2 = v;
        EXPECT_NEAR(v2.x, float{}, 1e-10f);

        v = v2 = v3;
        ASSERT_FLOAT_EQ(v2.x, 4.2f);
        ASSERT_FLOAT_EQ(v.x, 4.2f);
    }

    TEST(Public, VectorOperatorBool) {
        Vector v;
        ASSERT_FALSE(v);
    }

    TEST(Public, VectorUnaryMinus) {
        Vector a(1);

        Vector b = -a;
        ASSERT_FLOAT_EQ(b.x, -1.0f);

        b = - -a;
        ASSERT_FLOAT_EQ(b.x, 1.0f);
    }

    TEST(Public, VectorMinusVector) {
        Vector a(1), b(2);

        a -= b;
        ASSERT_FLOAT_EQ(a.x, -1.0f);

        Vector c = a -= b;
        ASSERT_FLOAT_EQ(a.x, -3.0f);
        ASSERT_FLOAT_EQ(c.x, -3.0f);

        c = a - b;
        ASSERT_FLOAT_EQ(c.x, -5.0f);
    }

    TEST(Public, VectorPlusVector) {
        Vector a(1), b(2);

        a += b;
        ASSERT_FLOAT_EQ(a.x, 3.0f);

        Vector c = a += b;
        ASSERT_FLOAT_EQ(a.x, 5.0f);
        ASSERT_FLOAT_EQ(c.x, 5.0f);

        c = a + b;
        ASSERT_FLOAT_EQ(c.x, 7.0f);
    }

    TEST(Public, VectorMultVector) {
        Vector a(2.f), b(2.f);

        a *= b;
        ASSERT_FLOAT_EQ(a.x, 4.0f);
        ASSERT_FLOAT_EQ(a.y, 4.0f);
        ASSERT_FLOAT_EQ(a.z, 4.0f);

        Vector c = a * b;
        ASSERT_FLOAT_EQ(c.x, 8.0f);
        ASSERT_FLOAT_EQ(c.y, 8.0f);
        ASSERT_FLOAT_EQ(c.z, 8.0f);
    }

    TEST(Public, MatrixConstructAndAssign) {
        Matrix m;
        EXPECT_NEAR(m.x.x, float{}, 1e-10f);

        m.z.y = m.y.z = 4.1f;
        ASSERT_FLOAT_EQ(m.y.z, 4.1f);
        ASSERT_FLOAT_EQ(m.z.y, 4.1f);

        auto& row = m.y;
        ASSERT_FLOAT_EQ(row.z, 4.1f);

        row.z = 2.2f;
        ASSERT_FLOAT_EQ(m.y.z, 2.2f);

        Matrix m2 = m;
        ASSERT_FLOAT_EQ(m2.y.z, 2.2f);
        ASSERT_FLOAT_EQ(m2.z.y, 4.1f);

        Matrix m3;
        m2 = m3;
        EXPECT_NEAR(m2.y.z, float{}, 1e-10f);
        EXPECT_NEAR(m2.z.y, float{}, 1e-10f);

        const auto& row2 = m.z;
        ASSERT_FLOAT_EQ(row2.y, 4.1f);

        m = m2 = m3;
        EXPECT_NEAR(row.y, float{}, 1e-10f);
    }

    TEST(Public, MatrixOperatorBool) {
        Matrix m;
        ASSERT_FALSE(m);
    }

    TEST(Public, MatrixDeterminant) {
        Matrix m(1);
        ASSERT_FLOAT_EQ(~m, 0.0f);

        Matrix e;
        e.x.x = e.y.y = e.z.z = 1.0f;
        ASSERT_FLOAT_EQ(~e, 1.0f);

        Matrix h;
        h.x.x = 2.0f;
        h.x.y = 1.0f;
        h.x.z = 5.0f;
        h.y.x = 4.0f;
        h.y.y = 3.0f;
        h.y.z = 4.0f;
        h.z.x = 5.0f;
        h.z.y = 2.0f;
        h.z.z = 1.0f;

        ASSERT_FLOAT_EQ(~h, -29.0f);
    }

    TEST(Public, MatrixUnaryMinus) {
        Matrix a(1);

        Matrix result = -a;
        ASSERT_FLOAT_EQ(result.x.x, -1.0f);

        result = - -a;
        ASSERT_FLOAT_EQ(result.x.x, 1.0f);
    }

    TEST(Public, MatrixMinusMatrix) {
        Matrix a(1), b(2);

        Matrix result = a - b;
        ASSERT_FLOAT_EQ(result.x.x, -1.0f);

        result -= b;
        ASSERT_FLOAT_EQ(result.x.x, -3.0f);

        result = result -= b;
        ASSERT_FLOAT_EQ(result.x.x, -5.0f);
    }


    TEST(Public, MatrixPlusMatrix) {
        Matrix a(1), b(2);

        Matrix result = a + b;
        ASSERT_FLOAT_EQ(result.x.x, 3.0f);

        result += b;
        ASSERT_FLOAT_EQ(result.x.x, 5.0f);

        result = result += b;
        ASSERT_FLOAT_EQ(result.x.x, 7.0f);
    }

    TEST(Public, MatrixMultMatrix) {
        Matrix a(2), b;
        b.x.x = b.y.y = b.z.z = 2.0f;

        Matrix product = a * b;
        ASSERT_FLOAT_EQ(product.x.x, 4.0f);

        product *= b;
        ASSERT_FLOAT_EQ(product.x.x, 8.0f);
    }

    TEST(Public, MatrixMultVector) {
        Matrix a(2);
        Vector v(2);

        Vector result = a * v;  // 3x1
        ASSERT_FLOAT_EQ(result.x, 12.0f);
    }

    TEST(Public, MatrixMultFloat) {
        Matrix a(2);

        a *= 2.0f;
        ASSERT_FLOAT_EQ(a.x.x, 4.0f);

        Matrix c = a *= 2.0f;
        ASSERT_FLOAT_EQ(c.x.x, 8.0f);
        ASSERT_FLOAT_EQ(a.x.x, 8.0f);

        Matrix result = a * 3.0f;
        ASSERT_FLOAT_EQ(result.x.x, 24.0f);

        result = 3.0f * a;
        ASSERT_FLOAT_EQ(result.x.x, 24.0f);
    }
}
