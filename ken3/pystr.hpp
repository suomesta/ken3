/**
 * @file    ken3/pystr.hpp
 * @brief   Define functions which imitates Python str class methods.
 *          This file does not contain implements but #include.
 * @author  toda
 * @date    2017-07-23
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 *
 * @note
 * General rules:
 * - All definitions are in namespace "pystr".
 * - In all functions, first argument is std::string (named 'self')
 *   and it coincides with str which calls method in Python.
 *   pystr::count("aaa", "a") is same as 'aaa'.count('a') in Python.
 * - Three exceptions are defined in this module, pystr::ValueError,
 *   pystr::IndexError, and pystr::TypeError. Those could be raised
 *   in same situations as python.
 * - std::vector<std::string> is used for all iterable string object.
 * - pystr::index_type is used to control str length. This type is
 *   created by removing unsigned from std::string::size_type.
 *   User should keep in mind that max value of pystr::index_type is
 *   smaller than std::string::size_type's one.
 * - Ascii is only supported code in this module.
 * - slice() imitates Python's slice operation.
 *   pystr::slice("abcde", 1, 4) is same as 'abcde'[1:4]
 *
 * Some limitations.
 * - 'format' is not supported.
 * - 'encode' is not supported, because only ascii string is allowed.
 * - '__class__', '__delattr__', '__doc__', '__format__',
 *   '__getattribute__', '__getnewargs__', '__hash__', '__init__',
 *   '__mod__', '__new__', '__reduce__', '__reduce_ex__', '__rmod__',
 *   '__rmul__', '__setattr__', '__sizeof__', '__str__', and
 *   '__subclasshook__' are not supported, because of differencies of
 *   language specification between Python and C++.
 * - '__iter__', 'format_map', 'isdecimal', 'isidentifier',
 *   'isnumeric', 'isprintable', and 'maketrans' are not supported,
 *   becuase these functions are not in Python 2.
 * - '__getslice__', '_formatter_field_name_split',
 *   '_formatter_parser', and 'decode' are not supported, because these
 *   functions are not in Python 3.
 * - 'translate' is not supported, because its specification has been
 *   changed a lot from Python 2 to Python 3.
 *
 * Following is a sample to use pystr::split() and pystr::upper().
 *     std::string s = "a,b,c";
 *     std::vector<std::string> v = ken3::pystr::split(s, ",");
 *     for (const auto& i: v) {
 *         std::cout << ken3::pystr::upper(i) << std::endl;
 *         // => "A"
 *         //    "B"
 *         //    "C"
 *     }
 */

#ifndef INCLUDE_GUARD_KEN3_PYSTR_HPP
#define INCLUDE_GUARD_KEN3_PYSTR_HPP

#include <limits>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>

