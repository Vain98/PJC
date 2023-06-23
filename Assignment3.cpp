#include <iostream>
#include <numeric>

class Frac
{
private:
    int numerator;
    int denominator;
public:
    Frac();
    Frac(int numerator);
    Frac(int numerator, int denominator);
    Frac(const Frac& frac);
    int getNumerator() const;
    int getDenominator() const;
    double getResult() const;
public:
    void operator=(const Frac& rhs);
    double operator+(const Frac& frac) const;
    double operator-(const Frac& frac) const;
    double operator*(const Frac& frac) const;
    double operator/(const Frac& frac) const;
    template<typename T> double operator+(const T& rhs) const;
    template<typename T> double operator-(const T& rhs) const;
    template<typename T> double operator*(const T& rhs) const;
    template<typename T> double operator/(const T& rhs) const;
    template<typename T> friend double operator+(const T& lhs, const Frac& rhs);
    template<typename T> friend double operator*(const T& lhs, const Frac& rhs);
    template<typename T> friend double operator*(const T& lhs, const Frac& rhs);
    template<typename T> friend double operator/(const T& lhs, const Frac& rhs);
    friend std::ostream& operator<<(std::ostream& os, const Frac& frac);
};

Frac::Frac()
    : numerator(0), denominator(1)
{
}

Frac::Frac(int numerator)
    : numerator(numerator), denominator(1)
{
}

Frac::Frac(int numerator, int denominator)
{
    if (denominator == 0)
        throw std::string("In Frac::Frac(int, int), denominator is 0 exception!");

    else if (denominator < 0)
    {
        this->numerator = -numerator;
        this->denominator = -denominator;
    }

    else if (denominator > 0)
    {
        this->numerator = numerator;
        this->denominator = denominator;
    }
}

Frac::Frac(const Frac& frac)
    : numerator(frac.numerator), denominator(frac.denominator)
{
}

int Frac::getNumerator() const
{
    return numerator;
}

int Frac::getDenominator() const
{
    return denominator;
}

double Frac::getResult() const
{
    return static_cast<double>(numerator) / denominator;
}

void Frac::operator=(const Frac& rhs)
{
    numerator = rhs.numerator;
    denominator = rhs.denominator;
}

double Frac::operator+(const Frac& frac) const
{
    return getResult() + frac.getResult();
}

double Frac::operator-(const Frac& frac) const
{
    return getResult() - frac.getResult();
}

double Frac::operator*(const Frac& frac) const
{
    return getResult() * frac.getResult();
}

double Frac::operator/(const Frac& frac) const
{
    return getResult() / frac.getResult();
}

template<typename T>
double Frac::operator+(const T& rhs) const
{
    return getResult() + rhs;
}

template<typename T>
double Frac::operator-(const T& rhs) const
{
    return getResult() - rhs;
}

template<typename T>
double Frac::operator*(const T& rhs) const
{
    return getResult() * rhs;
}

template<typename T>
double Frac::operator/(const T& rhs) const
{
    return getResult() / rhs;
}

template<typename T>
double operator+(const T& lhs, const Frac& rhs)
{
    return lhs + rhs.getResult();
}

template<typename T>
double operator-(const T& lhs, const Frac& rhs)
{
    return lhs - rhs.getResult();
}

template<typename T>
double operator*(const T& lhs, const Frac& rhs)
{
    return lhs * rhs.getResult();
}

template<typename T>
double operator/(const T& lhs, const Frac& rhs)
{
    return lhs / rhs.getResult();
}

std::ostream& operator<<(std::ostream& os, const Frac& frac)
{
    os << frac.getResult();
    return os;
}

int main()
{
    Frac a(2), b(4, 10), c(24, -15), x(1, -3), y(2, 6);

    std::cout << -2 * ((a + b) * 5 - 4) / c << " "
        << (7 + x + y * 1114 / 111) << std::endl;

    return 0;
}