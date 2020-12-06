#include "entry_point.h"

#include "gtest/gtest.h"
#include "gmock/gmock.h"

namespace Task03 {
    TEST(PublicAdvanced, VectorSubscriptOperator) {
        Vector v;
        ASSERT_FLOAT_EQ(v[0], float{});

        Vector v2(3.1f);
        ASSERT_FLOAT_EQ(v2[0], 3.1f);

        v2[0] = v2[1] = 4.2f;
        ASSERT_FLOAT_EQ(v2[0], 4.2f);

        const Vector v3 = v2;
        ASSERT_FLOAT_EQ(v3[0], 4.2f);

        v2 = v;
        ASSERT_FLOAT_EQ(v2[0], float{});

        v = v2 = v3;
        ASSERT_FLOAT_EQ(v2[0], 4.2f);
        ASSERT_FLOAT_EQ(v[0], 4.2f);
    }

    TEST(PublicAdvanced, VectorOutOfBound) {
        Vector v;
        EXPECT_THROW(v[Vector::Size()], OutOfBoundException);

        try {
            v[Vector::Size() + 1] = 4;
        } catch (const std::exception& ex) {
            ASSERT_STREQ("Index is out of bounds", ex.what());
        }
    }

    TEST(PublicAdvanced, MatrixSubscriptOperator) {
        Matrix m;
        ASSERT_FLOAT_EQ(m[0][0], float{});

        m[2][1] = m[1][2] = 4.1f;
        ASSERT_FLOAT_EQ(m[1][2], 4.1f);
        ASSERT_FLOAT_EQ(m[2][1], 4.1f);

        auto& row = m[1];
        ASSERT_FLOAT_EQ(row[2], 4.1f);

        row[2] = 2.2f;
        ASSERT_FLOAT_EQ(m[1][2], 2.2f);

        Matrix m2 = m;
        ASSERT_FLOAT_EQ(m2[1][2], 2.2f);
        ASSERT_FLOAT_EQ(m2[2][1], 4.1f);

        Matrix m3;
        m2 = m3;
        ASSERT_FLOAT_EQ(m2[1][2], float{});
        ASSERT_FLOAT_EQ(m2[2][1], float{});

        const auto& row2 = m[2];
        ASSERT_FLOAT_EQ(row2[1], 4.1f);

        m = m2 = m3;
        ASSERT_FLOAT_EQ(row[1], float{});
    }

    TEST(PublicAdvanced, MatrixOutOfBound) {
        Matrix m;
        EXPECT_THROW(m[Matrix::RowsSize()], OutOfBoundException);
    }

    TEST(PublicAdvanced, InitializerList) {
        EXPECT_NO_THROW({
                            Vector v({1, 2, 3});
                        });

        EXPECT_NO_THROW({
                            Matrix m({
                                             {1, 2, 3},
                                             {4, 5, 6},
                                             {7, 8, 9},
                                     });
                        });
    }

    TEST(PublicAdvanced, InitializerList_RangeChecking) {
        EXPECT_THROW({
                            Vector v({1, 2, 3, 4});
                     },
                     OutOfBoundException);
        EXPECT_THROW({
                        Matrix m({
                                         {1, 2, 3, 4}
                                 });
                     },
                     OutOfBoundException);
    }

    TEST(PublicAdvanced, OutputToStream) {
        Matrix m(1.234567f);
        std::ostringstream stream;

        stream << m;
        ASSERT_STREQ(stream.str().c_str(), "((1.235,1.235,1.235),(1.235,1.235,1.235),(1.235,1.235,1.235))");

        Vector v(3.141592);
        std::ostringstream stream2;

        stream2 << v;
        ASSERT_STREQ(stream2.str().c_str(), "(3.142,3.142,3.142)");
    }

    TEST(PublicAdvanced, InputFromStream) {
        Matrix m;
        std::istringstream stream("0 1 2 0 0 0 0 0 0");

        stream >> m;
        ASSERT_FLOAT_EQ(m.x.x, 0.0f);
        ASSERT_FLOAT_EQ(m.x.y, 1.0f);
        ASSERT_FLOAT_EQ(m.x.z, 2.0f);

        Vector v;
        std::istringstream stream2("0 1 2");

        stream2 >> v;
        ASSERT_FLOAT_EQ(v.x, 0.0f);
        ASSERT_FLOAT_EQ(v.y, 1.0f);
        ASSERT_FLOAT_EQ(v.z, 2.0f);
    }

    TEST(PublicAdvanced, SizeConstexpr) {
        Matrix m(4.f);
        float v[m.RowsSize()][m.ColsSize()];

        for (size_t i = 0; i < m.RowsSize(); ++i) {
            for (size_t j = 0; j < m.ColsSize(); ++j) {
                v[i][j] = m[i][j];
            }
        }
    }
}
