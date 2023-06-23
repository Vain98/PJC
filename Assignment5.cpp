#include <iostream>

namespace datatype
{
    template <typename FType, typename SType>
    class pair
    {
    private:
        FType ft;
        SType st;
    public:
        pair() : ft(FType()), st(SType()) {}

        pair(const FType& ft, const SType& st) : ft(ft), st(st) {}

        template <typename UFType, typename USType>
        pair(const pair<UFType, USType>& rhs) : ft(rhs.first()), st(rhs.second()) {}

        template <typename UFType, typename USType>
        pair& operator=(const pair<UFType, USType>& rhs)
        {
            ft = rhs.first();
            st = rhs.second();

            return *this;
        }

        const FType& first() const { return ft; }
        const SType& second() const { return st; }
    public:
        friend std::ostream& operator<<(std::ostream& os, const pair& rhs)
        {
            os << "[" << rhs.ft << ", " << rhs.st << "]";
            return os;
        }
    };
}

template <typename PAIR>
bool operator<(const PAIR& lhs, const PAIR& rhs)
{
    return lhs.first() < rhs.first();
}

template <typename PAIR>
bool operator<=(const PAIR& lhs, const PAIR& rhs)
{
    return lhs < rhs ||
           (lhs.first() == rhs.first() &&
            lhs.second() == rhs.second());
}

template <typename PAIR>
bool operator>(const PAIR& lhs, const PAIR& rhs)
{
    return !(lhs < rhs) ? (lhs.second() > rhs.second() ? true : false) : false;
}

template <typename PAIR>
bool operator>=(const PAIR& lhs, const PAIR& rhs)
{
    return lhs > rhs ||
           (lhs.first() == rhs.first() &&
            lhs.second() == rhs.second());
}

template <typename PAIR>
bool operator==(const PAIR& lhs, const PAIR& rhs)
{
    return lhs.first() == rhs.first() &&
           lhs.second() == rhs.second();
}

template <typename PAIR>
bool operator!=(const PAIR& lhs, const PAIR& rhs)
{
    return !(lhs == rhs);
}

template <typename PAIR>
void check(const PAIR& lhs, const PAIR& rhs)
{
    auto flags = std::cout.flags();

    std::cout << std::boolalpha;
    std::cout << "\nLHS = " << lhs << " RHS = " << rhs << std::endl;
    std::cout << "lhs < rhs: " << (lhs < rhs) << std::endl;
    std::cout << "lhs <= rhs: " << (lhs <= rhs) << std::endl;
    std::cout << "lhs > rhs: " << (lhs > rhs) << std::endl;
    std::cout << "lhs >= rhs: " << (lhs >= rhs) << std::endl;
    std::cout << "lhs == rhs: " << (lhs == rhs) << std::endl;
    std::cout << "lhs != rhs: " << (lhs != rhs) << std::endl;
    std::cout.flags(flags);
}

int main()
{
    check(datatype::pair<int, int>(3, 3), datatype::pair<int, int>(4, 2));
    check(datatype::pair<int, int>(3, 3), datatype::pair<int, int>(3, 2));
    check(datatype::pair<int, int>(4, 3), datatype::pair<int, int>(4, 3));

    datatype::pair<int, int> pia { 3, 4 };
    datatype::pair<int, int> pib { 4, 5 };
    datatype::pair<double, double> pd(pia);

    std::cout << pia << std::endl;
    std::cout << pd << std::endl;

    pd = pib;
    std::cout << pd << std::endl;

    return 0;
}