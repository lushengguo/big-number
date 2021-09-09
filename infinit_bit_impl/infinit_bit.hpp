#ifndef __INFINIT_BIT_HPP__
#define __INFINIT_BIT_HPP__
#include <list>

namespace DIY
{
class BitAgent;

class InfinitBit
{
  public:
    typedef long long SizeType;
    typedef std::list<SizeType> ContainerType;
    typedef std::list<SizeType>::iterator IteratorType;

    InfinitBit()
      : container_size_(0), last_iter_(container_.end())
    {}
    ~InfinitBit() = default;

    BitAgent first_bit() const;
    BitAgent last_bit() const;
    void advance(BitAgent &agent, size_t n = 1) const;
    void previous(BitAgent &agent, size_t n = 1);

    void print() const;

  private:
    mutable ContainerType container_;
    mutable size_t container_size_;
    mutable IteratorType last_iter_;
};

class BitAgent
{
  public:
    BitAgent(InfinitBit::IteratorType iter, size_t bit)
      : iter_(iter), bit_(bit)
    {}

    BitAgent &operator=(const BitAgent &r)
    {
        iter_ = r.iter_;
        bit_ = r.bit_;
        return *this;
    }

    bool get()
    {
        return *iter_ & (1 << bit_);
    }

    void clear()
    {
        *iter_ &= ~(long long)(1 << bit_);
    }

    void set()
    {
        *iter_ |= 1 << bit_;
    }

    bool operator==(const BitAgent &r)
    {
        return iter_ == r.iter_ && bit_ == r.bit_;
    }

    bool operator!=(const BitAgent &r)
    {
        return !(*this == r);
    }

  private:
    friend InfinitBit;
    InfinitBit::IteratorType iter_;
    size_t bit_;
};
} // namespace DIY

#endif