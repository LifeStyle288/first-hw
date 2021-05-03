#include "ip_filter.h"

#include <algorithm>
#include <iterator>
#include <cassert>

namespace ip_filter
{

void Filter::Add(const StringsVector& ip_addrs)
{
    IpAddr r;
    for (const auto& ip_addr : ip_addrs)
    {
        r.emplace_back(std::stoi(ip_addr));
    }
    m_pool.emplace_back(r);
}

void Filter::Sort()
{
    std::sort(m_pool.begin(), m_pool.end(), [](const auto& lhs, const auto& rhs){
        assert(lhs.size() == rhs.size());
        for (size_t idx = 0; idx < lhs.size(); ++idx)
        {
            if (lhs[idx] == rhs[idx])
            {
                continue;
            }
            return lhs[idx] > rhs[idx];
        }
        return false;
    });
}

void Filter::PrintAll(std::ostream& os) const
{
    for (auto ip = m_pool.cbegin(); ip != m_pool.cend(); ++ip)
    {
        PrintSingle(os, *ip);
        os << '\n';
    }
}

void Filter::PrintSortedRange(std::ostream& os, const int first, const int second) const
{
    for (auto ip = m_pool.cbegin(); ip != m_pool.cend(); ++ip)
    {
        if (*(ip->cbegin()) == first)
        {
            if ((second != INT_MAX && *(std::next(ip->cbegin())) == second) || second == INT_MAX)
            {
                PrintSingle(os, *ip);
                os << '\n';
            }
        }
    }
}

void Filter::PrintSortedValue(std::ostream& os, const int value) const
{
    for (auto ip = m_pool.cbegin(); ip != m_pool.cend(); ++ip)
    {
        if (std::find(ip->cbegin(), ip->cend(), value) != ip->cend())
        {
            PrintSingle(os, *ip);
            os << '\n';
        }
    }   
}

void Filter::PrintSingle(std::ostream& os, const IpAddr& ip) const
{
    for (auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part)
    {
        if (ip_part != ip.cbegin())
        {
            os << ".";
        }
        os << +(*ip_part);
    }
}

StringsVector split(const std::string& str, const char d)
{
    StringsVector r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.emplace_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.emplace_back(str.substr(start));

    return r;
}

} // namespace ip_filter
