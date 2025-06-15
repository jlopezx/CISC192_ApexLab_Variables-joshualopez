//
// Don't modify code in this file, with the exception
// of adding test cases.
//
#include <cassert>
#include <iostream>
#include "apex_code.h"

using namespace std;

static int testNum = 0;
static int testsPassed = 0;

#define TEST_FUNC_PTR void (*test_func)(stringstream&, stringstream&)
void test(TEST_FUNC_PTR, const string& input, const string& expected)
{
    testNum++;
    stringstream in_stream(input);
    stringstream out_stream;
    test_func(in_stream, out_stream);

    cout << "test " << testNum << ": ";
    
    if(expected == out_stream.str())
    {
        cout << "PASS" << endl;
        testsPassed++;
    }
    else
    {
        cout << "With input \"" << input << "\" expected output \"" << expected
            << "\", received \"" << out_stream.str() << "\"" << endl;
    }
}

int main()
{
    // To add a test case, duplicate one of the test lines below
    // modify input with the first string, and the expected output
    // in the second string.

    // Testing minutes to 12 hour time
    // Zero test
    test(minutes_to_12hour_time, "0", "0:0 !");
    // Just minutes test
    test(minutes_to_12hour_time, "10", "0:10 !");
    // Just hours test
    test(minutes_to_12hour_time, "60", "1:0 !");
    // Hours and minutes test
    test(minutes_to_12hour_time, "61", "1:1 !");
    // More than one hour test
    test(minutes_to_12hour_time, "121", "2:1 !");
    // More than 12 hour test
    test(minutes_to_12hour_time, "785", "1:5 !");
    // 24 hour test
    test(minutes_to_12hour_time, "1441", "0:1 !");
    // More than 24 hour test
    test(minutes_to_12hour_time, "45678", "5:18 !");

    // Testing hours minutes seconds to 12 hour time
    // Zero test
    test(numbers_to_12hour_time, "0 0 0", "0:0.0 !");
    // Nominal test
    test(numbers_to_12hour_time, "1 1 1", "1:1.1 !");
    // Seconds to minutes
    test(numbers_to_12hour_time, "0 0 60", "0:1.0 !");
    // Seconds to hours
    test(numbers_to_12hour_time, "0 0 3600", "1:0.0 !");
    // Minutes to hours
    test(numbers_to_12hour_time, "0 60 0", "1:0.0 !");
    // Second and minutes to hours
    test(numbers_to_12hour_time, "0 59 60", "1:0.0 !");
    // Decimal hours
    test(numbers_to_12hour_time, "60.5 60 60", "1:31.0 !");
    // High precision decimal hours
    test(numbers_to_12hour_time, "129000.25834 100 2", "1:55.32 !");

    // Random tests
    test(numbers_to_12hour_time, "1 121 12", "3:1.12 !");
    test(numbers_to_12hour_time, "1.1 121 12", "3:7.12 !");
    test(numbers_to_12hour_time, "60.51 60 3605", "2:30.41 !");
    test(numbers_to_12hour_time, "10 600 24", "8:0.24 !");

    if (testNum != 20) {
        cout << "Some tests are missing :( Check your code again, and please don't modify testbench.cpp!" << endl;
    } else if (testsPassed != 20) {
        cout << "Some tests did not pass :(" << endl;
    } else {
        cout << "All tests passed! Hooray! 🥳" << endl;
    }
    
    return 0;
}
