/**
 * @file    biunique_map.hpp
 * @brief   Implementation of biunique_map class. 
 *          biunique_map is usefule when two kinds of data are biunique. 
 * @author  toda
 * @date    2016-11-24
 * @version 0.1.0
 * @remark  the target is C++11 or more
 * @remark  biunique_map works only with this header file
 *
 * @note
 * Typical usage is;
 *     ken3::biunique_map<char, int> bm{{'A', 10}, {'B', 11}, {'C', 12},
 *                                      {'D', 13}, {'E', 14}, {'F', 15}};
 *     std::cout << bm.f2s('A'); // => 10
 *     std::cout << bm.s2f(15); // => 'F'
 *
 * biunique means, both key value and mapped value are unique.
 *     ken3::biunique_map<char, int> bm{{'A', 10}, {'A', 11}}; // not allowed
 *     ken3::biunique_map<char, int> bm{{'A', 10}, {'B', 10}}; // not allowed
 */

#ifndef INCLUDE_GUARD_KEN3_BIUNIQUE_MAP_HPP
#define INCLUDE_GUARD_KEN3_BIUNIQUE_MAP_HPP

#include <map>
#include <stdexcept>
#include <type_traits>
#include <unordered_map>

namespace ken3 {

/**
 * @enum    biunique_map_type
 * @brief   type of biunique_map.
 *          ordered_no_default: biunique_map uses std::map for container. f2s() or s2f() 
 *                              may throw out_of_range.
 *          ordered_front_default: biunique_map uses std::map for container. f2s() or
 *                                 s2f() tries to find default value from front of std::map.
 *          ordered_back_default: biunique_map uses std::map for container. f2s() or
 *                                s2f() tries to find default value from back of std::map.
 *          unordered_no_default: biunique_map uses std::unordered_map for container. f2s()
 *                                or s2f() may throw out_of_range.
 */
enum class biunique_map_type
{
    ordered_no_default = 0,
    ordered_front_default,
    ordered_back_default,
    unordered_no_default,
};
/////////////////////////////////////////////////////////////////////////////

/**
 * @enum    biunique_map_policy
 * @brief   policy of biunique_map about inserting data.
 *          silence: biunique_map does nothing when duplex data is to be inserted. Just first win.
 *          throwing: biunique_map throws invalid_argument when duplex data is to be inserted.
 */
enum class biunique_map_policy
{
    silence = 0,
    throwing,
};
/////////////////////////////////////////////////////////////////////////////

/**
 * @class   biunique_map
 * @brief   A map class, which handles biunique key and value.
 *          Both key and value are kept as unique repectively.
 *          one of good example is ascii code. biunique_map{{10, 'A'}, {11, 'B'},
 *          {12, 'C'}, {13, 'D'}, {14, 'E'}, {15, 'f'}}.
 * @tparam  F: key type of biunique_map.
 * @tparam  S: mapped type of biunique_map.
 * @tparam  TYPE: biunique_map_type. default is ordered_no_default.
 * @tparam  POLICY: biunique_map_policy. default silence. 
 */
template <typename F, typename S, biunique_map_type TYPE=biunique_map_type::ordered_no_default, biunique_map_policy POLICY=biunique_map_policy::silence>
class biunique_map
{
    // static_asserts
    static_assert(
        TYPE == biunique_map_type::ordered_no_default ||
        TYPE == biunique_map_type::ordered_front_default ||
        TYPE == biunique_map_type::ordered_back_default ||
        TYPE == biunique_map_type::unordered_no_default,
        "unknown type for biunique_map"
    );
    static_assert(
        POLICY == biunique_map_policy::silence ||
        POLICY == biunique_map_policy::throwing,
        "unknown policy for biunique_map"
    );
    /////////////////////////////////////////////////////////////////////////////

public:
    // type definitions
    using map_type       = typename std::conditional<TYPE == biunique_map_type::unordered_no_default, std::unordered_map<F, S>, std::map<F, S>>::type;
    using key_type       = typename map_type::key_type;
    using mapped_type    = typename map_type::mapped_type;
    using value_type     = typename map_type::value_type;
    using size_type      = typename map_type::size_type;
    using const_iterator = typename map_type::const_iterator;
private:
    using self_type      = biunique_map<F, S, TYPE, POLICY>;
    template <biunique_map_type BMT, typename V = void> struct sType;
    template <biunique_map_type BMT> struct sType<BMT, typename std::enable_if<BMT == biunique_map_type::ordered_no_default>::type> {};
    template <biunique_map_type BMT> struct sType<BMT, typename std::enable_if<BMT == biunique_map_type::ordered_front_default>::type> {};
    template <biunique_map_type BMT> struct sType<BMT, typename std::enable_if<BMT == biunique_map_type::ordered_back_default>::type> {};
    template <biunique_map_type BMT> struct sType<BMT, typename std::enable_if<BMT == biunique_map_type::unordered_no_default>::type> {};
    template <biunique_map_policy BMP, typename V = void> struct sPolicy;
    template <biunique_map_policy BMP> struct sPolicy<BMP, typename std::enable_if<BMP == biunique_map_policy::silence>::type> {};
    template <biunique_map_policy BMP> struct sPolicy<BMP, typename std::enable_if<BMP == biunique_map_policy::throwing>::type> {};
    using my_type        = sType<TYPE>;
    using my_policy      = sPolicy<POLICY>;
    /////////////////////////////////////////////////////////////////////////////

public:
    /**
     * @brief      default-constructor, copy-constructor, move-constructor, destructor,
     *             copy-operator=, and move-operator= are default.
     */
    biunique_map(void) = default;
    biunique_map(const self_type& src) = default;
    biunique_map(self_type&& src) = default;
    self_type& operator=(const self_type& rhs) = default;
    self_type& operator=(self_type&& rhs) = default;
    ~biunique_map(void) = default;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      iterator constructor.
     * @param[in]  first: first iterator
     * @param[in]  last: last iterator
     */
    template <typename InputIt>
    biunique_map(InputIt first, InputIt last)
    {
        insert_impl(first, last, false, my_policy{});
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      constructor with initializer_list.
     * @param[in]  init: source of constructor
     * @note       if init includes duplex value,
     *             - duplex value is ignored if POLICY is Silence.
     *             - invalid_argument is thrown if POLICY is Throwing.
     */
    biunique_map(std::initializer_list<value_type> init)
    {
        insert_impl(init.begin(), init.end(), false, my_policy{});
    }
    /////////////////////////////////////////////////////////////////////////////


    /**
     * @brief      assignment with initializer_list.
     * @param[in]  init: right hand side of assignment
     * @note       if init includes duplex value,
     *             - duplex value is ignored if POLICY is Silence.
     *             - invalid_argument is thrown if POLICY is Throwing.
     */
    self_type& operator=(std::initializer_list<value_type> init)
    {
        operator=(biunique_map{init});
        return *this;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      equality operator.
     * @param[in]  rhs: right hand side of equality operator
     * @return     result of equality operator
     */
    bool operator==(const self_type& rhs) const
    {
        if (size() != rhs.size()) {
            return false;
        }
        for (auto i = rhs.cbegin(); i != rhs.cend(); ++i) {
            auto j = m_.find(i->first);
            if (j == m_.end()) {
                return false;
            }
            else if (i->second != j->second) {
                return false;
            }
        }
        return true;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      inequality operator.
     * @param[in]  rhs: right hand side of inequality operator
     * @return     result of inequality operator
     */
    bool operator!=(const self_type& rhs) const
    {
        return !(*this == rhs);
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      swap with another
     * @param[in,out] rhs: right hand side of swap
     */
    void swap(self_type& rhs) noexcept
    {
        m_.swap(rhs.m_);
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      get size.
     * @return     size of map.
     */
    size_type size(void) const noexcept
    {
        return m_.size();
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      get empty or not.
     * @return     true: empty, false: not empty
     */
    bool empty(void) const noexcept
    {
        return m_.empty();
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      get begin iterator.
     * @return     begin
     * @note       this class does not support non-const begin()
     */
    const_iterator cbegin(void) const noexcept
    {
        return m_.cbegin();
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      get end iterator.
     * @return     end
     * @note       this class does not support non-const end()
     */
    const_iterator cend(void) const noexcept
    {
        return m_.cend();
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      clear all data
     */
    void clear(void) noexcept
    {
        m_.clear();
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      insert from another biunique_map.
     * @param[in]  m: source of inserting
     * @note       if m includes duplex value,
     *             - duplex value is ignored if POLICY is Silence.
     *             - invalid_argument is thrown if POLICY is Throwing.
     */
    void insert(const self_type& m)
    {
        insert_impl(m.cbegin(), m.cend(), true, my_policy{});
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      insert from initializer_list.
     * @param[in]  init: source of inserting
     * @note       if init includes duplex value,
     *             - do nothing if POLICY is Silence.
     *             - invalid_argument is thrown if POLICY is Throwing.
     */
    void insert(std::initializer_list<value_type> init)
    {
        insert_impl(init.begin(), init.end(), false, my_policy{});
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      insert iterator.
     * @param[in]  first: first iterator
     * @param[in]  last: last iterator
     */
    template <typename InputIt>
    void insert(InputIt first, InputIt last)
    {
        insert_impl(first, last, false, my_policy{});
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      insert from value_type.
     * @param[in]  v: source of inserting
     * @note       if v includes duplex value,
     *             - do nothing if POLICY is Silence.
     *             - invalid_argument is thrown if POLICY is Throwing.
     */
    void insert(const value_type& v)
    {
        std::initializer_list<value_type> init = {v};
        insert_impl(init.begin(), init.end(), false, my_policy{});
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      insert from another biunique_map.
     * @param[in]  f: key value to be inserted.
     * @param[in]  s: mapped value to be inserted.
     * @note       if f or s is duplex value,
     *             - do nothing if POLICY is Silence.
     *             - invalid_argument is thrown if POLICY is Throwing.
     */
    void insert(const F& f, const S& s)
    {
        std::initializer_list<value_type> init = {{f, s}};
        insert_impl(init.begin(), init.end(), false, my_policy{});
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      check if f is already registered as key value.
     * @param[in]  f: key value to be checked.
     * @return     true: f is already registered, false: not registered
     * @note       this method helps to avoid throwing exception by f2s().
     */
    bool has_f(const F& f) const
    {
        return m_.find(f) != m_.cend();
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      check if s is already registered as mapped value.
     * @param[in]  s: mapped value to be checked.
     * @return     true: s is already registered, false: not registered
     * @note       this method helps to avoid throwing exception by s2f().
     */
    bool has_s(const S& s) const
    {
        for (const auto& i: m_) {
            if (s == i.second) {
                return true;
            }
        }
        return false;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      erase one pair by key value.
     * @param[in]  f: key value to be removed.
     * @note       nothing happenes if f is not registered.
     */
    void erase_by_f(const F& f)
    {
        m_.erase(f);
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      erase one pair by mapped value.
     * @param[in]  s: mapped value to be removed.
     * @note       nothing happenes if s is not registered.
     */
    void erase_by_s(const S& s)
    {
        for (const auto& i: m_) {
            if (s == i.second) {
                m_.erase(i.first);
                break;
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      convert from key value to mapped value.
     * @param[in]  f: key value.
     * @return     mapped value, which is connected to f.
     * @note       if f is not found in map,
     *             - out_of_range is thrown if TYPE is ordered_no_default.
     *             - mapped value of front (std::map::cbegin()->second) is returned
     *               if POLICY is ordered_front_default. if map is empty, then
     *               out_of_range is thrown.
     *             - mapped value of back (std::map::crbegin()->second) is returned
     *               if POLICY is ordered_back_default. if map is empty, then
     *               out_of_range is thrown.
     *             - out_of_range is thrown if TYPE is unordered_no_default.
     *             To avoid exception, call has_f() and check return value before 
     *             calling this method.
     */
    const S& f2s(const F& f) const
    {
        auto i = m_.find(f);
        if (i != m_.cend()) {
            return i->second;
        }
        return throw_or_default<false>(my_type{});
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      convert from mapped value to key value.
     * @param[in]  s: mapped value.
     * @return     key value, which is connected to s.
     * @note       if s is not found in map,
     *             - out_of_range is thrown if TYPE is ordered_no_default.
     *             - key value of front (std::map::cbegin()->first) is returned
     *               if POLICY is ordered_front_default. out_of_range is thrown,
     *               if map is empty.
     *             - key value of back (std::map::crbegin()->first) is returned
     *               if POLICY is ordered_back_default. out_of_range is thrown,
     *               if map is empty.
     *             - out_of_range is thrown if TYPE is unordered_no_default.
     *             To avoid exception, call has_s() and check return value before 
     *             calling this method.
     */
    const F& s2f(const S& s) const
    {
        for (const auto& i: m_) {
            if (s == i.second) {
                return i.first;
            }
        }
        return throw_or_default<true>(my_type{});
    }
    /////////////////////////////////////////////////////////////////////////////

private:
    /**
     * @brief      process to get value when appointed key is not found.
     * @tparam     FIRST: if true, get first. else, get second.
     * @param[in]  dummy: compile switcher. in this case, TYPE == ordered_no_default.
     * @return     never returns. always throw std::out_of_range
     * @throw      std::out_of_range: always.
     */
    template <bool FIRST>
    typename std::conditional<FIRST, const F&, const S&>::type throw_or_default(sType<biunique_map_type::ordered_no_default> dummy) const
    {
        throw std::out_of_range("");
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      process to get value when appointed key is not found.
     * @tparam     FIRST: if true, get first. else, get second.
     * @param[in]  dummy: compile switcher. in this case, TYPE == ordered_front_default.
     * @return     first or second of map.begin()
     * @throw      std::out_of_range: when map is empty
     */
    template <bool FIRST>
    typename std::conditional<FIRST, const F&, const S&>::type throw_or_default(sType<biunique_map_type::ordered_front_default> dummy) const
    {
        if (m_.empty()) {
            throw std::out_of_range("");
        }
        return std::get<FIRST ? 0 : 1>(*m_.cbegin());
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      process to get value when appointed key is not found.
     * @tparam     FIRST: if true, get first. else, get second.
     * @param[in]  dummy: compile switcher. in this case, TYPE == ordered_back_default.
     * @return     first or second of map.rbegin()
     * @throw      std::out_of_range: when map is empty
     */
    template <bool FIRST>
    typename std::conditional<FIRST, const F&, const S&>::type throw_or_default(sType<biunique_map_type::ordered_back_default> dummy) const
    {
        if (m_.empty()) {
            throw std::out_of_range("");
        }
        return std::get<FIRST ? 0 : 1>(*m_.crbegin());
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      process to get value when appointed key is not found.
     * @tparam     FIRST: if true, get first. else, get second.
     * @param[in]  dummy: compile switcher. in this case, TYPE == unordered_no_default.
     * @return     never returns. always throw std::out_of_range
     * @throw      std::out_of_range: always.
     */
    template <bool FIRST>
    typename std::conditional<FIRST, const F&, const S&>::type throw_or_default(sType<biunique_map_type::unordered_no_default> dummy) const
    {
        throw std::out_of_range("");
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      process to insert items.
     * @tparam     InputIt: iterator type.
     * @param[in]  first: first iterator
     * @param[in]  last: last iterator
     * @param[in]  self: true means the iterator type is self_type's iterator.
     *                   in this function, this argument is not used.
     * @param[in]  dummy: compile switcher. in this case, POLICY == Silence.
     */
    template <typename InputIt>
    void insert_impl(InputIt first, InputIt last, bool self, sPolicy<biunique_map_policy::silence> dummy)
    {
        for (auto i = first; i != last; ++i) {
            if (!has_f(i->first) && !has_s(i->second)) {
                m_.insert(*i);
            } 
       }
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      process to insert items.
     * @tparam     InputIt: iterator type.
     * @param[in]  first: first iterator
     * @param[in]  last: last iterator
     * @param[in]  self: true means the iterator type is self_type's iterator.
     *                   thus, iterator data is already biunique.
     *                   if this is false, need to check whether the input is 
     *                   biunique or not.
     * @param[in]  dummy: compile switcher. in this case, POLICY == Throwing.
     * @throw      std::invalid_argument: if fails to insert an item.
     */
    template <typename InputIt>
    void insert_impl(InputIt first, InputIt last, bool self, sPolicy<biunique_map_policy::throwing> dummy)
    {
        if (not self) {
            for (auto i = first; i != last; ++i) {
                for (auto j = std::next(i, 1); j != last; ++j) {
                    if ((i->first == j->first) || (i->second == j->second)) {
                        throw std::invalid_argument("");
                    }
                }
            }
        }

        for (const auto& i: m_) {
            for (auto j = first; j != last; ++j) {
                if ((i.first == j->first) || (i.second == j->second)) {
                    throw std::invalid_argument("");
                }
            }
        }

        for (auto i = first; i != last; ++i) {
            m_.insert(*i);
        }
    }
    /////////////////////////////////////////////////////////////////////////////

private:
    map_type m_; // stores biunique map data
};
/////////////////////////////////////////////////////////////////////////////

} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_BIUNIQUE_MAP_HPP

