/**
 * @file    ken3/typenames.hpp
 * @brief   Implementation of typenames class. 
 *          typenames can convert type into type name string. 
 * @author  toda
 * @date    2021-04-04
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 *
 * @note
 * Typical usage is;
 *     ken3::typenames tn;
 *     std::cout << tn.str_of<int>(); // => "int"
 *     std::cout << tn.str_of<unsigned short>(); // => "unsigned short"
 * 
 * any type can be registerred or replaced
 *     tn.register_str<std::vector<int>>("std::vector<int>");
 *     tn.register_str<unsigned short>("uint16_t");
 *     std::cout << tn.str_of<std::vector<int>>(); // => "std::vector<int>"
 *     std::cout << tn.str_of<unsigned short>(); // => "uint16_t"
 */

#ifndef INCLUDE_GUARD_KEN3_TYPENAMES_HPP
#define INCLUDE_GUARD_KEN3_TYPENAMES_HPP

#include <string>
#include <typeinfo>
#include <typeindex>
#include <unordered_map>

namespace ken3 {

class typenames {
public:
    /**
     * @brief      default_constructor, copy-constructor, move-constructor, destructor,
     *             copy-operator=,  and move-operator= are default.
     */
    typenames(void) = default;
    typenames(const typenames& src) = default;
    typenames(typenames&& src) noexcept = default;
    ~typenames(void) noexcept = default;
    typenames& operator=(const typenames& rhs) = default;
    typenames& operator=(typenames&& rhs) noexcept = default;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      register a string as type name.
     *             if the type is already registerred, then old string is overwritten.
     * @param[in]  value: appointed string
     * @tparam     T: appointed type
     */
    template <typename T>
    void register_str(const std::string& value) {
        table_[std::type_index(typeid(T))] = value;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      get type name.
     * @tparam     T: appointed type
     * @return     gotten type name
     * @throw      std::out_of_range: if T is not registerred
     */
    template <typename T>
    std::string str_of() {
        return table_.at(std::type_index(typeid(T)));
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief      get whole type names data.
     * @return     type names data in std::unordered_map
     */
    std::unordered_map<std::type_index, std::string> copy_map() {
        return table_;
    }
    /////////////////////////////////////////////////////////////////////////////

private:
    std::unordered_map<std::type_index, std::string> table_{
        {std::type_index(typeid(bool)), "bool"},
        {std::type_index(typeid(char)), "char"},
        {std::type_index(typeid(signed char)), "signed char"},
        {std::type_index(typeid(unsigned char)), "unsigned char"},
        {std::type_index(typeid(short)), "short"},
        {std::type_index(typeid(unsigned short)), "unsigned short"},
        {std::type_index(typeid(int)), "int"},
        {std::type_index(typeid(unsigned int)), "unsigned int"},
        {std::type_index(typeid(long)), "long"},
        {std::type_index(typeid(unsigned long)), "unsigned long"},
        {std::type_index(typeid(long long)), "long long"},
        {std::type_index(typeid(unsigned long long)), "unsigned long long"},
        {std::type_index(typeid(float)), "float"},
        {std::type_index(typeid(double)), "double"},
        {std::type_index(typeid(long double)), "long double"},
        {std::type_index(typeid(char16_t)), "char16_t"},
        {std::type_index(typeid(char32_t)), "char32_t"},
        {std::type_index(typeid(wchar_t)), "wchar_t"},
        {std::type_index(typeid(decltype(nullptr))), "std::nullptr_t"},
    };
};
/////////////////////////////////////////////////////////////////////////////

} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_TYPENAMES_HPP
