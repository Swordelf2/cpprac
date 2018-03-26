#include <iostream>
#include <ctime>

#include <string>
#include <algorithm>

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
            data[i] = stoul(s.substr(cur_ind - CHARS_IN_NUM, CHARS_IN_NUM), NULL, HEX_BASE);
            cur_ind -= CHARS_IN_NUM;
        } else {
            data[i] = stoul(s.substr(start, cur_ind - start), NULL, HEX_BASE);
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

namespace std
{

template <>
struct hash<Account>
{
    size_t operator()(Account acc) const
    {
        return acc.cdata()[0] ^ acc.cdata()[1] ^
                acc.cdata()[2] ^ acc.cdata()[3];
    }
};

}
using namespace std;

int main()
{
    srand(time(NULL));
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) {
        uint32_t d[4];
        for (int j = 0; j < 4; ++j) {
            d[j] = rand();
        }
        cout << ((Account) d).to_string() << endl;
    }
}
