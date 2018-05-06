#include <string>
#include <sstream>
#include <array>
#include <limits>
#include <cctype>
#include <stdexcept>
#include <type_traits>

/* Forward declarations */

template <class SignedT>
class Range;

namespace RangeImpl {

// Some template magic incoming!
template <class SignedT>
Range<SignedT> AddRanges(const Range<SignedT> &r1, const Range<SignedT> &r2);
template <class SignedT>
Range<SignedT> SubRanges(const Range<SignedT> &r1, const Range<SignedT> &r2);
template <class SignedT>
Range<SignedT> MulRanges(const Range<SignedT> &r1, const Range<SignedT> &r2);

}

/* Class definition */

template <class SignedT>
class Range
{
    SignedT low = SignedT();
    SignedT high = SignedT();

public:
    Range();
    Range(SignedT _low);
    Range(SignedT _low, SignedT _high);
    explicit Range(std::string s);

    // template magic right here
    friend Range operator+(const Range &r1, const Range &r2)
    {
        return RangeImpl::AddRanges(r1, r2);
    }
    friend Range operator-(const Range &r1, const Range &r2)
    {
        return RangeImpl::SubRanges(r1, r2);
    }
    friend Range operator*(const Range &r1, const Range &r2)
    {
        return RangeImpl::MulRanges(r1, r2);
    }

    // continues here
    friend Range<SignedT> RangeImpl::AddRanges<>(const Range<SignedT> &r1, const Range<SignedT> &r2);
    friend Range<SignedT> RangeImpl::SubRanges<>(const Range<SignedT> &r1, const Range<SignedT> &r2);
    friend Range<SignedT> RangeImpl::MulRanges<>(const Range<SignedT> &r1, const Range<SignedT> &r2);
    Range<SignedT> operator-() const;

    std::string to_string() const;

    SignedT get_low() const;
    SignedT get_high() const;
};

/* Some auxillary functions definitions */
namespace RangeImpl
{

template <class SignedT>
constexpr void TypeCheck()
{
    static_assert((std::is_signed<SignedT>::value &&
            std::is_integral<SignedT>::value) ||
            std::is_class<SignedT>::value ||
            std::is_union<SignedT>::value,
            "The type is neither a signed built-in type, nor a user-defined type");
}

template <class BuiltinSignedT>
BuiltinSignedT Convert(long long num)
{
    if (num < std::numeric_limits<BuiltinSignedT>::min() ||
            num > std::numeric_limits<BuiltinSignedT>::max()) {
        throw std::out_of_range("Conversion failed");
    }
    return num;
}

template <class BuiltinSignedT>
BuiltinSignedT ReadFromString(std::string s)
{
    std::size_t pos;
    BuiltinSignedT result;
    try {
        long long val = stoll(s, &pos, 0);
        if (pos != s.length()) {
            throw std::invalid_argument("Conversion failed");
        }
        result = Convert<BuiltinSignedT>(val);
    } catch (std::out_of_range&) {
        throw std::range_error("Read failed");
    }
    return result;
}

/* *******
    The 3 following functions perform arithmetic operations depending on
    whether the given type is user-defined or built-in
    (in which case it also tracks overflows)
*/
    
template <class SignedT>
SignedT Add(SignedT a, SignedT b)
{
    if constexpr (std::is_signed<SignedT>::value) {
        std::overflow_error o_err("Addition overflow");
        long long add_res;
        // We perform an operation on long long values
        // and then convert them into SignedT type
        // the overflow happens if either the operation
        // on long long would overflow, or if the conversion does
        if (__builtin_saddll_overflow(a, b, &add_res)) {
            throw o_err;
        }
        SignedT res;
        try {
            res = Convert<SignedT>(add_res);
        } catch (std::out_of_range&) {
            throw o_err;
        }
        return res;
    } else {
        return a + b;
    }
}

template <class SignedT>
SignedT Sub(SignedT a, SignedT b)
{
    if constexpr (std::is_signed<SignedT>::value) {
        std::overflow_error o_err("Substraction overflow");
        long long sub_res;
        if (__builtin_ssubll_overflow(a, b, &sub_res)) {
            throw o_err;
        }
        SignedT res;
        try {
            res = Convert<SignedT>(sub_res);
        } catch (std::out_of_range&) {
            throw o_err;
        }
        return res;
    } else {
        return a - b;
    }
}

template <class SignedT>
SignedT Mul(SignedT a, SignedT b)
{
    if constexpr (std::is_signed<SignedT>::value) {
        std::overflow_error o_err("Multiplication overflow");
        long long mul_res;
        if (__builtin_smulll_overflow(a, b, &mul_res)) {
            throw o_err;
        }
        SignedT res;
        try {
            res = Convert<SignedT>(mul_res);
        } catch (std::out_of_range&) {
            throw o_err;
        }
        return res;
    } else {
        return a * b;
    }
}

// Find min and max values in an array
template <class SignedT, size_t n>
std::pair<SignedT, SignedT> MinMax(std::array<SignedT, n> arr)
{
    SignedT min = arr[0], max = arr[0];
    for (size_t i = 1; i < n; ++i) {
        if (arr[i] < min) {
            min = arr[i];
        } else if (arr[i] > max) {
            max = arr[i];
        }
    }
    return std::pair(min, max);
}

}

