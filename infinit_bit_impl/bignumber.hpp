#ifndef __BIG_NUMBER_HPP__
#define __BIG_NUMBER_HPP__
#include "infinit_bit.hpp"
namespace DIY
{
class BigNumber
{
  public:
    BigNumber(long long init);

    BigNumber &add(const BigNumber &r);
    BigNumber &dec(const BigNumber &r);
    BigNumber &multi(const BigNumber &r);
    BigNumber &div(const BigNumber &r);
    BigNumber &mod(const BigNumber &r);

  private:
    InfinitBit bits_;
    bool positive_;
};
} // namespace DIY
#endif