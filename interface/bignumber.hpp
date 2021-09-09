namespace DIY
{
class BigNumber
{
  public:
    virtual BigNumber &add(const BigNumber &r) = 0;
    virtual BigNumber &dec(const BigNumber &r) = 0;
    virtual BigNumber &multi(const BigNumber &r) = 0;
    virtual BigNumber &div(const BigNumber &r) = 0;
    virtual BigNumber &mod(const BigNumber &r) = 0;
};
} // namespace DIY