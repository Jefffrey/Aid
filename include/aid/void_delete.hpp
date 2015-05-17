#pragma once

namespace aid {

    template<typename Type>
    struct void_delete {
        void operator()(void* ptr) {
            delete static_cast<Type*>(ptr);
        }
    };

}
