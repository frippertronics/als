#include <unity.h>

void setUp(void)
{
    
}

void tearDown(void)
{

}

void test_Sanity(void)
{
    TEST_ASSERT_TRUE(1);
}

int main(void)
{
    UNITY_BEGIN();

    RUN_TEST(test_Sanity);

    return UNITY_END();
}
