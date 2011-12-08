#ifndef __COMPOSITE_VISITOR_HPP__
#define __COMPOSITE_VISITOR_HPP__

#include "rjmcmc/tuple.hpp"

namespace simulated_annealing {

    namespace internal {

        struct visitor_init
        {
            int m_dump, m_save;
            visitor_init(int dump, int save) : m_dump(dump), m_save(save) {}
            template<typename T> inline void operator()(T& t) { t .init(m_dump,m_save); }
            template<typename T> inline void operator()(T* t) { t->init(m_dump,m_save); }
        };

        template<typename Configuration, typename Sampler>
        struct visitor_begin
        {
            const Configuration& m_config;
            const Sampler& m_sample;
            double m_t;
            visitor_begin(const Configuration& config, const Sampler& sample, double t) : m_config(config), m_sample(sample), m_t(t) {}
            template<typename T> inline void operator()(T& t) { t .begin(m_config,m_sample,m_t); }
            template<typename T> inline void operator()(T* t) { t->begin(m_config,m_sample,m_t); }
        };
        template<typename Configuration, typename Sampler>
        struct visitor_visit
        {
            const Configuration& m_config;
            const Sampler& m_sample;
            double m_t;
            visitor_visit(const Configuration& config, const Sampler& sample, double t) : m_config(config), m_sample(sample), m_t(t) {}
            template<typename T> inline void operator()(T& t) { t .visit(m_config,m_sample,m_t); }
            template<typename T> inline void operator()(T* t) { t->visit(m_config,m_sample,m_t); }
        };
        template<typename Configuration, typename Sampler>
        struct visitor_end
        {
            const Configuration& m_config;
            const Sampler& m_sample;
            double m_t;
            visitor_end(const Configuration& config, const Sampler& sample, double t) : m_config(config), m_sample(sample), m_t(t) {}
            template<typename T> inline void operator()(T& t) { t .end(m_config,m_sample,m_t); }
            template<typename T> inline void operator()(T* t) { t->end(m_config,m_sample,m_t); }
        };

    } // namespace internal

    template<RJMCMC_TUPLE_TYPENAMES>
    class composite_visitor
    {
    public:
        typedef rjmcmc::tuple<RJMCMC_TUPLE_TYPES> Visitors;
        composite_visitor(RJMCMC_TUPLE_ARGS) : m_visitors(RJMCMC_TUPLE_PARAMS) {}

        void init(int dump, int save)
        {
            internal::visitor_init v(dump,save);
            rjmcmc::for_each(m_visitors,v);
        }

        template<typename Configuration, typename Sampler>
        void begin(const Configuration& config, const Sampler& sample, double t)
        {
            internal::visitor_begin<Configuration,Sampler> v(config,sample,t);
            rjmcmc::for_each(m_visitors,v);
        }

        template<typename Configuration, typename Sampler>
        void visit(const Configuration& config, const Sampler& sample, double t)
        {
            internal::visitor_visit<Configuration,Sampler> v(config,sample,t);
            rjmcmc::for_each(m_visitors,v);
        }

        template<typename Configuration, typename Sampler>
        void end(const Configuration& config, const Sampler& sample, double t)
        {
            internal::visitor_end<Configuration,Sampler> v(config,sample,t);
            rjmcmc::for_each(m_visitors,v);
        }
    private:
        Visitors m_visitors;
    };

/*
    template<RJMCMC_TUPLE_TYPENAMES>
    composite_visitor<RJMCMC_TUPLE_TYPES> make_visitor(RJMCMC_TUPLE_ARGS)
    {
        return composite_visitor(RJMCMC_TUPLE_PARAMS);
    }
*/
} // namespace simulated_annealing

#endif // __COMPOSITE_VISITOR_HPP__
