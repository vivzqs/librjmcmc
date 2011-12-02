#ifndef CONSTANT_UNARY_ENERGY_HPP_
#define CONSTANT_UNARY_ENERGY_HPP_

#include "rjmcmc/energy.hpp"

template<typename Value = double>
class constant_energy : public rjmcmc::energy<Value>
{
public:
    template<typename T> result_type operator()(const T &) const { return m_energy; }
    template<typename T,typename U> result_type operator()(const T &, const U &) const { return m_energy; }
    constant_energy(Value energy) { m_energy = energy; }

private:
    Value m_energy;
};

#endif /*CONSTANT_UNARY_ENERGY_HPP_*/