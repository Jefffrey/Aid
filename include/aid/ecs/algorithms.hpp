#pragma once

#include <list>
#include <algorithm>

#include <aid/ecs/entity.hpp>

namespace aid {

    // Finds the first element in a container that has the
    // specified components.
    template<typename... Components, typename It>
    auto find_with(It begin, It end) {
        return std::find_if(begin, end, [](auto const& e) 
            { return spel::has<Components...>(e); });
    }

    // Transforms only entities with specified components
    // and leaves other entities untouched.
    template<typename...Components, typename It, typename Fn>
    void mutate_with(It begin, It end, Fn&& fn) {
        auto pred = [&fn](auto e) { 
            if (spel::has<Components...>(e))
                return fn(spel::get<Components>(e)...);
        };
        std::transform(begin, end, begin, pred);
    }

}
