#include <iostream>
#include <string>
#include <ctype.h>

constexpr int HEX_BASE = 16;
constexpr int CHARS_IN_NUM = 8; // hexademical digits in one 32-bit number

class Account
{
public:
    Account();
    Account(const Account &other);
    Account(const std::string &s);
    Account(const uint32_t *_data);

    std::string to_string() const;
    const uint32_t *cdata() const;

    operator bool() const;
    friend int cmp(const Account &acc1, const Account &acc2);
    friend bool operator<(const Account &acc1, const Account &acc2);
    friend bool operator>(const Account &acc1, const Account &acc2);
    friend bool operator<=(const Account &acc1, const Account &acc2);
    friend bool operator>=(const Account &acc1, const Account &acc2);
    friend bool operator==(const Account &acc1, const Account &acc2);
    friend bool operator!=(const Account &acc1, const Account &acc2);

    static constexpr size_t DATA_SIZE = 4;

private:
    static inline uint32_t hextou(const char *s, size_t n);
    static inline uint32_t chartou(char c);
    uint32_t data[DATA_SIZE];
};

Account::Account()
{
    for (size_t i = 0; i < DATA_SIZE; ++i) {
        data[i] = 0;
    }
}

Account::Account(const Account &other)
{
    std::copy(other.data, other.data + DATA_SIZE, data);
}

Account::Account(const std::string &s)
{
    size_t len = s.length();
    size_t start = 2; // 0x...

    bool finish_flag = false;
    if (start >= len) {
        finish_flag = true;
    }
    size_t i = 0;
    size_t cur_ind = len; // the right-hand pointer to what is being read
    for (; i < DATA_SIZE && !finish_flag; ++i) {
        if (cur_ind - start > CHARS_IN_NUM) {
            data[i] = hextou(s.c_str() + cur_ind - CHARS_IN_NUM, CHARS_IN_NUM);
            cur_ind -= CHARS_IN_NUM;
        } else {
            data[i] = hextou(s.c_str() + start, cur_ind - start);
            finish_flag = true;
        }
    }

    // fill the rest with 0's
    for (size_t j = i; j < DATA_SIZE; ++j) {
        data[j] = 0;
    }
}

Account::Account(const uint32_t *_data)
{
    for (size_t i = 0; i < DATA_SIZE; ++i) {
        data[i] = _data[i];
    }
}

std::string Account::to_string() const
{
    if (data[0] == 0 && data[1] == 0 && data[2] == 0 && data[3] == 0) {
        return std::string("0");
    }
    char result[2 + DATA_SIZE * CHARS_IN_NUM + 1] = "0x";
    for (size_t i = 0; i < DATA_SIZE; ++i) {
        size_t j = DATA_SIZE - 1 - i;
        size_t wr_pos = 2 + i * CHARS_IN_NUM;
        snprintf(result + wr_pos, sizeof(result) - wr_pos, "%08x", data[j]);
    }
    result[2 + DATA_SIZE * CHARS_IN_NUM] = '\0';
    return std::string(result);
}

const uint32_t *Account::cdata() const
{
    return data;
}

Account::operator bool() const
{
    uint32_t result = 0x0u;
    for (size_t i = 0; i < DATA_SIZE; ++i) {
        result |= data[i];
    }
    return result;
}

int cmp(const Account &acc1, const Account &acc2)
{
    for (size_t i = 0; i < Account::DATA_SIZE; ++i) {
        size_t j = Account::DATA_SIZE - 1 - i;
        if (acc1.data[j] > acc2.data[j]) {
            return 1;
        } else if (acc1.data[j] < acc2.data[j]) {
            return -1;
        }
    }
    return 0;
}

bool operator<(const Account &acc1, const Account &acc2)
{
    return cmp(acc1, acc2) < 0;
}

bool operator>(const Account &acc1, const Account &acc2)
{
    return cmp(acc1, acc2) > 0;
}

bool operator<=(const Account &acc1, const Account &acc2)
{
    return cmp(acc1, acc2) <= 0;
}

bool operator>=(const Account &acc1, const Account &acc2)
{
    return cmp(acc1, acc2) >= 0;
}

bool operator==(const Account &acc1, const Account &acc2)
{
    return cmp(acc1, acc2) == 0;
}

bool operator!=(const Account &acc1, const Account &acc2)
{
    return cmp(acc1, acc2) != 0;
}

// 1 <= n <= 8
uint32_t Account::hextou(const char *s, size_t n)
{
    uint32_t result = 0x0;
    int i = n -2;
    int cnt = 0;
    for (; i >= 0; i -= 2, ++cnt) {
        uint32_t byte = (chartou(s[i]) << 4) + chartou(s[i + 1]);
        result |= (byte << cnt * 8);
    }
    if (i == -1) {
        result |= (chartou(s[0]) << cnt * 8);
    }
    return result;
}

// from hex char
uint32_t Account::chartou(char c)
{
    if (isdigit(c)) {
        return c - '0';
    } else {
        if (islower(c)) {
            return c - 'a' + 10;
        } else {
            return c - 'A' + 10;
        }
    }
}


namespace std
{

// WRONG HASH
template <>
struct hash<Account>
{
    size_t operator()(Account acc) const
    {
        size_t result = 0;
        for (size_t i = 0; i < Account::DATA_SIZE; ++i) {
            size_t ihash = (hash<uint32_t> {})(acc.cdata()[i]);
            result ^= (ihash << i);
        }
        return result;
    }
};

}
