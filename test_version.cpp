#define BOOST_TEST_MODULE test_version

#include <sstream>

#include "lib.h"
#include "ip_filter.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(test_version)

BOOST_AUTO_TEST_CASE(test_valid_version)
{
    BOOST_CHECK(version() > 0);
}

// BOOST_AUTO_TEST_CASE(add_and_sort_test)
// {
//     ip_filter::Filter filter;
//     filter.Add(ip_filter::split("10.1.31.71", '.'));
//     filter.Add(ip_filter::split("1.1.52.188", '.'));
//     filter.Add(ip_filter::split("1.1.51.189", '.'));
//     filter.Add(ip_filter::split("2.5.64.21", '.'));
//     filter.Add(ip_filter::split("2.5.64.23", '.'));
//     filter.Add(ip_filter::split("3.7.8.251", '.'));

//     filter.Sort();

//     std::ostringstream os;

//     filter.PrintAll(os);

//     const StringsVector values(ip_filter::split(os.str(), '\n'));

//     const StringsVector sample = {"1.1.51.189", "1.1.52.188", "2.5.64.21", "2.5.64.23", "3.7.8.251", "10.1.31.71"};

//     BOOST_CHECK(sample == values);
// }

}
