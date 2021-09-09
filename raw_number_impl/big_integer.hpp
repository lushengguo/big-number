#ifndef __BIG_INTEGER_HPP__
#define __BIG_INTEGER_HPP__
#include <list>
#include <string>
namespace DIY
{
class BigInteger
{
  public:
    typedef long long IntegerType;
    enum CompareResult
    {
        kEqual,
        kBigger,
        kSmaller
    };
    BigInteger(IntegerType init);
    BigInteger(const BigInteger &r);

    std::string to_string() const;

    BigInteger &add(const BigInteger &r);
    BigInteger &dec(const BigInteger &r);
    BigInteger &multi(const BigInteger &r);
    BigInteger &div(const BigInteger &r);
    BigInteger &mod(const BigInteger &r);

    CompareResult compare(const BigInteger &r, bool ignore_sign) const;

    void debug_view() const;

  private:
    void swap(BigInteger &r);
    void clean_mess();
    void storge_emplace_back(IntegerType val)
    {
        storge_.emplace_back(val);
        storge_len_++;
    }

    bool positive_;
    std::list<IntegerType> storge_;
    size_t storge_len_;
    static constexpr size_t node_max_ = 10000;
    static constexpr size_t node_string_len_ = 5;
};
} // namespace DIY

#endif