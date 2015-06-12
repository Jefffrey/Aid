#pragma once

namespace aid {

    template<typename TypeNum, typename TypeDenum = TypeNum>
    struct fractio {
        fractio(TypeNum n, TypeDenum d)
            : numerator(n)
            , denumerator(d)
            {}

        fractio(TypeNum n)
            : numerator(n)
            , denumerator(1)
            {}

        TypeNum numerator;
        TypeDenum denumerator;
    };

    template<typename EvalType, typename TypeNum, typename TypeDenum>
    EvalType evaluate(fractio<TypeNum, TypeDenum> const& fr) {
        return EvalType(fr.numerator) / EvalType(fr.denumerator);
    }

}
