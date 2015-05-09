#pragma once

#include <unordered_map>
#include <typeindex>
#include <boost/any.hpp>

namespace aid {

    class entity {
    public:
        
        // construction
        entity() = default;
        entity(entity const&) = default;
        entity(entity&&) = default;

        // assignment
        entity& operator=(entity const&) = default;
        entity& operator=(entity&&) = default;

        // component query
        template<typename Component, typename Component2, typename... Components>
        bool has() const {
            return has<Component>() && has<Component2, Components...>();
        }

        template<typename Component>
        bool has() const {
            auto it = components.find(std::type_index(typeid(Component)));
            return it != components.end();
        }

        // component access
        template<typename Component>
        Component& get() {
            auto it = components.find(std::type_index(typeid(Component)));
            return boost::any_cast<Component&>(it->second);
        }

        // component access
        template<typename Component>
        Component const& get() const {
            auto it = components.find(std::type_index(typeid(Component)));
            return boost::any_cast<Component&>(it->second);
        }

        // component addition
        template<typename Component, typename... Args>
        void add(Args&&... args) {
            components.emplace
                ( std::type_index(typeid(Component))
                , Component(std::forward<Args>(args)...));
        }

        // component removal
        template<typename Component>
        void remove() {
            components.erase(std::type_index(typeid(Component)));
        }

    private:

        // attributes
        using component_type = boost::any;
        std::unordered_map<std::type_index, component_type> components;

    };

    // non member functions
    template<typename... Components>
    inline bool has(entity const& e) { return e.has<Components...>(); }

    template<typename Component>
    inline Component& get(entity& e) { return e.get<Component>(); }

    template<typename Component>
    inline Component const& get(entity const& e) { return e.get<Component>(); }

    template<typename Component, typename... Args>
    inline void add(entity& e, Args... args) { 
        e.add<Component>(std::forward<Args>(args)...);
    }

    template<typename Component>
    inline void remove(entity& e) { e.remove<Component>(); }

}
