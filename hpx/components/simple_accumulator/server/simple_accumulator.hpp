//  Copyright (c) 2007-2008 Hartmut Kaiser
// 
//  Distributed under the Boost Software License, Version 1.0. (See accompanying 
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(HPX_COMPONENTS_SERVER_SIMPLE_ACCUMULATOR_JUL_18_2008_1154AM)
#define HPX_COMPONENTS_SERVER_SIMPLE_ACCUMULATOR_JUL_18_2008_1154AM

#include <iostream>

#include <hpx/hpx_fwd.hpp>
#include <hpx/runtime/applier/applier.hpp>
#include <hpx/runtime/threads/thread.hpp>
#include <hpx/runtime/actions/component_action.hpp>
#include <hpx/runtime/components/component_type.hpp>
#include <hpx/runtime/components/server/simple_component_base.hpp>

namespace hpx { namespace components { namespace server 
{
    ///////////////////////////////////////////////////////////////////////////
    /// \class simple_accumulator simple_accumulator.hpp hpx/components/simple_accumulator.hpp
    ///
    /// The simple_accumulatorclass is a small example components demonstrating 
    /// the main principles of writing your own components. It exposes 4 
    /// different actions: init, add, query, and print, showing how to used and 
    /// implement functionality in a way conformant with the HPX runtime system. 
    /// The simple_accumulator is a very simple example of an HPX component. 
    ///
    /// Note that the implementation of the simple_accumulator does not require 
    /// special data members or virtual functions. All specifics are embedded 
    /// in the simple_component_base class the simple_accumulator is derived 
    /// from.
    ///
    class simple_accumulator 
      : public simple_component_base<simple_accumulator>
    {
    public:
        // parcel action code: the action to be performed on the destination 
        // object (the accumulator)
        enum actions
        {
            accumulator_init = 0,
            accumulator_add = 1,
            accumulator_query_value = 2,
            accumulator_print = 3
        };

        // constructor: initialize accumulator value
        simple_accumulator(threads::thread_self& self, applier::applier& appl)
          : simple_component_base<simple_accumulator>(self, appl),
            arg_(0)
        {}

        ///////////////////////////////////////////////////////////////////////
        // exposed functionality of this component

        /// Initialize the accumulator
        threads::thread_state 
        init (threads::thread_self&, applier::applier& appl) 
        {
            arg_ = 0;
            return threads::terminated;
        }

        /// Add the given number to the accumulator
        threads::thread_state 
        add (threads::thread_self&, applier::applier& appl, double arg) 
        {
            arg_ += arg;
            return threads::terminated;
        }

        /// Return the current value to the caller
        threads::thread_state 
        query (threads::thread_self&, applier::applier& appl,
            double* result) 
        {
            // this will be zero if the action got invoked without continuations
            if (result)
                *result = arg_;
            return threads::terminated;
        }

        /// Print the current value of the accumulator
        threads::thread_state 
        print (threads::thread_self&, applier::applier& appl) 
        {
            std::cout << arg_ << std::flush << std::endl;
            return threads::terminated;
        }

        ///////////////////////////////////////////////////////////////////////
        // Each of the exposed functions needs to be encapsulated into an action
        // type, allowing to generate all required boilerplate code for threads,
        // serialization, etc.
        typedef hpx::actions::action0<
            simple_accumulator, accumulator_init, 
            &simple_accumulator::init
        > init_action;

        typedef hpx::actions::action1<
            simple_accumulator, accumulator_add, double, 
            &simple_accumulator::add
        > add_action;

        typedef hpx::actions::result_action0<
            simple_accumulator, double, accumulator_query_value, 
            &simple_accumulator::query
        > query_action;

        typedef hpx::actions::action0<
            simple_accumulator, accumulator_print, 
            &simple_accumulator::print
        > print_action;

    private:
        double arg_;
    };

}}}

#endif
