#if WITH_UNIT_TESTS && SOLUTION == 1

#include "solution.cpp"

#include <iostream>

void fail(const char* message)
{
    std::cerr << "Test failed: " << message << std::endl;
    std::terminate();
}

void test_true(bool test, const char* message)
{
    if (test)
    {
        return;
    }
    fail(message);
}

template <typename T>
void test_equal(T lhs, T rhs, const char* message)
{
    if (lhs == rhs)
    {
        return;
    }
    std::cerr << "test_equal failed for \n" << lhs << '\n' << rhs << std::endl;
    fail(message);
}

template <>
void test_equal(score_16t lhs, score_16t rhs, const char* message)
{
    if (all_true(lhs == rhs))
    {
        return;
    }
    std::cerr << "test_equal failed for \n" << lhs << '\n' << rhs << std::endl;
    fail(message);
}

int main()
{
    // Init broadcast.
    {
        score_16t actual {broadcast(1)};
        score_16t expected {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
        test_equal(actual, expected, "Inti broadcast");
    }

    // Max.
    {
        score_16t a = {1, 20, 3, 40, 1, 20, 3, 40, 1, 20, 3, 40, 1, 20, 3, 40};
        score_16t b = {10, 2, 30, 4, 10, 2, 30, 4, 10, 2, 30, 4, 10, 2, 30, 4};
        score_16t actual = max(a, b);
        score_16t expected {10, 20, 30, 40, 10, 20, 30, 40, 10, 20, 30, 40, 10, 20, 30, 40};
        test_equal(actual, expected, "Max");
    }
    return 0;
}
#else

#if WITH_UNIT_TESTS
int main()
{
    // Don't have any unit tests for the given solutions yet, so just return
    // immediately.
    return 0;
}
#endif
#endif
