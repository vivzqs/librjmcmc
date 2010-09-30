#ifndef __COUNT_SAMPLER_HPP__
#define __COUNT_SAMPLER_HPP__

#include "rjmcmc/random.hpp"
#include <boost/random/poisson_distribution.hpp>
#include <boost/random/uniform_smallint.hpp>

namespace marked_point_process {

    // exp(-poisson) * (poisson^n) / n!
    class poisson_count_sampler {
    public:
        typedef boost::variate_generator<rjmcmc::generator&, boost::poisson_distribution<> > count_sampler;
        poisson_count_sampler(double poisson)
            : m_poisson(poisson)
            , m_die(rjmcmc::random(), boost::poisson_distribution<>(poisson)) {}

        // new/old
        // old/new : (m_poisson^dn) * n! / (n+dn)!
        template<typename Configuration, typename Modification>
        double pdf_ratio(const Configuration &c, const Modification &m) const
        {
            unsigned int n = c.size();
            int dn = m.birth_size()-m.death_size();
            double res = 1.;
            for(   ;dn>0;--dn) res *= m_poisson/(n+dn);
            for(++n;dn<0;++dn) res *= (n+dn)/m_poisson;
            return res;
        }
        inline unsigned int operator()() const { return m_die(); }

    private:
        double m_poisson;
        mutable count_sampler m_die;
    };

    // 1_(n\in[a,b])/(b-a+1)
    class uniform_count_sampler {
    public:
        typedef boost::variate_generator<rjmcmc::generator&, boost::uniform_smallint<> > count_sampler;
        uniform_count_sampler(unsigned int a, unsigned int b)
            : m_min(a), m_max(b)
            , m_die(rjmcmc::random(), boost::uniform_smallint<>(a,b)) {}

        uniform_count_sampler(unsigned int b)
            : m_min(0), m_max(b)
            , m_die(rjmcmc::random(), boost::uniform_smallint<>(0,b)) {}

        template<typename Configuration, typename Modification>
        double pdf_ratio(const Configuration &c, const Modification &m) const
        {
            unsigned int n0 = c.size();
            unsigned int n1 = (n0 + m.birth_size())-m.death_size();
            return (n0<m_min || n1<m_min || n0>m_max || n1>m_max)? 0. : 1.;
        }
        inline unsigned int operator()() const { return m_die(); }
    private:
        unsigned int m_min, m_max;
        mutable count_sampler m_die;
    };

}; // namespace marked_point_process

#endif // __COUNT_SAMPLER_HPP__
