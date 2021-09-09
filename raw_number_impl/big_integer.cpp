#include "big_integer.hpp"
#include <iostream>
#include <iterator>
#include <vector>
namespace DIY
{
BigInteger::BigInteger(IntegerType init) : positive_(true), storge_(1, init), storge_len_(1)
{
    clean_mess();
}

BigInteger::BigInteger(const BigInteger &r)
{
    positive_ = r.positive_;
    storge_ = r.storge_;
    storge_len_ = r.storge_len_;
}

std::string BigInteger::to_string() const
{
    std::string str;
    str.reserve(storge_len_ * node_string_len_ + 1);

    if (!positive_)
        str.append(1, '-');

    for (auto iter = storge_.rbegin(); iter != storge_.rend(); iter++)
    {
        //首个node前面不用补0
        if (str.empty() || (str.size() == 1 && str.front() == '-'))
        {
            str.append(std::to_string(*iter));
            continue;
        }

        size_t len = node_max_ / 10;
        while (len)
        {
            str.append(1, (*iter / len) % 10 + '0');
            len /= 10;
        }
    }

    return str;
}

BigInteger &BigInteger::add(const BigInteger &r)
{
    if (&r == this)
        return multi(2);

    if (positive_ != r.positive_)
        return dec(BigInteger(r).multi(-1));

    auto iter = storge_.begin();
    for (auto val : r.storge_)
    {
        *iter += val;
        if (std::next(iter) == storge_.end())
            storge_emplace_back(0);
        iter++;
    }
    clean_mess();
    return *this;
}

BigInteger &BigInteger::dec(const BigInteger &r)
{
    if (&r == this)
        *this = BigInteger(0);

    if (r.positive_ != positive_)
        return add(BigInteger(r).multi(-1));

    auto iter1 = storge_.begin();
    auto iter2 = r.storge_.cbegin();
    while (iter2 != r.storge_.cend())
    {
        *iter1 -= *iter2;
        if (std::next(iter1) == storge_.end())
            storge_emplace_back(0);
        iter1++;
        iter2++;
    }
    clean_mess();

    return *this;
}

BigInteger &BigInteger::multi(const BigInteger &r)
{
    BigInteger res(0);
    res.positive_ = (r.positive_ == positive_);

    auto first_assign_iter = res.storge_.begin();
    for (auto val : r.storge_)
    {
        auto assign_iter = first_assign_iter;
        for (auto val2 : storge_)
        {
            *assign_iter += val2 * val;
            if (std::next(assign_iter) == res.storge_.end())
                res.storge_emplace_back(0);
            assign_iter++;
        }
        res.clean_mess();
        if (first_assign_iter == res.storge_.end())
            res.storge_emplace_back(0);
        first_assign_iter++;
    }
    res.clean_mess();
    swap(res);
    return *this;
}

BigInteger &BigInteger::div(const BigInteger &r)
{
    positive_ = (positive_ == r.positive_);

    if (r.storge_.back() == 0)
    {
        std::cerr << "divide zero is forbidden" << std::endl;
        throw -1;
    }

    // ignore sign
    switch (compare(r, true))
    {
    case kBigger:
    {
        break;
    }
    case kEqual:
    {
        BigInteger tmp(1);
        swap(tmp);
        break;
    }
    case kSmaller:
    {
        BigInteger tmp(0);
        swap(tmp);
        break;
    }
    }

    return *this;
}

BigInteger &BigInteger::mod(const BigInteger &r)
{
    BigInteger tmp(*this);
    dec(tmp.div(r).multi(r));
    return *this;
}

void BigInteger::clean_mess()
{
    while (storge_len_ != 1 && storge_.back() == 0)
        storge_.pop_back();

    size_t carry = 0;
    bool rent = false;
    bool revert = (storge_.back() < 0);
    if (revert)
        positive_ = !positive_;

    for (auto iter = storge_.begin(); iter != storge_.end(); iter++)
    {
        auto val = *iter;
        if (revert)
            val *= -1;

        if (rent)
            val -= 1;

        val += carry;
        if (val >= 0)
        {
            rent = false;
            carry = val / node_max_;
            val %= node_max_;
        }
        else
        {
            rent = true;
            carry = 0;
            val += node_max_;
        }

        *iter = val;
        if (std::next(iter) == storge_.end() && carry > 0)
            storge_emplace_back(0);
    }
}

void BigInteger::debug_view() const
{
    if (!positive_)
        std::cout << "-";
    for (auto iter = storge_.rbegin(); iter != storge_.rend(); iter++)
        std::cout << *iter << " ";
    std::cout << std::endl;
}

void BigInteger::swap(BigInteger &r)
{
    storge_ = std::move(r.storge_);
    storge_len_ = r.storge_len_;
    positive_ = r.positive_;
}

BigInteger::CompareResult BigInteger::compare(const BigInteger &r, bool ignore_sign) const
{
    CompareResult res = kEqual;

    if (storge_len_ > r.storge_len_)
    {
        res = kBigger;
    }
    else if (storge_len_ < r.storge_len_)
    {
        res = kSmaller;
    }
    else // has same len but not qualified same value
    {
        auto iter1 = storge_.crbegin();
        auto iter2 = r.storge_.crbegin();
        while (iter1 != storge_.crend())
        {
            if (*iter1 > *iter2)
            {
                res = kBigger;
                break;
            }
            if (*iter1 < *iter2)
            {
                res = kSmaller;
                break;
            }
            iter1++;
            iter2++;
        }
    }

    if (!ignore_sign)
        return res;

    if (positive_ != r.positive_)
    {
        if (positive_)
            return kBigger;
        else
            return kSmaller;
    }
    else // same sign
    {
        if (!positive_)
        {
            if (res == kBigger)
                res = kSmaller;
            else if (res == kSmaller)
                res = kBigger;
        }
        return res;
    }
} // namespace DIY
} // namespace DIY