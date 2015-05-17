#pragma once

#include <unordered_map>
#include <typeindex>
#include <boost/any.hpp>

namespace aid {

    class component_set {
    public:
        
        component_set() = default;
        component_set(component_set&&) = default;
        component_set(component_set const&) = default; 
        component_set& operator=(component_set&&) = default;
        component_set& operator=(component_set const&) = default;

        template<typename Component, typename Component2, typename... Components>
        bool has() const {
            return has<Component>() && has<Component2, Components...>();
        }

        template<typename Component>
        bool has() const {
            auto it = components.find(std::type_index(typeid(Component)));
            return it != components.end();
        }

        template<typename Component>
        Component& get() {
            auto it = components.find(std::type_index(typeid(Component)));
            return boost::any_cast<Component&>(it->second);
        }

        template<typename Component>
        Component const& get() const {
            auto it = components.find(std::type_index(typeid(Component)));
            return boost::any_cast<Component&>(it->second);
        }

        template<typename Component, typename... Args>
        void add(Args&&... args) {
            components.emplace
                ( std::type_index(typeid(Component))
                , Component(std::forward<Args>(args)...) );
        }

        template<typename Component>
        void remove() {
            components.erase(std::type_index(typeid(Component)));
        }

    private:

        using container_type = std::unordered_map<std::type_index, boost::any>;
        container_type components;

    };

    template<typename... Components>
    inline bool has(component_set const& e) { return e.has<Components...>(); }

    template<typename Component>
    inline Component& get(component_set& e) { return e.get<Component>(); }

    template<typename Component>
    inline Component const& get(component_set const& e) { return e.get<Component>(); }

    template<typename Component, typename... Args>
    inline void add(component_set& e, Args... args) { 
        e.add<Component>(std::forward<Args>(args)...);
    }

    template<typename Component>
    inline void remove(component_set& e) { e.remove<Component>(); }

}
