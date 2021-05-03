#ifndef IP_FILTER_H
#define IP_FILTER_H

#include <string>
#include <vector>
#include <climits>
#include <iostream>

using StringsVector = std::vector<std::string>;

namespace ip_filter
{

using IpAddr = std::vector<uint8_t>;
using IpPool = std::vector<IpAddr>;

class Filter
{
public:
    void Add(const StringsVector& ip_addrs);
    void Sort();
    void PrintAll(std::ostream& os) const;
    void PrintSortedRange(std::ostream& os, const int first, const int second = INT_MAX) const;
    void PrintSortedValue(std::ostream& os, const int value) const;
private:
    void PrintSingle(std::ostream& os, const IpAddr& ip) const;
    IpPool m_pool;
};

StringsVector split(const std::string& str, const char d);

} // namespace ip_filter

#endif // IP_FILTER_H
