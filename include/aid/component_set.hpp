#pragma once

#include <unordered_map>
#include <typeindex>

namespace aid {

    class component_set {
    private:

        struct placeholder;
        using component_type = std::unique_ptr<placeholder>;
        using container_type = std::unordered_map<std::type_index, component_type>;

    public:
        
        component_set() = default;

        component_set(component_set&&)
            noexcept(std::is_nothrow_move_constructible<container_type>::value)
            = default;

        component_set(component_set const& rhs) { (*this) = rhs; }

        component_set& operator=(component_set&&)
            noexcept(std::is_nothrow_move_assignable<container_type>::value)
            = default;

        component_set& operator=(component_set const& rhs) {
            for (auto const& p : rhs.components)
                components.emplace
                    ( p.second->type_index()
                    , p.second->clone() );
        }

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
            return static_cast<holder<Component>*>(it->second.get())->component;
        }

        template<typename Component>
        Component const& get() const {
            auto it = components.find(std::type_index(typeid(Component)));
            return static_cast<holder<Component>*>(it->second.get())->component;
        }

        template<typename Component, typename... Args>
        void add(Args&&... args) {
            components.emplace
                ( std::type_index(typeid(Component))
                , component_type(new holder<Component>(Component(std::forward<Args>(args)...))));
        }

        template<typename Component>
        void remove() {
            components.erase(std::type_index(typeid(Component)));
        }

    private:

        struct placeholder {

            virtual std::type_index type_index() const = 0;
            virtual std::unique_ptr<placeholder> clone() const = 0;
            virtual ~placeholder() noexcept = default;

        };

        template<typename ComponentType>
        struct holder : placeholder {

            holder() = default;
            holder(holder&&) = default;
            holder(holder const&) = default;

            explicit holder(ComponentType const& rhs)
                : component(rhs)
                {}

            explicit holder(ComponentType&& rhs)
                : component(std::move(rhs))
                {}

            virtual std::type_index type_index() const override {
                return std::type_index(typeid(ComponentType));
            }

            virtual std::unique_ptr<placeholder> clone() const override {
                return std::unique_ptr<placeholder>
                    (new holder<ComponentType>(component));
            }

            ComponentType component;

        };

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
