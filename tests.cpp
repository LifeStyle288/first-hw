#define BOOST_TEST_MODULE tests

#include <boost/test/unit_test.hpp>

#include <sstream>
#include "lib.h"
#include "ip_filter.h"

BOOST_AUTO_TEST_SUITE(tests)

BOOST_AUTO_TEST_CASE(test_valid_version)
{
    BOOST_CHECK(version() > 0);
}

BOOST_AUTO_TEST_CASE(test_add_and_sort)
{
    ip_filter::Filter filter;
    filter.Add(ip_filter::split("10.1.31.71", '.'));
    filter.Add(ip_filter::split("1.1.52.188", '.'));
    filter.Add(ip_filter::split("1.1.51.189", '.'));
    filter.Add(ip_filter::split("2.5.64.21", '.'));
    filter.Add(ip_filter::split("2.5.64.23", '.'));
    filter.Add(ip_filter::split("3.7.8.251", '.'));

    filter.Sort();

    std::ostringstream os;

    filter.PrintAll(os);

    const StringsVector values(ip_filter::split(os.str(), '\n'));
    const StringsVector sample = {"10.1.31.71", "3.7.8.251", "2.5.64.23", "2.5.64.21", "1.1.52.188", "1.1.51.189"};
    BOOST_CHECK_EQUAL_COLLECTIONS(sample.begin(), sample.end(), values.begin(), values.end());
}

BOOST_AUTO_TEST_CASE(test_sort_range)
{
    ip_filter::Filter filter;
    filter.Add(ip_filter::split("10.1.31.71", '.'));
    filter.Add(ip_filter::split("1.1.52.188", '.'));
    filter.Add(ip_filter::split("1.1.51.189", '.'));
    filter.Add(ip_filter::split("2.5.64.21", '.'));
    filter.Add(ip_filter::split("2.5.64.23", '.'));
    filter.Add(ip_filter::split("3.7.8.251", '.'));
    filter.Add(ip_filter::split("3.7.52.145", '.'));
    filter.Add(ip_filter::split("3.7.58.156", '.'));
    filter.Add(ip_filter::split("3.7.165.121", '.'));
    filter.Add(ip_filter::split("3.7.54.165", '.'));
    filter.Add(ip_filter::split("3.7.98.97", '.'));
    filter.Add(ip_filter::split("3.7.80.80", '.'));
    filter.Add(ip_filter::split("3.5.45.45", '.'));
    filter.Add(ip_filter::split("3.6.78.187", '.'));
    filter.Add(ip_filter::split("3.9.11.1", '.'));
    filter.Add(ip_filter::split("3.10.25.238", '.'));

    filter.Sort();

    {
        std::ostringstream os;

        filter.PrintSortedRange(os, 3, 7);

        const StringsVector values(ip_filter::split(os.str(), '\n'));
        const StringsVector sample = {"3.7.165.121", "3.7.98.97", "3.7.80.80", "3.7.58.156", "3.7.54.165", "3.7.52.145", "3.7.8.251"};
        BOOST_CHECK_EQUAL_COLLECTIONS(sample.begin(), sample.end(), values.begin(), values.end());
    }

    {
        std::ostringstream os;

        filter.PrintSortedRange(os, 3);

        const StringsVector values(ip_filter::split(os.str(), '\n'));
        const StringsVector sample = {"3.10.25.238", "3.9.11.1", "3.7.165.121", "3.7.98.97", "3.7.80.80", "3.7.58.156",
                                      "3.7.54.165", "3.7.52.145", "3.7.8.251", "3.6.78.187", "3.5.45.45"};
        BOOST_CHECK_EQUAL_COLLECTIONS(sample.begin(), sample.end(), values.begin(), values.end());
    }
}

BOOST_AUTO_TEST_SUITE_END()