namespace ken3 {
namespace pystr {

// define types
using index_type = std::make_signed<std::string::size_type>::type;

/**
 * @brief constant value which imitates Python None. 
 */
constexpr index_type None = std::numeric_limits<index_type>::lowest();
/////////////////////////////////////////////////////////////////////////////

/**
 * @class ValueError
 * @brief Exception which imitates Python ValueError. 
 */
struct ValueError : public std::runtime_error
{
    /**
     * @brief       constructor. 
     * @param[in]   msg: message for what(). 
     */
    explicit ValueError(const std::string& msg);
};
/////////////////////////////////////////////////////////////////////////////

/**
 * @class IndexError
 * @brief Exception which imitates Python IndexError. 
 */
struct IndexError : public std::runtime_error
{
    /**
     * @brief       constructor. 
     * @param[in]   msg: message for what(). 
     */
    explicit IndexError(const std::string& msg);
};
/////////////////////////////////////////////////////////////////////////////

/**
 * @class TypeError
 * @brief Exception which imitates Python TypeError. 
 */
struct TypeError : public std::runtime_error
{
    /**
     * @brief       constructor. 
     * @param[in]   msg: message for what(). 
     */
    explicit TypeError(const std::string& msg);
};
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__add__()
 *        pystr::add("abc", "a") <=> 'abc' + 'a' or 'abc'.__add__('a')
 */
std::string add(const std::string& self, const std::string& x);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__contains__()
 *        pystr::contains("abc", "a") <=> 'a' in 'abc' or 'abc'.__contains__('a')
 */
bool contains(const std::string& self, const std::string& x) noexcept;
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__eq__()
 *        pystr::eq("abc", "a") <=> 'abc' == 'a' or 'abc'.__eq__('a')
 */
bool eq(const std::string& self, const std::string& x) noexcept;
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__ge__()
 *        pystr::ge("abc", "a") <=> 'abc' >= 'a' or 'abc'.__ge__('a')
 */
bool ge(const std::string& self, const std::string& x) noexcept;
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__getitem__() with index
 *        pystr::getitem("abc", 1) <=> 'abc'[1] or 'abc'.__getitem__(1)
 * @throw ken3::pystr::IndexError: when index is out of range
 * @note  the return value is std::string (not char)
 */
std::string getitem(const std::string& self, index_type index);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__getitem__() with slice
 *        pystr::slice("abcde", 1, 4, 2) <=> 'abcde'[1:4:2] or 'abcde'.__getitem__(slice(1, 4, 2))
 * @throw ken3::pystr::ValueError: when step is 0
 */
std::string slice(const std::string& self, index_type start=None, index_type end=None, index_type step=None);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__gt__()
 *        pystr::gt("abc", "a") <=> 'abc' > 'a' or 'abc'.__gt__('a')
 */
bool gt(const std::string& self, const std::string& x) noexcept;
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__le__()
 *        pystr::le("abc", "a") <=> 'abc' <= 'a' or 'abc'.__le__('a')
 */
bool le(const std::string& self, const std::string& x) noexcept;
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__len__()
 *        pystr::len("abc") <=> len('abc') or 'abc'.__len__()
 */
index_type len(const std::string& self) noexcept;
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__lt__()
 *        pystr::lt("abc", "a") <=> 'abc' < 'a' or 'abc'.__lt__('a')
 */
bool lt(const std::string& self, const std::string& x) noexcept;
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__mul__()
 *        pystr::mul("abc", 3) <=> 'abc' * 3 or 'abc'.__mul__(3)
 */
std::string mul(const std::string& self, index_type n);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__ne__()
 *        pystr::ne("abc", "a") <=> 'abc' != 'a' or 'abc'.__ne__('a')
 */
bool ne(const std::string& self, const std::string& x) noexcept;
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__repr__()
 *        pystr::repr("abc") <=> repr('abc') or 'abc'.__repr__()
 */
std::string repr(const std::string& self);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.capitalize()
 *        pystr::capitalize("abc") <=> 'abc'.capitalize()
 */
std::string capitalize(const std::string& self);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.center()
 *        pystr::center("abc", 5) <=> 'abc'.center(5)
 * @throw ken3::pystr::TypeError: when fillchar is not one character
 * @note  the type of fillchar is not char.
 * @note  the behavior of str.centor() is little bit strange.
 *        see http://bugs.python.org/issue23624
 */
std::string center(const std::string& self, index_type width, const std::string& fillchar=std::string(" "));
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.count()
 *        pystr::count("abc", "a") <=> 'abc'.count('a')
 */
index_type count(const std::string& self, const std::string& sub, index_type start=None, index_type end=None);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.endswith() with str
 *        pystr::endswith("abc", "a") <=> 'abc'.endswith('a')
 */
bool endswith(const std::string& self, const std::string& suffix, index_type start=None, index_type end=None);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.endswith() with tuple
 *        pystr::endswith("abc", std::vector({"a", "b"})) <=> 'abc'.endswith(('a', 'b'))
 */
bool endswith(const std::string& self, const std::vector<std::string>& suffix, index_type start=None, index_type end=None);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.expandtabs()
 *        pystr::expandtabs("abc") <=> 'abc'.expandtabs()
 */
std::string expandtabs(const std::string& self, index_type tabsize=8);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.find()
 *        pystr::find("abc", "a") <=> 'abc'.find('a')
 */
index_type find(const std::string& self, const std::string& sub, index_type start=None, index_type end=None);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.index()
 *        pystr::index("abc", "a") <=> 'abc'.index('a')
 * @throw ken3::pystr::ValueError: when sub is not found in self
 */
index_type index(const std::string& self, const std::string& sub, index_type start=None, index_type end=None);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.isalnum()
 *        pystr::isalnum("abc") <=> 'abc'.isalnum()
 */
bool isalnum(const std::string& self);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.isalpha()
 *        pystr::isalpha("abc") <=> 'abc'.isalpha()
 */
bool isalpha(const std::string& self);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.isdigit()
 *        pystr::isdigit("abc") <=> 'abc'.isdigit()
 */
bool isdigit(const std::string& self);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.islower()
 *        pystr::islower("abc") <=> 'abc'.islower()
 */
bool islower(const std::string& self);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.isspace()
 *        pystr::isspace("abc") <=> 'abc'.isspace()
 */
bool isspace(const std::string& self);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.istitle()
 *        pystr::istitle("abc") <=> 'abc'.istitle()
 */
bool istitle(const std::string& self);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.isupper()
 *        pystr::isupper("abc") <=> 'abc'.isupper()
 */
bool isupper(const std::string& self);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.join()
 *        pystr::join("abc", std::vector({"a", "b"})) <=> 'abc'.join(['a', 'b'])
 */
std::string join(const std::string& self, const std::vector<std::string>& strs);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.ljust()
 *        pystr::ljust("abc", 5) <=> 'abc'.ljust(5)
 * @throw ken3::pystr::TypeError: when fillchar is not one character
 * @note  the type of fillchar is not char.
 */
std::string ljust(const std::string& self, index_type width, const std::string& fillchar=std::string(" "));
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.lower()
 *        pystr::lower("abc") <=> 'abc'.lower()
 */
std::string lower(const std::string& self);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.lstrip()
 *        pystr::lstrip("  abc") <=> '  abc'.lstrip()
 * @note  chars always str, None is not supported.
 */
std::string lstrip(const std::string& self, const std::string& chars=std::string(" "));
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.partition()
 *        pystr::partition("abc", "b") <=> 'abc'.partition('b')
 * @throw ken3::pystr::ValueError: when sep is empty
 */
std::vector<std::string> partition(const std::string& self, const std::string& sep);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.replace()
 *        pystr::replace("abc", "a", "b") <=> 'abc'.replace('a', 'b')
 */
std::string replace(const std::string& self, const std::string& old, const std::string& new_, index_type count=None);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.rfind()
 *        pystr::rfind("abc", "a") <=> 'abc'.rfind('a')
 */
index_type rfind(const std::string& self, const std::string& sub, index_type start=None, index_type end=None);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.rindex()
 *        pystr::rindex("abc", "a") <=> 'abc'.rindex('a')
 * @throw ken3::pystr::ValueError: when sub is not found in self
 */
index_type rindex(const std::string& self, const std::string& sub, index_type start=None, index_type end=None);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.rjust()
 *        pystr::rjust("abc", 5) <=> 'abc'.rjust(5)
 * @throw ken3::pystr::TypeError: when fill char is not one character
 * @note  the type of fillchar is not char.
 */
std::string rjust(const std::string& self, index_type width, const std::string& fillchar=std::string(" "));
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.rpartition()
 *        pystr::rpartition("abc", "b") <=> 'abc'.rpartition('b')
 * @throw ken3::pystr::ValueError: when sep is empty
 */
std::vector<std::string> rpartition(const std::string& self, const std::string& sep);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.rsplit()
 *        pystr::rsplit("abc", "b") <=> 'abc'.rsplit('b')
 * @throw ken3::pystr::ValueError: when sep is empty
 * @note  this function corresponds to str.rsplit(sep).
 */
std::vector<std::string> rsplit(const std::string& self, const std::string& sep, index_type maxsplit=None);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.rsplit()
 *        pystr::rsplit("abc") <=> 'abc'.rsplit()
 * @note  this function corresponds to str.rsplit() (without sep).
 */
std::vector<std::string> rsplit(const std::string& self, index_type maxsplit=None);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.rstrip()
 *        pystr::rstrip("abc  ") <=> 'abc  '.rstrip()
 * @note  chars always str, None is not supported.
 */
std::string rstrip(const std::string& self, const std::string& chars=std::string(" "));
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.split()
 *        pystr::split("abc", "b") <=> 'abc'.split('b')
 * @throw ken3::pystr::ValueError: when sep is empty
 * @note  this function corresponds to str.split(sep).
 */
std::vector<std::string> split(const std::string& self, const std::string& sep, index_type maxsplit=None);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.split()
 *        pystr::split("abc") <=> 'abc'.split()
 * @note  this function corresponds to str.split() (without sep).
 */
std::vector<std::string> split(const std::string& self, index_type maxsplit=None);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.splitlines()
 *        pystr::splitlines("ab\nc\n") <=> 'ab\nc\n'.splitlines()
 */
std::vector<std::string> splitlines(const std::string& self, bool keepends=false);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.startswith() with str
 *        pystr::startswith("abc", "a") <=> 'abc'.startswith('a')
 */
bool startswith(const std::string& self, const std::string& preffix, index_type start=None, index_type end=None);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.startswith() with tuple
 *        pystr::startswith("abc", std::vector({"a", "b"})) <=> 'abc'.startswith(('a', 'b'))
 */
bool startswith(const std::string& self, const std::vector<std::string>& preffix, index_type start=None, index_type end=None);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.strip()
 *        pystr::strip(" abc ") <=> ' abc '.strip()
 * @note  chars always str, None is not supported.
 */
std::string strip(const std::string& self, const std::string& chars=std::string(" "));
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.swapcase()
 *        pystr::swapcase("abc") <=> 'abc'.swapcase()
 */
std::string swapcase(const std::string& self);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.title()
 *        pystr::title("abc") <=> 'abc'.title()
 */
std::string title(const std::string& self);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.upper()
 *        pystr::upper("abc") <=> 'abc'.upper()
 */
std::string upper(const std::string& self);
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.zfill()
 *        pystr::zfill("abc", 5) <=> 'abc'.zfill(5)
 */
std::string zfill(const std::string& self, index_type width);
/////////////////////////////////////////////////////////////////////////////

} // namespace pystr {
} // namespace ken3 {

#endif // #ifndef INCLUDE_GUARD_KEN3_PYSTR_HPP

