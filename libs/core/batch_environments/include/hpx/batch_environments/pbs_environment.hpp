//  Copyright (c) 2007-2022 Hartmut Kaiser
//  Copyright (c) 2013-2015 Thomas Heller
//
//  SPDX-License-Identifier: BSL-1.0
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#pragma once

#include <hpx/config.hpp>

#include <cstddef>
#include <string>
#include <vector>

namespace hpx::util::batch_environments {

    struct pbs_environment
    {
        HPX_CORE_EXPORT pbs_environment(
            std::vector<std::string>& nodelist, bool have_mpi, bool debug);

        constexpr bool valid() const noexcept
        {
            return valid_;
        }

        constexpr std::size_t node_num() const noexcept
        {
            return node_num_;
        }

        constexpr std::size_t num_threads() const noexcept
        {
            return num_threads_;
        }

        constexpr std::size_t num_localities() const noexcept
        {
            return num_localities_;
        }

    private:
        std::size_t node_num_;
        std::size_t num_localities_;
        std::size_t num_threads_;
        bool valid_;

        HPX_CORE_EXPORT void read_nodefile(
            std::vector<std::string>& nodelist, bool have_mpi, bool debug);
        HPX_CORE_EXPORT void read_nodelist(
            std::vector<std::string>& nodelist, bool debug);
    };
}    // namespace hpx::util::batch_environments
