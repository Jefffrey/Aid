#pragma once

#include <unordered_map>
#include <typeindex>
#include <boost/any.hpp>

namespace aid {

    class component_set {
    public:
        
        // construction
        component_set() = default;
        component_set(component_set&&) = default;
        component_set(component_set const& rhs) = delete;

        // assignment
        component_set& operator=(component_set&&) = default;
        component_set& operator=(component_set const&) = delete;

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
            return *static_cast<Component*>(it->second.get());
        }

        // component access
        template<typename Component>
        Component const& get() const {
            auto it = components.find(std::type_index(typeid(Component)));
            return *static_cast<Component*>(it->second.get());
        }

        // component addition
        template<typename Component, typename... Args>
        void add(Args&&... args) {
            auto component_deleter		
                = [](void* ptr) { delete static_cast<Component*>(ptr); };
            components.emplace
                ( std::type_index(typeid(Component))
                , component_type
                    ( new Component(std::forward<Args>(args)...)
                    , component_deleter ));
        }

        // component removal
        template<typename Component>
        void remove() {
            components.erase(std::type_index(typeid(Component)));
        }

    private:

        // attributes
        using component_type = std::unique_ptr<void, void(*)(void*)>;
        std::unordered_map<std::type_index, component_type> components;

    };

    // non member functions
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
