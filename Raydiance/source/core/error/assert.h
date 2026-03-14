#pragma once
#include <iostream>

#define RA_ASSERT(expr) \
do { \
    if (!(expr)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT failed\n"; \
        std::cerr << "  Expression: " << #expr << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_ASSERT_MSG(expr, msg) \
do { \
    if (!(expr)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_MSG failed\n"; \
        std::cerr << "  Expression: " << #expr << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_ASSERT_TRUE(expr) \
do { \
    if (!(expr)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_TRUE failed\n"; \
        std::cerr << "  Expression: " << #expr << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_ASSERT_TRUE_MSG(expr, msg) \
do { \
    if (!(expr)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_TRUE_MSG failed\n"; \
        std::cerr << "  Expression: " << #expr << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_EXPECT_TRUE(expr) \
do { \
    if (!(expr)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_TRUE failed\n"; \
        std::cerr << "  Expression: " << #expr << "\n"; \
    } \
} while(false)

#define RA_EXPECT_TRUE_MSG(expr, msg) \
do { \
    if (!(expr)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_TRUE_MSG failed\n"; \
        std::cerr << "  Expression: " << #expr << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
    } \
} while(false)

#define RA_ASSERT_FALSE(expr) \
do { \
    if (expr) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_FALSE failed\n"; \
        std::cerr << "  Expression: " << #expr << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_ASSERT_FALSE_MSG(expr, msg) \
do { \
    if (expr) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_FALSE_MSG failed\n"; \
        std::cerr << "  Expression: " << #expr << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_EXPECT_FALSE(expr) \
do { \
    if (expr) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_FALSE failed\n"; \
        std::cerr << "  Expression: " << #expr << "\n"; \
    } \
} while(false)

#define RA_EXPECT_FALSE_MSG(expr, msg) \
do { \
    if (expr) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_FALSE_MSG failed\n"; \
        std::cerr << "  Expression: " << #expr << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
    } \
} while(false)

#define RA_ASSERT_EQ(a, b) \
do { \
    if (a != b) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_EQ failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_ASSERT_EQ_MSG(a, b, msg) \
do { \
    if (a != b) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_EQ failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_EXPECT_EQ(a, b) \
do { \
    if (a != b) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_EQ failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
    } \
} while(false)

#define RA_EXPECT_EQ_MSG(a, b, msg) \
do { \
    if (a != b) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_EQ_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
    } \
} while(false)

#define RA_ASSERT_NEQ(a, b) \
do { \
    if (a == b) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_NEQ failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_ASSERT_NEQ_MSG(a, b, msg) \
do { \
    if (a == b) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_NEQ failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_EXPECT_NEQ(a, b) \
do { \
    if (a == b) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_NEQ failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
    } \
} while(false)

#define RA_EXPECT_NEQ_MSG(a, b, msg) \
do { \
    if (a == b) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_NEQ_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
    } \
} while(false)

// ---------------- Comparison ----------------
#define RA_ASSERT_LT(a,b) \
do { \
    if ((a) >= (b)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_LT failed\n"; \
        std::cerr << "  Expression: " << #a << " < " << #b << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_ASSERT_LT_MSG(a,b,msg) \
do { \
    if ((a) >= (b)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_LT_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " < " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_EXPECT_LT(a,b) \
do { \
    if ((a) >= (b)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_LT failed\n"; \
        std::cerr << "  Expression: " << #a << " < " << #b << "\n"; \
    } \
} while(false)

#define RA_EXPECT_LT_MSG(a,b,msg) \
do { \
    if ((a) >= (b)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_LT_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " < " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
    } \
} while(false)

#define RA_ASSERT_LE(a,b) \
do { \
    if ((a) > (b)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_LE failed\n"; \
        std::cerr << "  Expression: " << #a << " <= " << #b << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_ASSERT_LE_MSG(a,b,msg) \
do { \
    if ((a) > (b)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_LE_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " <= " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_EXPECT_LE(a,b) \
do { \
    if ((a) > (b)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_LE failed\n"; \
        std::cerr << "  Expression: " << #a << " <= " << #b << "\n"; \
    } \
} while(false)

#define RA_EXPECT_LE_MSG(a,b,msg) \
do { \
    if ((a) > (b)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_LE_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " <= " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
    } \
} while(false)

#define RA_ASSERT_GT(a,b) \
do { \
    if ((a) <= (b)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_GT failed\n"; \
        std::cerr << "  Expression: " << #a << " > " << #b << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_ASSERT_GT_MSG(a,b,msg) \
do { \
    if ((a) <= (b)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_GT_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " > " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_EXPECT_GT(a,b) \
do { \
    if ((a) <= (b)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_GT failed\n"; \
        std::cerr << "  Expression: " << #a << " > " << #b << "\n"; \
    } \
} while(false)

#define RA_EXPECT_GT_MSG(a,b,msg) \
do { \
    if ((a) <= (b)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_GT_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " > " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
    } \
} while(false)

#define RA_ASSERT_GE(a,b) \
do { \
    if ((a) < (b)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_GE failed\n"; \
        std::cerr << "  Expression: " << #a << " >= " << #b << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_ASSERT_GE_MSG(a,b,msg) \
do { \
    if ((a) < (b)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_GE_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " >= " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_EXPECT_GE(a,b) \
do { \
    if ((a) < (b)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_GE failed\n"; \
        std::cerr << "  Expression: " << #a << " >= " << #b << "\n"; \
    } \
} while(false)

#define RA_EXPECT_GE_MSG(a,b,msg) \
do { \
    if ((a) < (b)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_GE_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " >= " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
    } \
} while(false)

// ---------------- String Comparisons ----------------
#define RA_ASSERT_STREQ(a,b) \
do { \
    if (std::strcmp((a),(b)) != 0) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_STREQ failed\n"; \
        std::cerr << "  Expression: " << #a << " == " << #b << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_ASSERT_STREQ_MSG(a,b,msg) \
do { \
    if (std::strcmp((a),(b)) != 0) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_STREQ_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " == " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_EXPECT_STREQ(a,b) \
do { \
    if (std::strcmp((a),(b)) != 0) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_STREQ failed\n"; \
        std::cerr << "  Expression: " << #a << " == " << #b << "\n"; \
    } \
} while(false)

#define RA_EXPECT_STREQ_MSG(a,b,msg) \
do { \
    if (std::strcmp((a),(b)) != 0) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_STREQ_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " == " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
    } \
} while(false)

#define RA_ASSERT_STRNE(a,b) \
do { \
    if (std::strcmp((a),(b)) == 0) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_STRNE failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_ASSERT_STRNE_MSG(a,b,msg) \
do { \
    if (std::strcmp((a),(b)) == 0) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_STRNE_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_EXPECT_STRNE(a,b) \
do { \
    if (std::strcmp((a),(b)) == 0) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_STRNE failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
    } \
} while(false)

#define RA_EXPECT_STRNE_MSG(a,b,msg) \
do { \
    if (std::strcmp((a),(b)) == 0) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_STRNE_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
    } \
} while(false)

// ---------------- Floating Point ----------------
#define RA_ASSERT_NEAR(a,b,eps) \
do { \
    if (std::fabs((a)-(b)) > (eps)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_NEAR failed\n"; \
        std::cerr << "  Expression: |" << #a << " - " << #b << "| <= " << #eps << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_ASSERT_NEAR_MSG(a,b,eps,msg) \
do { \
    if (std::fabs((a)-(b)) > (eps)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_NEAR_MSG failed\n"; \
        std::cerr << "  Expression: |" << #a << " - " << #b << "| <= " << #eps << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_EXPECT_NEAR(a,b,eps) \
do { \
    if (std::fabs((a)-(b)) > (eps)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_NEAR failed\n"; \
        std::cerr << "  Expression: |" << #a << " - " << #b << "| <= " << #eps << "\n"; \
    } \
} while(false)

#define RA_EXPECT_NEAR_MSG(a,b,eps,msg) \
do { \
    if (std::fabs((a)-(b)) > (eps)) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_NEAR_MSG failed\n"; \
        std::cerr << "  Expression: |" << #a << " - " << #b << "| <= " << #eps << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
    } \
} while(false)

#define RA_ASSERT_FLOAT_EQ(a,b) \
do { \
    if (std::fabs((a)-(b)) > 1e-6) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_FLOAT_EQ failed\n"; \
        std::cerr << "  Expression: " << #a << " == " << #b << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_ASSERT_FLOAT_EQ_MSG(a,b,msg) \
do { \
    if (std::fabs((a)-(b)) > 1e-6) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_FLOAT_EQ_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " == " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_EXPECT_FLOAT_EQ(a,b) \
do { \
    if (std::fabs((a)-(b)) > 1e-6) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_FLOAT_EQ failed\n"; \
        std::cerr << "  Expression: " << #a << " == " << #b << "\n"; \
    } \
} while(false)

#define RA_EXPECT_FLOAT_EQ_MSG(a,b,msg) \
do { \
    if (std::fabs((a)-(b)) > 1e-6) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_FLOAT_EQ_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " == " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
    } \
} while(false)

#define RA_ASSERT_FLOAT_NEQ(a,b) \
do { \
    if (std::fabs((a)-(b)) <= 1e-6) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_FLOAT_NEQ failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_ASSERT_FLOAT_NEQ_MSG(a,b,msg) \
do { \
    if (std::fabs((a)-(b)) <= 1e-6) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_FLOAT_NEQ_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_EXPECT_FLOAT_NEQ(a,b) \
do { \
    if (std::fabs((a)-(b)) <= 1e-6) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_FLOAT_NEQ failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
    } \
} while(false)

#define RA_EXPECT_FLOAT_NEQ_MSG(a,b,msg) \
do { \
    if (std::fabs((a)-(b)) <= 1e-6) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_FLOAT_NEQ_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
    } \
} while(false)

// ---------------- Double Precision ----------------
#define RA_ASSERT_DOUBLE_EQ(a,b) \
do { \
    if (std::fabs((a)-(b)) > 1e-12) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_DOUBLE_EQ failed\n"; \
        std::cerr << "  Expression: " << #a << " == " << #b << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_ASSERT_DOUBLE_EQ_MSG(a,b,msg) \
do { \
    if (std::fabs((a)-(b)) > 1e-12) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_DOUBLE_EQ_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " == " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_EXPECT_DOUBLE_EQ(a,b) \
do { \
    if (std::fabs((a)-(b)) > 1e-12) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_DOUBLE_EQ failed\n"; \
        std::cerr << "  Expression: " << #a << " == " << #b << "\n"; \
    } \
} while(false)

#define RA_EXPECT_DOUBLE_EQ_MSG(a,b,msg) \
do { \
    if (std::fabs((a)-(b)) > 1e-12) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_DOUBLE_EQ_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " == " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
    } \
} while(false)

#define RA_ASSERT_DOUBLE_NEQ(a,b) \
do { \
    if (std::fabs((a)-(b)) <= 1e-12) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_DOUBLE_NEQ failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_ASSERT_DOUBLE_NEQ_MSG(a,b,msg) \
do { \
    if (std::fabs((a)-(b)) <= 1e-12) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_ASSERT_DOUBLE_NEQ_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
        std::abort(); \
    } \
} while(false)

#define RA_EXPECT_DOUBLE_NEQ(a,b) \
do { \
    if (std::fabs((a)-(b)) <= 1e-12) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_DOUBLE_NEQ failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
    } \
} while(false)

#define RA_EXPECT_DOUBLE_NEQ_MSG(a,b,msg) \
do { \
    if (std::fabs((a)-(b)) <= 1e-12) { \
        std::cerr << __FILE__ << ":" << __LINE__ << "\n"; \
        std::cerr << "RA_EXPECT_DOUBLE_NEQ_MSG failed\n"; \
        std::cerr << "  Expression: " << #a << " != " << #b << "\n"; \
        std::cerr << "  Message: " << msg << "\n"; \
    } \
} while(false)