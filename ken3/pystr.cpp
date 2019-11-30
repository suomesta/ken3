/**
 * @file    ken3/pystr.cpp
 * @brief   Implementation of pystr functions. 
 * @author  toda
 * @date    2016-06-29
 * @version 0.1.0
 * @remark  the target is C++11 or more.
 */

#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cctype>
#include <map>
#include "ken3/pystr.hpp"

namespace {

using ken3::pystr::index_type;
using ken3::pystr::None;
using ken3::pystr::ValueError;

/**
 * @brief     helper function to convert a characer into std::string for repr().
 * @param[in] c: appointed character
 * @return    converted string. it consists of three kinds.
 *            1) escape characters ex.) "\\t" whose length is 2
 *            2) binary expression ex.) "\\x2a" whose length is 4 and in lower case
 *            3) ascii characters ex.) "A"
 */
std::string conv_repr(char c)
{
    static const std::map<char, std::string> _esc = {
        {'\t', "\\t"}, {'\n', "\\n"}, {'\r', "\\r"}, {'\\', "\\\\"},
    };

    // special escape characters
    auto i = _esc.find(c);
    if (i != _esc.end()) {
        return i->second;
    }

    // non-ascci characters. return string which starts with "\\x"
    unsigned char uc;
    memcpy(&uc, &c, sizeof(uc));
    if ((uc < 0x20) || (uc >= 0x7f)) {
        char buf[16] = {'\0'};
        sprintf(buf, "\\x%02x", uc);
        return buf;
    }

    // ascci characters
    return std::string(1, c);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief     helper function to judge whether all {start, end, step} are
 *            default or not.
 * @param[in] start: start index for slice
 * @param[in] end: end index for slice
 * @param[in] step: step of slice
 * @return    true: all default value, flase: else
 */
bool all_default(index_type start=None, index_type end=None, index_type step=None)
{
    return (start == None && end == None && step == None);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief     helper class to arrange {start, end, step} for safety use.
 */
class slice_object {
public:
    /**
     * @brief     constructor to have valid {start, end, step}.
     * @param[in] size: appointed string size
     * @param[in] start: start index for slice
     * @param[in] end: end index for slice
     * @param[in] step: step of slice
     * @throw     ken3::pystr::ValueError: when step is 0
     */
    explicit slice_object(index_type size, index_type start=None, index_type end=None, index_type step=None) :
        start_(start),
        end_(end),
        step_(step)
    {
        // set step
        if (step_ == 0) {
            throw ValueError("slice step cannot be zero");
        }
        else if (step_ == None) {
            step_ = 1;
        }

        // set start
        if (start_ == None) {
            start_ = (step_ >= 0) ? 0 : size - 1;
        }
        else if (start_ < 0) {
            start_ += size;
            if (start_ < 0) {
                start_ = (step_ >= 0) ? 0 : -1;
            }
        }
        else if (start_ > size) {
            if (step_ < 0) {
                start_ = size - 1;
            }
        }

        // set end
        if (end_ == None) {
            end_ = (step_ >= 0) ? size : -1;
        }
        else if (end_ < 0) {
            end_ += size;
            if (end_ < 0) {
                end_ = (step_ >= 0) ? 0 : -1;
            }
        }
        else if (end_ > size) {
            if (step_ < 0) {
                end_ = size - 1;
            }
        }
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief     delete default constructor
     */
    slice_object(void) = delete;
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief     getter of start
     */
    index_type start(void) const
    {
        return start_;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief     getter of end
     */
    index_type end(void) const
    {
        return end_;
    }
    /////////////////////////////////////////////////////////////////////////////

    /**
     * @brief     getter of step
     */
    index_type step(void) const
    {
        return step_;
    }
    /////////////////////////////////////////////////////////////////////////////

private:
    index_type start_;
    index_type end_;
    index_type step_;
};
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief     helper function to get start position from {start, end, step}.
 * @param[in] self: string data
 * @param[in] start: start index for slice
 * @param[in] end: end index for slice
 * @param[in] step: step of slice
 * @return    start index
 * @throw     ken3::pystr::ValueError: when step is 0
 */
index_type offset(const std::string& self, index_type start=None, index_type end=None, index_type step=None)
{
    slice_object s(static_cast<index_type>(self.size()), start, end, step);

    return s.start();
}
/////////////////////////////////////////////////////////////////////////////

} // namespace {

namespace ken3 {
namespace pystr {

/**
 * @brief       constructor. 
 * @param[in]   msg: message for what(). 
 */
ValueError::ValueError(const std::string& msg) :
    std::runtime_error(std::string("ValueError: ") + msg)
{
    ;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief       constructor. 
 * @param[in]   msg: message for what(). 
 */
IndexError::IndexError(const std::string& msg) :
    std::runtime_error(std::string("IndexError: ") + msg)
{
    ;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief       constructor. 
 * @param[in]   msg: message for what(). 
 */
TypeError::TypeError(const std::string& msg) :
    std::runtime_error(std::string("TypeError: ") + msg)
{
    ;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__add__()
 *        pystr::add("abc", "a") <=> 'abc' + 'a' or 'abc'.__add__('a')
 */
std::string add(const std::string& self, const std::string& x)
{
    return self + x;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__contains__()
 *        pystr::contains("abc", "a") <=> 'a' in 'abc' or 'abc'.__contains__('a')
 */
bool contains(const std::string& self, const std::string& x) noexcept
{
    return self.find(x) != std::string::npos;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__eq__()
 *        pystr::eq("abc", "a") <=> 'abc' == 'a' or 'abc'.__eq__('a')
 */
bool eq(const std::string& self, const std::string& x) noexcept
{
    return self.compare(x) == 0;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__ge__()
 *        pystr::ge("abc", "a") <=> 'abc' >= 'a' or 'abc'.__ge__('a')
 */
bool ge(const std::string& self, const std::string& x) noexcept
{
    return self.compare(x) >= 0;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__getitem__()
 *        pystr::getitem("abc", 1) <=> 'abc'[1] or 'abc'.__getitem__(1)
 * @throw ken3::pystr::IndexError: when index is out of range
 * @note  the return value is std::string (not char)
 */
std::string getitem(const std::string& self, index_type index)
{
    index_type size = static_cast<index_type>(self.size());
    index_type new_index = (index >= 0) ? index : size + index;
    if ((new_index < 0) || (new_index >= size)) {
        throw IndexError("string index out of range");
    }

    return self.substr(new_index, 1);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__getitem__() with slice
 *        pystr::slice("abcde", 1, 4, 2) <=> 'abcde'[1:4:2] or 'abcde'.__getitem__(slice(1, 4, 2))
 * @throw ken3::pystr::ValueError: when step is 0
 */
std::string slice(const std::string& self, index_type start/*=None*/, index_type end/*=None*/, index_type step/*=None*/)
{
    const index_type size = static_cast<index_type>(self.size());
    slice_object s(size, start, end, step);

    std::string retval;

    if (s.step() > 0) {
        for (index_type i = s.start(); i < s.end(); i += s.step()) {
            if (i < 0 || i >= size) {
                break;
            }
            retval.push_back(self[i]);
        }
    }
    else {
        for (index_type i = s.start(); i > s.end(); i += s.step()) {
            if (i < 0 || i >= size) {
                break;
            }
            retval.push_back(self[i]);
        }
    }

    return retval;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__gt__()
 *        pystr::gt("abc", "a") <=> 'abc' > 'a' or 'abc'.__gt__('a')
 */
bool gt(const std::string& self, const std::string& x) noexcept
{
    return self.compare(x) > 0;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__le__()
 *        pystr::le("abc", "a") <=> 'abc' <= 'a' or 'abc'.__le__('a')
 */
bool le(const std::string& self, const std::string& x) noexcept
{
    return self.compare(x) <= 0;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__len__()
 *        pystr::len("abc") <=> len('abc') or 'abc'.__len__()
 */
index_type len(const std::string& self) noexcept
{
    return static_cast<index_type>(self.size());
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__lt__()
 *        pystr::lt("abc", "a") <=> 'abc' < 'a' or 'abc'.__lt__('a')
 */
bool lt(const std::string& self, const std::string& x) noexcept
{
    return self.compare(x) < 0;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__mul__()
 *        pystr::mul("abc", 3) <=> 'abc' * 3 or 'abc'.__mul__(3)
 */
std::string mul(const std::string& self, index_type n)
{
    if (n <= 0) {
        return std::string();
    }

    std::string retval;
    retval.reserve(self.size() * n);
    for (index_type i = 0; i < n; i++) {
        retval += self;
    }
    return retval;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__rmul__()
 *        pystr::rmul("abc", 3) <=> 3 * 'abc' or 'abc'.__rmul__(3)
 */
std::string rmul(const std::string& self, index_type n)
{
    if (n <= 0) {
        return std::string();
    }

    std::string retval;
    retval.reserve(self.size() * n);
    for (index_type i = 0; i < n; i++) {
        retval += self;
    }
    return retval;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__ne__()
 *        pystr::ne("abc", "a") <=> 'abc' != 'a' or 'abc'.__ne__('a')
 */
bool ne(const std::string& self, const std::string& x) noexcept
{
    return self.compare(x) != 0; 
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.__repr__()
 *        pystr::repr("abc") <=> repr('abc') or 'abc'.__repr__()
 */
std::string repr(const std::string& self)
{
    std::string ret;
    ret.reserve(self.size() + 2);

    for (const auto& i: self) {
        ret += conv_repr(i);
    }

    if (ret.find("'") == std::string::npos) {
        ret = std::string("'") + ret + std::string("'");
    }
    else {
        if (ret.find('"') == std::string::npos) {
            ret = std::string("\"") + ret + std::string("\"");
        }
        else {
            ret = std::string("'") + replace(ret, "'", "\\'") + std::string("'");
        }
    }

    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.capitalize()
 *        pystr::capitalize("abc") <=> 'abc'.capitalize()
 */
std::string capitalize(const std::string& self)
{
    std::string str(self);
    if (!str.empty()) {
        std::string::iterator first = str.begin();
        std::string::iterator second = std::next(first, 1);
        std::transform(first, second, first, ::toupper);
        std::transform(second, str.end(), second, ::tolower);
    }
    return str;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.casefold()
 *        pystr::casefold("abc") <=> 'abc'.casefold()
 */
std::string casefold(const std::string& self)
{
    std::string str(self);
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.center()
 *        pystr::center("abc", 5) <=> 'abc'.center(5)
 * @throw ken3::pystr::TypeError: when fillchar is not one character
 * @note  the behavior of str.centor() is little bit strange.
 *        see http://bugs.python.org/issue23624
 */
std::string center(const std::string& self, index_type width, const std::string& fillchar/*=std::string(" ")*/)
{
    if (fillchar.size() != 1) {
        throw TypeError("The fill character must be exactly one character long");
    }

    if (static_cast<index_type>(self.size()) >= width) {
        return self;
    }

    std::string str(width, fillchar.at(0));
    index_type fill_size = width - static_cast<index_type>(self.size());
    index_type offset = fill_size / 2;
    if ((fill_size % 2 != 0) && (self.size() % 2 == 0)) {
        // special adjustment
        offset = (fill_size + 1) / 2;
    }
    str.replace(offset, self.size(), self);
    return str;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.count()
 *        pystr::count("abc", "a") <=> 'abc'.count('a')
 */
index_type count(const std::string& self, const std::string& sub, index_type start/*=None*/, index_type end/*=None*/)
{
    const std::string& s = all_default(start, end) ? self : slice(self, start, end);

    if (sub.empty()) {
        return (static_cast<index_type>(s.size()) + 1);
    }

    index_type counter = 0;

    std::string::size_type pos = s.find(sub, 0);
    while (pos != std::string::npos) {
        counter++;

        pos = s.find(sub, pos + sub.size());
    }

    return counter;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.endswith() with str
 *        pystr::endswith("abc", "a") <=> 'abc'.endswith('a')
 */
bool endswith(const std::string& self, const std::string& suffix, index_type start/*=None*/, index_type end/*=None*/)
{
    const std::string& s = all_default(start, end) ? self : slice(self, start, end);

    std::string::size_type pos = s.rfind(suffix);
    return (pos != std::string::npos) && (pos + suffix.size() == s.size());
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.endswith() with tuple
 *        pystr::endswith("abc", std::vector({"a", "b"})) <=> 'abc'.endswith(('a', 'b'))
 */
bool endswith(const std::string& self, const std::vector<std::string>& suffix, index_type start/*=None*/, index_type end/*=None*/)
{
    const std::string& s = all_default(start, end) ? self : slice(self, start, end);

    for (const auto& i: suffix) {
        if (endswith(s, i)) {
            return true;
        }
    }

    return false;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.expandtabs()
 *        pystr::expandtabs("abc") <=> 'abc'.expandtabs()
 */
std::string expandtabs(const std::string& self, index_type tabsize/*=8*/)
{
    std::string str;
    str.reserve(self.size());

    index_type counter = 0;
    for (const auto& i: self) {
        if (i == '\t') {
            for (; counter < tabsize; counter++) {
                str += ' ';
            }
        }
        else if ((i == '\r') || (i == '\n')) {
            str += i;
            counter = 0;
        }
        else {
            str += i;
            counter++;
        }

        if (counter >= tabsize) {
            counter = 0;
        }
    }

    return str;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.find()
 *        pystr::find("abc", "a") <=> 'abc'.find('a')
 */
index_type find(const std::string& self, const std::string& sub, index_type start/*=None*/, index_type end/*=None*/)
{
    const std::string& s = all_default(start, end) ? self : slice(self, start, end);
    index_type offset_pos = all_default(start, end) ? 0 : offset(self, start, end);

    std::string::size_type pos = s.find(sub);
    if (pos != std::string::npos) {
        return static_cast<index_type>(pos) + offset_pos;
    }
    else {
        return -1;
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.index()
 *        pystr::index("abc", "a") <=> 'abc'.index('a')
 * @throw ken3::pystr::ValueError: when sub is not found in self
 */
index_type index(const std::string& self, const std::string& sub, index_type start/*=None*/, index_type end/*=None*/)
{
    const std::string& s = all_default(start, end) ? self : slice(self, start, end);
    index_type offset_pos = all_default(start, end) ? 0 : offset(self, start, end);

    std::string::size_type pos = s.find(sub);
    if (pos != std::string::npos) {
        return static_cast<index_type>(pos) + offset_pos;
    }
    else {
        throw ValueError("substring not found");
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.isalnum()
 *        pystr::isalnum("abc") <=> 'abc'.isalnum()
 */
bool isalnum(const std::string& self)
{
    return (
        not self.empty() &&
        std::all_of(self.begin(), self.end(), ::isalnum)
    );
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.isalpha()
 *        pystr::isalpha("abc") <=> 'abc'.isalpha()
 */
bool isalpha(const std::string& self)
{
    return (
        not self.empty() &&
        std::all_of(self.begin(), self.end(), ::isalpha)
    );
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.isascii()
 *        pystr::isascii("abc") <=> 'abc'.isascii()
 */
bool isascii(const std::string& self)
{
    return (
        std::all_of(self.begin(), self.end(), [](char c) { return ((0x00 <= c) && (c <= 0x7f)); })
    );
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.isdecimal()
 *        pystr::isdecimal("abc") <=> 'abc'.isdecimal()
 */
bool isdecimal(const std::string& self)
{
    return (
        not self.empty() &&
        std::all_of(self.begin(), self.end(), ::isdigit)
    );
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.isdigit()
 *        pystr::isdigit("abc") <=> 'abc'.isdigit()
 */
bool isdigit(const std::string& self)
{
    return (
        not self.empty() &&
        std::all_of(self.begin(), self.end(), ::isdigit)
    );
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.islower()
 *        pystr::islower("abc") <=> 'abc'.islower()
 */
bool islower(const std::string& self)
{
    return (
        std::any_of(self.begin(), self.end(), ::islower) &&
        std::none_of(self.begin(), self.end(), ::isupper)
    );
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.isnumeric()
 *        pystr::isnumeric("abc") <=> 'abc'.isnumeric()
 */
bool isnumeric(const std::string& self)
{
    return (
        not self.empty() &&
        std::all_of(self.begin(), self.end(), ::isdigit)
    );
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.isprintable()
 *        pystr::isprintable("abc") <=> 'abc'.isprintable()
 */
bool isprintable(const std::string& self)
{
    return (
        std::all_of(self.begin(), self.end(), [](char c) { return ((0x20 <= c) && (c <= 0x7e)); })
    );
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.isspace()
 *        pystr::isspace("abc") <=> 'abc'.isspace()
 */
bool isspace(const std::string& self)
{
    return (
        not self.empty() &&
        std::all_of(self.begin(), self.end(), ::isspace)
    );
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.istitle()
 *        pystr::istitle("abc") <=> 'abc'.istitle()
 */
bool istitle(const std::string& self)
{
    if (self.empty()) {
        return false;
    }

    bool pre_alpha = false;
    for (const auto& i: self) {
        if (std::isalpha(i) != 0) {
            if (pre_alpha != (std::islower(i) != 0)) {
                return false;
            }
            pre_alpha = true;
        }
        else {
            pre_alpha = false;
        }
    }

    return true;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.isupper()
 *        pystr::isupper("abc") <=> 'abc'.isupper()
 */
bool isupper(const std::string& self)
{
    return (
        std::any_of(self.begin(), self.end(), ::isupper) &&
        std::none_of(self.begin(), self.end(), ::islower)
    );
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.join()
 *        pystr::join("abc", std::vector({"a", "b"})) <=> 'abc'.join(['a', 'b'])
 */
std::string join(const std::string& self, const std::vector<std::string>& strs)
{
    if (strs.empty()) {
        return std::string();
    }

    std::string::size_type size = self.size() * (strs.size() - 1);
    for (const auto& i: strs) {
        size += i.size();
    }

    std::string retval;
    retval.reserve(size);
    for (auto i = strs.cbegin(); i != strs.cend(); ++i) {
        if (i != strs.cbegin()) {
            retval += self;
        }
        retval += *i;
    }
    return retval;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.ljust()
 *        pystr::ljust("abc", 5) <=> 'abc'.ljust(5)
 * @throw ken3::pystr::TypeError: when fillchar is not one character
 * @note  the type of fillchar is not char.
 */
std::string ljust(const std::string& self, index_type width, const std::string& fillchar/*=std::string(" ")*/)
{
    if (fillchar.size() != 1) {
        throw TypeError("must be char, not str");
    }

    if (static_cast<index_type>(self.size()) >= width) {
        return self;
    }

    std::string str(width, fillchar.at(0));
    str.replace(0, self.size(), self);
    return str;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.lower()
 *        pystr::lower("abc") <=> 'abc'.lower()
 */
std::string lower(const std::string& self)
{
    std::string str(self);
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.lstrip()
 *        pystr::lstrip("  abc") <=> '  abc'.lstrip()
 * @note  chars always str, None is not supported.
 */
std::string lstrip(const std::string& self, const std::string& chars/*=std::string(" ")*/)
{
    std::size_t first = 0;
    std::size_t found = self.find_first_of(chars);
    while (found == first) {
        first++;
        found = self.find_first_of(chars, first);
    }

    return std::string(self, first);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.partition()
 *        pystr::partition("abc", "b") <=> 'abc'.partition('b')
 * @throw ken3::pystr::ValueError: when sep is empty
 */
std::vector<std::string> partition(const std::string& self, const std::string& sep)
{
    if (sep.empty()) {
        throw ValueError("empty separator");
    }

    std::vector<std::string> ret(3);

    std::string::size_type pos = self.find(sep);
    if (pos != std::string::npos) {
        ret[0] = self.substr(0, pos);
        ret[1] = self.substr(pos, sep.size());
        ret[2] = self.substr(pos + sep.size());
    }
    else {
        ret[0] = self;
    }

    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.replace()
 *        pystr::replace("abc", "a", "b") <=> 'abc'.replace('a', 'b')
 */
std::string replace(const std::string& self, const std::string& old, const std::string& new_, index_type count/*=None*/)
{
    std::string str = self;
    std::string::size_type pos = 0;
    bool no_count = ((count == None) || (count < 0));
    index_type counter = 0;

    while (pos = str.find(old, pos), pos != std::string::npos) {
        counter++;
        if (!no_count && (counter > count)) {
            break;
        }

        str.replace(pos, old.size(), new_);
        pos += new_.size() + (old.empty() ? 1 : 0);
    }

    return str;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.rfind()
 *        pystr::rfind("abc", "a") <=> 'abc'.rfind('a')
 */
index_type rfind(const std::string& self, const std::string& sub, index_type start/*=None*/, index_type end/*=None*/)
{
    const std::string& s = all_default(start, end) ? self : slice(self, start, end);
    index_type offset_pos = all_default(start, end) ? 0 : offset(self, start, end);

    std::string::size_type pos = s.rfind(sub);
    if (pos != std::string::npos) {
        return static_cast<index_type>(pos) + offset_pos;
    }
    else {
        return -1;
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.rindex()
 *        pystr::rindex("abc", "a") <=> 'abc'.rindex('a')
 * @throw ken3::pystr::ValueError: when sub is not found in self
 */
index_type rindex(const std::string& self, const std::string& sub, index_type start/*=None*/, index_type end/*=None*/)
{
    const std::string& s = all_default(start, end) ? self : slice(self, start, end);
    index_type offset_pos = all_default(start, end) ? 0 : offset(self, start, end);

    std::string::size_type pos = s.rfind(sub);
    if (pos != std::string::npos) {
        return static_cast<index_type>(pos) + offset_pos;
    }
    else {
        throw ValueError("substring not found");
    }
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.rjust()
 *        pystr::rjust("abc", 5) <=> 'abc'.rjust(5)
 * @throw ken3::pystr::TypeError: when fill char is not one character
 * @note  the type of fillchar is not char.
 */
std::string rjust(const std::string& self, index_type width, const std::string& fillchar/*=std::string(" ")*/)
{
    if (fillchar.size() != 1) {
        throw TypeError("must be char, not str");
    }

    if (static_cast<index_type>(self.size()) >= width) {
        return self;
    }

    std::string str(width, fillchar.at(0));
    str.replace(width - self.size(), self.size(), self);
    return str;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.rpartition()
 *        pystr::rpartition("abc", "b") <=> 'abc'.rpartition('b')
 * @throw ken3::pystr::ValueError: when sep is empty
 */
std::vector<std::string> rpartition(const std::string& self, const std::string& sep)
{
    if (sep.empty()) {
        throw ValueError("empty separator");
    }

    std::vector<std::string> ret(3);

    std::string::size_type pos = self.rfind(sep);
    if (pos != std::string::npos) {
        ret[0] = self.substr(0, pos);
        ret[1] = self.substr(pos, sep.size());
        ret[2] = self.substr(pos + sep.size());
    }
    else {
        ret[2] = self;
    }

    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.rsplit()
 *        pystr::rsplit("abc", "b") <=> 'abc'.rsplit('b')
 * @throw ken3::pystr::ValueError: when sep is empty
 * @note  this function corresponds to str.rsplit(sep).
 */
std::vector<std::string> rsplit(const std::string& self, const std::string& sep, index_type maxsplit/*=None*/)
{
    if (sep.empty()) {
        throw ValueError("empty separator");
    }
    if (self.empty()) {
        return std::vector<std::string>(1);
    }

    std::vector<std::string> ret;
    bool no_max = ((maxsplit == None) || (maxsplit < 0));
    index_type counter = 0;
    std::size_t start = self.size();
    std::size_t end = self.rfind(sep, start);
    while (end != std::string::npos) {
        counter++;
        if (!no_max && (counter > maxsplit)) {
            end = std::string::npos;
            break;
        }

        ret.push_back(self.substr(end + sep.size(), start - end - (sep.size() - 1)));
        if (end == 0) {
            break;
        }

        start = end - 1;
        end = self.rfind(sep, start);
    }
    ret.push_back((end == 0) ? std::string()
                             : self.substr(0, start + 1));

    std::reverse(ret.begin(), ret.end());
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.rsplit()
 *        pystr::rsplit("abc") <=> 'abc'.rsplit()
 * @note  this function corresponds to str.rsplit() (without sep).
 */
std::vector<std::string> rsplit(const std::string& self, index_type maxsplit/*=None*/)
{
    if (self.empty()) {
        return std::vector<std::string>();
    }

    std::vector<std::string> ret;
    std::string str = rstrip(self);
    bool no_max = ((maxsplit == None) || (maxsplit < 0));
    index_type counter = 0;
    std::size_t start = str.size();
    std::size_t end = str.rfind(" ", start);
    while (end != std::string::npos) {
        counter++;
        if (!no_max && (counter > maxsplit)) {
            end = std::string::npos;
            break;
        }

        ret.push_back(str.substr(end + 1, start - end));
        if (end == 0) {
            break;
        }

        start = end - 1;
        while ((0 < start) && (start < str.size()) && (str.at(start) == ' ')) {
            start--;
        }
        end = str.rfind(" ", start);
    }
    if (end != 0) {
        ret.push_back(str.substr(0, start + 1));
    }

    std::reverse(ret.begin(), ret.end());
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.rstrip()
 *        pystr::rstrip("abc  ") <=> 'abc  '.rstrip()
 * @note  chars always str, None is not supported.
 */
std::string rstrip(const std::string& self, const std::string& chars/*=std::string(" ")*/)
{
    std::string str(self);
    std::reverse(str.begin(), str.end());
    str = lstrip(str, chars);
    std::reverse(str.begin(), str.end());
    return str;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.split()
 *        pystr::split("abc", "b") <=> 'abc'.split('b')
 * @throw ken3::pystr::ValueError: when sep is empty
 * @note  this function corresponds to str.split(sep).
 */
std::vector<std::string> split(const std::string& self, const std::string& sep, index_type maxsplit/*=None*/)
{
    if (sep.empty()) {
        throw ValueError("empty separator");
    }

    std::vector<std::string> ret;
    bool no_max = ((maxsplit == None) || (maxsplit < 0));
    index_type counter = 0;
    std::size_t start = 0;
    std::size_t end = self.find(sep, start);
    while (end != std::string::npos) {
        counter++;
        if (!no_max && (counter > maxsplit)) {
            break;
        }

        ret.push_back(self.substr(start, end - start));

        start = end + sep.size();
        end = self.find(sep, start);
    }
    ret.push_back(self.substr(start));
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.split()
 *        pystr::split("abc") <=> 'abc'.split()
 * @note  this function corresponds to str.split() (without sep).
 */
std::vector<std::string> split(const std::string& self, index_type maxsplit/*=None*/)
{
    std::vector<std::string> ret;
    std::string str = lstrip(self);
    bool no_max = ((maxsplit == None) || (maxsplit < 0));
    index_type counter = 0;
    std::size_t start = 0;
    std::size_t end = str.find(" ", start);
    while (end != std::string::npos) {
        counter++;
        if (!no_max && (counter > maxsplit)) {
            break;
        }

        ret.push_back(str.substr(start, end - start));

        start = end + 1;
        while ((start < str.size()) && (str.at(start) == ' ')) {
            start++;
        }
        end = str.find(" ", start);
    }
    if (start != str.size()) {
        ret.push_back(str.substr(start));
    }
    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.splitlines()
 *        pystr::splitlines("ab\nc\n") <=> 'ab\nc\n'.splitlines()
 */
std::vector<std::string> splitlines(const std::string& self, bool keepends/*=false*/)
{
    std::vector<std::string> ret;

    std::size_t start = 0;
    while (start < self.size()) {
        std::size_t end_r = self.find("\r", start);
        std::size_t end_n = self.find("\n", start);

        if (end_r == std::string::npos && end_n == std::string::npos) { // find no return code
            ret.push_back(self.substr(start));
            break;
        }
        else if (end_r != std::string::npos && end_n == std::string::npos) { // find \r
            ret.push_back(self.substr(start, end_r - start + (keepends ? 1 : 0)));
            start = end_r + 1;
        }
        else if (end_r == std::string::npos && end_n != std::string::npos) { // find \n
            ret.push_back(self.substr(start, end_n - start + (keepends ? 1 : 0)));
            start = end_n + 1;
        }
        else {
            if (end_r > end_n) { // find \n
                ret.push_back(self.substr(start, end_n - start + (keepends ? 1 : 0)));
                start = end_n + 1;
            }
            else if ((end_r + 1) == end_n) { // find \r\n
                ret.push_back(self.substr(start, end_r - start + (keepends ? 2 : 0)));
                start = end_r + 2;
            }
            else { // find \r
                ret.push_back(self.substr(start, end_r - start + (keepends ? 1 : 0)));
                start = end_r + 1;
            }
        }
    }

    return ret;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.startswith() with str
 *        pystr::startswith("abc", "a") <=> 'abc'.startswith('a')
 */
bool startswith(const std::string& self, const std::string& preffix, index_type start/*=None*/, index_type end/*=None*/)
{
    const std::string& s = all_default(start, end) ? self : slice(self, start, end);

    std::string::size_type pos = s.find(preffix);
    return pos == 0;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.startswith() with tuple
 *        pystr::startswith("abc", std::vector({"a", "b"})) <=> 'abc'.startswith(('a', 'b'))
 */
bool startswith(const std::string& self, const std::vector<std::string>& preffix, index_type start/*=None*/, index_type end/*=None*/)
{
    const std::string& s = all_default(start, end) ? self : slice(self, start, end);

    for (const auto& i: preffix) {
        if (startswith(s, i)) {
            return true;
        }
    }

    return false;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.strip()
 *        pystr::strip(" abc ") <=> ' abc '.strip()
 * @note  chars always str, None is not supported.
 */
std::string strip(const std::string& self, const std::string& chars/*=std::string(" ")*/)
{
    return rstrip(lstrip(self, chars), chars);
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.swapcase()
 *        pystr::swapcase("abc") <=> 'abc'.swapcase()
 */
std::string swapcase(const std::string& self)
{
    std::string str(self);

    for (auto& i: str) {
        if (std::isalpha(i) != 0) {
            if (std::islower(i) != 0) {
                i = ::toupper(i);
            }
            else if (std::isupper(i) != 0) {
                i = ::tolower(i);
            }
        }
    }

    return str;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.title()
 *        pystr::title("abc") <=> 'abc'.title()
 */
std::string title(const std::string& self)
{
    std::string str(self);

    bool pre_alpha = false;
    for (auto& i: str) {
        if (std::isalpha(i) != 0) {
            if (pre_alpha) {
                i = ::tolower(i);
            }
            else {
                i = ::toupper(i);
            }
            pre_alpha = true;
        }
        else {
            pre_alpha = false;
        }
    }

    return str;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.upper()
 *        pystr::upper("abc") <=> 'abc'.upper()
 */
std::string upper(const std::string& self)
{
    std::string str(self);
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}
/////////////////////////////////////////////////////////////////////////////

/**
 * @brief str.zfill()
 *        pystr::zfill("abc", 5) <=> 'abc'.zfill(5)
 */
std::string zfill(const std::string& self, index_type width)
{
    if (startswith(self, "-")) {
        return std::string("-") + rjust(self.substr(1), width - 1, "0");
    }
    else {
        return rjust(self, width, "0");
    }
}
/////////////////////////////////////////////////////////////////////////////

} // namespace pystr {
} // namespace ken3 {
