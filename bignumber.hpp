#ifndef __BIG_NUMBER_HPP__
#define __BIG_NUMBER_HPP__

namespace DIY
{

/* Container should implement as
// class Container
// {
//   public:
//     DecimalBitIterator first_bit();
//     DecimalBitIterator last_bit();
//     DecimalBitIterator advance(DecimalBitIterator &);
//     // val between 0-9
//     void set(DecimalBitIterator iter,int val);
// };
 */
template <typename DecimalBitIterator, typename Container>
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
    DecimalBitIterator low_begin_;
    bool positive_;
};
} // namespace DIY
#endif