/* Range class function definitions */

/* Constructors */
template <class SignedT>
Range<SignedT>::Range()
{
    RangeImpl::TypeCheck<SignedT>();
}

template <class SignedT>
Range<SignedT>::Range(SignedT _low) : low(_low)
{
    RangeImpl::TypeCheck<SignedT>();
    if (_low > SignedT()) {
        throw std::invalid_argument("Invalid arguments in Range::Range()");
    }
}

template <class SignedT>
Range<SignedT>::Range(SignedT _low, SignedT _high) : low(_low), high(_high)
{
    RangeImpl::TypeCheck<SignedT>();
    if (_low > _high) {
        throw std::invalid_argument("Invalid arguments in Range::Range()");
    }
}

template <class SignedT>
Range<SignedT>::Range(std::string s)
{
    RangeImpl::TypeCheck<SignedT>();
    std::string low_str, high_str;
    std::invalid_argument inv_fmt("Invalid format");
    if (s.empty() || s[0] != '(' || s[s.length() - 1] != ')') {
        throw inv_fmt;
    }
    size_t comma_pos = s.find(',');
    if (comma_pos == s.npos) {
        throw inv_fmt;
    }

    low_str = s.substr(1, comma_pos - 1);
    high_str = s.substr(comma_pos + 1, (s.length() - 1) - (comma_pos + 1));
    if constexpr (std::is_signed<SignedT>::value) {
        low = RangeImpl::ReadFromString<SignedT>(low_str);
        high = RangeImpl::ReadFromString<SignedT>(high_str);
    } else {
        low = SignedT(low_str);
        high = SignedT(high_str);
    }
    if (low > high) {
        throw std::invalid_argument("Invalid arguments in Range::Range()");
    }
}
    
/* operators */
namespace RangeImpl
{

template <class SignedT>
Range<SignedT> AddRanges(const Range<SignedT> &r1, const Range<SignedT> &r2)
{
    return Range<SignedT>(RangeImpl::Add(r1.low, r2.low),
            RangeImpl::Add(r1.high, r2.high));
}

template <class SignedT>
Range<SignedT> SubRanges(const Range<SignedT> &r1, const Range<SignedT> &r2)
{
    return Range<SignedT>(RangeImpl::Sub(r1.low, r2.high),
            RangeImpl::Sub(r1.high, r2.low));
}

template <class SignedT>
Range<SignedT> MulRanges(const Range<SignedT> &r1, const Range<SignedT> &r2)
{
    std::array<SignedT, 4> arr = {Mul(r1.low, r2.low),
            RangeImpl::Mul(r1.low, r2.high),
            RangeImpl::Mul(r1.high, r2.low),
            RangeImpl::Mul(r1.high, r2.high)};
    auto min_max = RangeImpl::MinMax(arr);
    return Range(min_max.first, min_max.second);
}

}

template <class SignedT>
Range<SignedT> Range<SignedT>::operator-() const
{
    return Range<SignedT>() - *this;
}

/* other methods */

template <class SignedT>
std::string Range<SignedT>::to_string() const
{
    std::stringstream ss;   
    if constexpr (std::is_same<SignedT, signed char>::value ||
            std::is_same<SignedT, char>::value) {
        // For character types
        ss << '(' << static_cast<int>(low) << ',' << static_cast<int>(high) << ')';
    } else {
        ss << '(' << low << ',' << high << ')';
    }
    return ss.str();
}

template <class SignedT>
SignedT Range<SignedT>::get_low() const
{
    return low;
}

template <class SignedT>
SignedT Range<SignedT>::get_high() const
{
    return high;
}
