#include "bignumber.hpp"

namespace DIY
{
BigNumber::BigNumber(long long init)
{}
BigNumber &BigNumber::add(const BigNumber &r)
{
    auto agent = bits_.first_bit();
    auto agent2 = r.bits_.first_bit();

    while (agent2 != r.bits_.last_bit())
    {
        if (agent.get() && agent2.get())
        {
            auto carry_agent = agent;
            while (carry_agent.get())
            {
                carry_agent.clear();
                bits_.advance(carry_agent);
            }
            carry_agent.set();
        }
        else if (agent.get() || agent2.get())
        {
            agent.set();
        }
        bits_.advance(agent);
        r.bits_.advance(agent2);
    }
    return *this;
}
BigNumber &BigNumber::dec(const BigNumber &r)
{
    return *this;
}
BigNumber &BigNumber::multi(const BigNumber &r)
{
    return *this;
}
BigNumber &BigNumber::div(const BigNumber &r)
{
    return *this;
}
BigNumber &BigNumber::mod(const BigNumber &r)
{
    return *this;
}
} // namespace DIY