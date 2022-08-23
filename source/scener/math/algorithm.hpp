// Copyright (c) Carlos Guzmán Álvarez. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#ifndef SCENER_MATH_ALGORITHM_HPP
#define SCENER_MATH_ALGORITHM_HPP

namespace scener::math::algorithm
{
    template <class InputIterator1, class InputIterator2, class InputIterator3, class OutputIterator, class TernaryOperation>
    inline OutputIterator transform(
        InputIterator1 first1, InputIterator1   last1, InputIterator2 first2, InputIterator3 first3,
        OutputIterator result, TernaryOperation ternary_op)
    {
        for (; first1 != last1; ++first1, (void) ++first2, (void) ++first3, ++result)
        {
            *result = ternary_op(*first1, *first2, *first3);
        }
        return result;
    }

    template <class InputIterator1, class InputIterator2, class InputIterator3, class InputIterator4, class OutputIterator, class QuaternaryOperation>
    inline OutputIterator transform(
        InputIterator1 first1, InputIterator1   last1, InputIterator2 first2, InputIterator3 first3, InputIterator4 first4,
        OutputIterator result, QuaternaryOperation quaternary_op)
    {
        for (; first1 != last1; ++first1, (void) ++first2, (void) ++first3, (void) ++first4, ++result)
        {
            *result = quaternary_op(*first1, *first2, *first3, *first4);
        }
        return result;
    }
}

#endif // SCENER_MATH_ALGORITHM_HPP
