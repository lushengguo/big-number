#include "infinit_bit.hpp"
#include <bitset>
#include <iostream>
#include <iterator>
namespace DIY
{
BitAgent InfinitBit::first_bit() const
{
    if (container_size_ == 0)
    {
        container_.emplace_back(0);
        container_size_++;
        last_iter_ = container_.begin();
    }
    return BitAgent(container_.begin(), 0);
}

BitAgent InfinitBit::last_bit() const
{
    if (last_iter_ != container_.end())
        return BitAgent(
          last_iter_, sizeof(SizeType) * 8 - 1);

    auto agent = first_bit();
    agent.bit_ = sizeof(SizeType) * 8 - 1;
    return agent;
}

void InfinitBit::advance(BitAgent &agent, size_t n) const
{
    size_t bit = agent.bit_;
    bit += n;
    for (int i = 0; i < bit / sizeof(SizeType); i++)
    {
        // auto grow
        if (std::next(agent.iter_) == container_.end())
        {
            container_.emplace_back(0);
            container_size_++;
            last_iter_++;
        }

        agent.iter_++;
    }

    agent.bit_ = (bit % sizeof(SizeType));
}

void InfinitBit::previous(BitAgent &agent, size_t n)
{
    while (n > agent.bit_)
    {
        if (agent.iter_ == container_.cbegin())
        {
            agent = first_bit();
            return;
        }
        agent.iter_--;
        n -= agent.bit_ + 1;
        agent.bit_ = 7;
    }
    agent.bit_ -= n;
}

void InfinitBit::print() const
{
    std::cout << "length-> "
              << container_size_ * sizeof(SizeType)
              << std::endl;
    std::cout << "HighBit-> ";
    for (auto iter = container_.crbegin();
         iter != container_.crend();
         iter++)
    {
        std::bitset<sizeof(SizeType)> binary(*iter);
        std::cout << binary;
    }
    std::cout << " <-LowBit" << std::endl;
}
} // namespace DIY
