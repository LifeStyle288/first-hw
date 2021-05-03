#pragma once

#define BOOST_TEST_MODULE test_add_and_sort


#include <boost/test/unit_test.hpp>

#include "ip_filter.h"
#include <sstream>

BOOST_AUTO_TEST_SUITE(test_add_and_sort)

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

    const StringsVector sample = {"1.1.51.189", "1.1.52.188", "2.5.64.21", "2.5.64.23", "3.7.8.251", "10.1.31.71"};

    BOOST_CHECK(sample == values);
}

BOOST_AUTO_TEST_SUITE_END()
