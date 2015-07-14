#pragma once

#include <cassert>
#include <type_traits>
#include <iostream>

namespace aid {

    template<typename Type>
    class fractio {
    private:

        Type num;
        Type den;

    public:

        // intentionally not `explicit` to allow
        // implicit conversion from integral types to
        // fractio objects
        template<
            typename OtherType,
            typename  = typename std::enable_if<
                std::is_integral<Type>::value
                    && std::is_integral<OtherType>::value
            >::type
        >
        fractio(OtherType const& n)
            : num(n)
            , den(1)
            {}

        template<
            typename OtherType,
            typename = typename std::enable_if<
                std::is_integral<Type>::value
                    && std::is_integral<OtherType>::value
            >::type
        >
        fractio(OtherType const& n, OtherType const& d)
            : num(n)
            , den(d)
            {
            assert(den != 0);
        }

        Type numerator() const { return num; }
        Type denominator() const { return den; }

        fractio& invert() {
            assert(num != 0);
            std::swap(num, den);
            return (*this);
        }

        template<typename TypeRhs>
        fractio& operator*=(fractio<TypeRhs> const& rhs) {
            num *= rhs.num;
            den *= rhs.den;
            return (*this);
        }

        template<typename TypeRhs>
        fractio& operator/=(fractio<TypeRhs> rhs) {
            return (*this) *= rhs.invert();
        }

        // the following functions are friend in order to instantiate
        // them with the class and take advantage of the implicit conversion
        // from integral types to fractio

        friend fractio<Type> operator*(fractio<Type> lhs, fractio<Type> const& rhs) {
            return lhs *= rhs;
        }

        friend fractio<Type> operator/(fractio<Type> lhs, fractio<Type> const& rhs) {
            return lhs /= rhs;
        }

    };

    template<typename EvalType, typename Type>
    EvalType fractio_cast(fractio<Type> const& fr) {
        return EvalType(fr.numerator()) / EvalType(fr.denominator());
    }

    template<typename Type>
    fractio<Type> inverse(fractio<Type> obj) {
        return obj.invert();
    }

    template<typename Type>
    bool operator==(fractio<Type> const& lhs, Type const& rhs) {
        return lhs.numerator() == rhs
            && (lhs.denominator() == Type(1)
                || lhs.numerator() == Type(0));
    }

    template<typename Type>
    bool operator==(Type const& lhs, fractio<Type> const& rhs) {
        return rhs == lhs; 
    }

    template<typename Type>
    bool operator!=(fractio<Type> const& lhs, Type const& rhs) {
        return !(lhs == rhs);
    }

    template<typename Type>
    bool operator!=(Type const& lhs, fractio<Type> const& rhs) {
        return !(lhs == rhs);
    }

    template<typename Type>
    std::ostream& operator<<(std::ostream& os, fractio<Type> const& frac) {
        os << frac.numerator() << "/" << frac.denominator();
        return os;
    }

}
