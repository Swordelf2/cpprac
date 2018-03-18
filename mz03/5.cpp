#include <iostream>
#include <string>
#include <algorithm>

constexpr size_t DATA_SIZE = 4;
constexpr int HEX_BASE = 16;
constexpr int CHARS_IN_NUM = 8; // hexademical digits in one 32-bit number

class Account
{
    private:
    uint32_t data[DATA_SIZE];
    public:
    Account();
    Account(const Account &other);
    Account(const std::string &s);
    Account(const uint32_t *_data);

    std::string to_string() const;
    const uint32_t *cdata() const;
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
    size_t cur_ind = len;
    size_t start = 0;
    // find 'x' or 'X'
    {
        size_t x_pos;
        if ((x_pos = s.find('x')) != std::string::npos) {
            start = x_pos + 1;
        } else if ((x_pos = s.find('X')) != std::string::npos) {
            start = x_pos + 1;
        }
    }


    size_t i = 0;
    bool finish_flag = false;
    if (start == len) {
        finish_flag = true;
    }
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
    char result[2 + DATA_SIZE * CHARS_IN_NUM + 1] = "0x";
    ssize_t cnt = 2;
    int i = DATA_SIZE - 1;
    for (; i >= 0 && data[i] == 0; --i) {}
    if (i >= 0) {
        cnt += snprintf(result + cnt, sizeof(result) - cnt, "%x", data[i]);
    } else {
        result[2] = '0';
        ++cnt;
    }
    for (int j = i - 1; j >= 0; --j) {
        cnt += snprintf(result + cnt, sizeof(result) - cnt, "%08x", data[j]);
    }
    result[cnt] = '\0';
    return std::string(result);
}

const uint32_t *Account::cdata() const
{
    return data;
}

int main()
{
    std::string s;
    std::cin >> s;
    Account acc(s);
    std::cout << acc.to_string() << std::endl;
}
