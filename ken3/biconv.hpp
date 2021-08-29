/**
 * @file    ken3/biconv.hpp
 * @brief   Implementation of biconv class. 
 *          Bidirection convert an element to another element. 
 *          This is lightweight version of ken3::biunique_map. 
 * @author  toda
 * @date    2021-08-03
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 * @remark  this module works only with this header file.
 *
 * @note
 * Typical usage is;
 *     ken3::biconv<char, int> bc{{'A', 10}, {'B', 11}, {'C', 12},
 *                                {'D', 13}, {'E', 14}, {'F', 15}};
 *     std::cout << bc.convert('A'); // => 10
 *     std::cout << bc.rconvert(15); // => 'F'
 */

#ifndef INCLUDE_GUARD_KEN3_BICONV_HPP
#define INCLUDE_GUARD_KEN3_BICONV_HPP

#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <utility>
#include <vector>

namespace ken3 {

/**
 * @class   biconv
 * @brief   This class holds two datasets, one is F, the other is S.
 *          F and S are set by initializer_list<std::pair<F, S>> in constructor.
 *          biconv::convert() converts F to S.
 *          biconv::rconvert() converts S to F.
 * @tparam  F: type of first dataset.
 * @tparam  S: type of second dataset.
 */
template <typename F, typename S>
class biconv {
    // type definition
public:
    using value_type = std::pair<F, S>;
private:
    using self_type = biconv<F, S>;
    /////////////////////////////////////////////////////////////////////////////

public:
    /**
     * @brief      implicit constructors, copy operators, and destructor.
     */
    biconv(void) = default;
    biconv(const self_type& src) = default;
    biconv(self_type&& src) = default;
    self_type& operator=(const self_type& rhs) = delete;
    self_type& operator=(self_type&& rhs) = delete;
    ~biconv(void) noexcept = default;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      constructor with initializer_list.
     * @param[in]  init: paired data to be registered.
     */
    biconv(std::initializer_list<value_type> init):
        values_(init.begin(), init.end())
    {
        ;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      convert an element of first dataset to a second dataset element.
     * @param[in]  f: appointed element of first dataset.
     * @return     converted element of second dataset.
     * @throw      std::out_of_range: if f is not found in first dataset.
     */
    S convert(const F& f) const
    {
        auto iter = find<0>(f);
        if (iter != values_.end()) {
            return iter->second;
        }
        throw std::out_of_range("biconv::conv()");
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      convert an element of first dataset to a second dataset element.
     * @param[in]  f: appointed element of first dataset.
     * @return     converted element of second dataset. if f is not found in first dataset,
     *             then defaultS is returned.
     */
    S convert(const F& f, const S& defaultS) const
    {
        auto iter = find<0>(f);
        return (iter != values_.end()) ? iter->second : defaultS;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      convert an element of second dataset to a second first dataset element.
     * @param[in]  s: appointed element of second dataset.
     * @return     converted element of first dataset.
     * @throw      std::out_of_range: if s is not found in second dataset.
     */
    F rconvert(const S& s) const
    {
        auto iter = find<1>(s);
        if (iter != values_.end()) {
            return iter->first;
        }
        throw std::out_of_range("biconv::rconv()");
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      convert an element of second dataset to a first dataset element.
     * @param[in]  s: appointed element of second dataset.
     * @return     converted element of first dataset. if s is not found in second dataset,
     *             then defaultF is returned.
     */
    F rconvert(const S& s, const F& defaultF) const
    {
        auto iter = find<1>(s);
        return (iter != values_.end()) ? iter->first : defaultF;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      check if f is in first dataset.
     * @param[in]  f: appointed element of first dataset.
     * @return     true: found. false: not found.
     */
    bool containF(const F& f) const
    {
        return find<0>(f) != values_.end();
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      check if s is in second dataset.
     * @param[in]  s: appointed element of second dataset.
     * @return     true: found. false: not found.
     */
    bool containS(const S& s) const
    {
        return find<1>(s) != values_.end();
    }
    /////////////////////////////////////////////////////////////////////////////

private:
    /**
     * @brief      find check if s is in second dataset.
     * @param[in]  element: appointed element of dataset.
     * @tparam     N: 0 means first dataset, 1 means second dataset.
     * @return     found iterator value_type. maybe values_end().
     */
    template <size_t N>
    typename std::vector<value_type>::const_iterator find(const typename std::tuple_element<N, value_type>::type& element) const
    {
        return std::find_if(
            values_.begin(), values_.end(), 
            [&element] (const value_type& i) { return std::get<N>(i) == element; }
        );
    }
    /////////////////////////////////////////////////////////////////////////////

    const std::vector<value_type> values_; // registered datasets
    /////////////////////////////////////////////////////////////////////////////

};
/////////////////////////////////////////////////////////////////////////////

} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_BICONV_HPP
