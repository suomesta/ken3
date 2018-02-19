# -*- coding: utf-8 -*-

from collections import OrderedDict

test_map = OrderedDict()
test_map['add()'] = (
    (lambda: 'a'.__add__('a'), 'add("a", "a")'),
    (lambda: 'aAa'.__add__('a'), 'add("aAa", "a")'),
    (lambda: 'AAA'.__add__('a'), 'add("AAA", "a")'),
    (lambda: 'a'.__add__(''), 'add("a", "")'),
    (lambda: ''.__add__('a'), 'add("", "a")'),
    (lambda: ''.__add__(''), 'add("", "")'),
)
test_map['contains()'] = (
    (lambda: 'a'.__contains__('a'), 'contains("a", "a")'),
    (lambda: 'aAa'.__contains__('a'), 'contains("aAa", "a")'),
    (lambda: 'AAA'.__contains__('a'), 'contains("AAA", "a")'),
    (lambda: 'a'.__contains__(''), 'contains("a", "")'),
    (lambda: ''.__contains__('a'), 'contains("", "a")'),
    (lambda: ''.__contains__(''), 'contains("", "")'),
)
test_map['eq()'] = (
    (lambda: 'a'.__eq__('a'), 'eq("a", "a")'),
    (lambda: 'A'.__eq__('a'), 'eq("A", "a")'),
    (lambda: 'AAA'.__eq__('a'), 'eq("AAA", "a")'),
    (lambda: 'a'.__eq__(''), 'eq("a", "")'),
    (lambda: ''.__eq__('a'), 'eq("", "a")'),
    (lambda: ''.__eq__(''), 'eq("", "")'),
)
test_map['ge()'] = (
    (lambda: 'a'.__ge__('a'), 'ge("a", "a")'),
    (lambda: 'A'.__ge__('a'), 'ge("A", "a")'),
    (lambda: 'a'.__ge__('A'), 'ge("a", "A")'),
    (lambda: 'AAA'.__ge__('a'), 'ge("AAA", "a")'),
    (lambda: 'a'.__ge__(''), 'ge("a", "")'),
    (lambda: ''.__ge__('a'), 'ge("", "a")'),
    (lambda: ''.__ge__(''), 'ge("", "")'),
)
test_map['getitem()'] = (
    (lambda: 'abc'.__getitem__(0), 'getitem("abc", 0)'),
    (lambda: 'abc'.__getitem__(1), 'getitem("abc", 1)'),
    (lambda: 'abc'.__getitem__(2), 'getitem("abc", 2)'),
    (lambda: 'abc'.__getitem__(-3), 'getitem("abc", -3)'),
    (lambda: 'abc'.__getitem__(-2), 'getitem("abc", -2)'),
    (lambda: 'abc'.__getitem__(-1), 'getitem("abc", -1)'),
    (lambda: 'abc'.__getitem__(10), 'getitem("abc", 10)'),
    (lambda: 'abc'.__getitem__(-10), 'getitem("abc", -10)'),
    (lambda: ''.__getitem__(0), 'getitem("", 0)'),
    (lambda: ''.__getitem__(-1), 'getitem("", -1)'),
)
test_map['slice()'] = (
    (lambda: 'abcdefgh'.__getitem__(slice(0)), 'slice("abcdefgh", None, 0)'),
    (lambda: 'abcdefgh'.__getitem__(slice(1, 0)), 'slice("abcdefgh", 1, 0)'),
    (lambda: 'abcdefgh'.__getitem__(slice(1, 100)), 'slice("abcdefgh", 1, 100)'),
    (lambda: 'abcdefgh'.__getitem__(slice(100, 1)), 'slice("abcdefgh", 100, 1)'),
    (lambda: 'abcdefgh'.__getitem__(slice(2, 2)), 'slice("abcdefgh", 2, 2)'),
    (lambda: 'abcdefgh'.__getitem__(slice(200, 100)), 'slice("abcdefgh", 200, 100)'),
    (lambda: 'abcdefgh'.__getitem__(slice(1, -1)), 'slice("abcdefgh", 1, -1)'),
    (lambda: 'abcdefgh'.__getitem__(slice(-100, 100)), 'slice("abcdefgh", -100, 100)'),
    (lambda: 'abcdefgh'.__getitem__(slice(1, -100)), 'slice("abcdefgh", 1, -100)'),
    (lambda: 'abcdefgh'.__getitem__(slice(0, None)), 'slice("abcdefgh", 0, None)'),
    (lambda: 'abcdefgh'.__getitem__(slice(None, None)), 'slice("abcdefgh", None, None)'),
    (lambda: 'abcdefgh'.__getitem__(slice(None, None, 0)), 'slice("abcdefgh", None, None, 0)'),
    (lambda: 'abcdefgh'.__getitem__(slice(None, None, 2)), 'slice("abcdefgh", None, None, 2)'),
    (lambda: 'abcdefgh'.__getitem__(slice(1, 0, 2)), 'slice("abcdefgh", 1, 0, 2)'),
    (lambda: 'abcdefgh'.__getitem__(slice(1, 100, 2)), 'slice("abcdefgh", 1, 100, 2)'),
    (lambda: 'abcdefgh'.__getitem__(slice(100, 1, 2)), 'slice("abcdefgh", 100, 1, 2)'),
    (lambda: 'abcdefgh'.__getitem__(slice(2, 2, 2)), 'slice("abcdefgh", 2, 2, 2)'),
    (lambda: 'abcdefgh'.__getitem__(slice(200, 100, 2)), 'slice("abcdefgh", 200, 100, 2)'),
    (lambda: 'abcdefgh'.__getitem__(slice(1, -1, 2)), 'slice("abcdefgh", 1, -1, 2)'),
    (lambda: 'abcdefgh'.__getitem__(slice(-100, 100, 2)), 'slice("abcdefgh", -100, 100, 2)'),
    (lambda: 'abcdefgh'.__getitem__(slice(1, -100, 2)), 'slice("abcdefgh", 1, -100, 2)'),
    (lambda: 'abcdefgh'.__getitem__(slice(0, None, 2)), 'slice("abcdefgh", 0, None, 2)'),
    (lambda: 'abcdefgh'.__getitem__(slice(None, None, -1)), 'slice("abcdefgh", None, None, -1)'),
    (lambda: 'abcdefgh'.__getitem__(slice(1, 0, -1)), 'slice("abcdefgh", 1, 0, -1)'),
    (lambda: 'abcdefgh'.__getitem__(slice(1, 100, -1)), 'slice("abcdefgh", 1, 100, -1)'),
    (lambda: 'abcdefgh'.__getitem__(slice(100, 1, -1)), 'slice("abcdefgh", 100, 1, -1)'),
    (lambda: 'abcdefgh'.__getitem__(slice(2, 2, -1)), 'slice("abcdefgh", 2, 2, -1)'),
    (lambda: 'abcdefgh'.__getitem__(slice(200, 100, -1)), 'slice("abcdefgh", 200, 100, -1)'),
    (lambda: 'abcdefgh'.__getitem__(slice(1, -1, -1)), 'slice("abcdefgh", 1, -1, -1)'),
    (lambda: 'abcdefgh'.__getitem__(slice(-100, 100, -1)), 'slice("abcdefgh", -100, 100, -1)'),
    (lambda: 'abcdefgh'.__getitem__(slice(1, -100, -1)), 'slice("abcdefgh", 1, -100, -1)'),
    (lambda: 'abcdefgh'.__getitem__(slice(0, None, -1)), 'slice("abcdefgh", 0, None, -1)'),
    (lambda: 'abcdefgh'.__getitem__(slice(None, None, None)), 'slice("abcdefgh", None, None, None)'),
)
test_map['gt()'] = (
    (lambda: 'a'.__gt__('a'), 'gt("a", "a")'),
    (lambda: 'A'.__gt__('a'), 'gt("A", "a")'),
    (lambda: 'a'.__gt__('A'), 'gt("a", "A")'),
    (lambda: 'AAA'.__gt__('a'), 'gt("AAA", "a")'),
    (lambda: 'a'.__gt__(''), 'gt("a", "")'),
    (lambda: ''.__gt__('a'), 'gt("", "a")'),
    (lambda: ''.__gt__(''), 'gt("", "")'),
)
test_map['le()'] = (
    (lambda: 'a'.__le__('a'), 'le("a", "a")'),
    (lambda: 'A'.__le__('a'), 'le("A", "a")'),
    (lambda: 'a'.__le__('A'), 'le("a", "A")'),
    (lambda: 'AAA'.__le__('a'), 'le("AAA", "a")'),
    (lambda: 'a'.__le__(''), 'le("a", "")'),
    (lambda: ''.__le__('a'), 'le("", "a")'),
    (lambda: ''.__le__(''), 'le("", "")'),
)
test_map['len()'] = (
    (lambda: 'a'.__len__(), 'len("a")'),
    (lambda: 'AAA'.__len__(), 'len("AAA")'),
    (lambda: ''.__len__(), 'len("")'),
)
test_map['lt()'] = (
    (lambda: 'a'.__lt__('a'), 'lt("a", "a")'),
    (lambda: 'A'.__lt__('a'), 'lt("A", "a")'),
    (lambda: 'a'.__lt__('A'), 'lt("a", "A")'),
    (lambda: 'AAA'.__lt__('a'), 'lt("AAA", "a")'),
    (lambda: 'a'.__lt__(''), 'lt("a", "")'),
    (lambda: ''.__lt__('a'), 'lt("", "a")'),
    (lambda: ''.__lt__(''), 'lt("", "")'),
)
test_map['mul()'] = (
    (lambda: 'a'.__mul__(3), 'mul("a", 3)'),
    (lambda: 'abc'.__mul__(3), 'mul("abc", 3)'),
    (lambda: ''.__mul__(10), 'mul("", 10)'),
    (lambda: 'abc'.__mul__(0), 'mul("abc", 0)'),
    (lambda: 'abc'.__mul__(-1), 'mul("abc", -1)'),
)
test_map['repr()'] = (
    (lambda: ''.join(chr(i) for i in range(128)).__repr__(), 'repr(str7F(128))'),
    (lambda: "abc'abc".__repr__(), 'repr("abc\'abc")'),
    (lambda: "abc\"'abc".__repr__(), 'repr("abc\\"\'abc")'),
    (lambda: 'abc'.__repr__(), 'repr("abc")'),
    (lambda: '\r\n\t'.__repr__(), 'repr("\\r\\n\\t")'),
    (lambda: ''.__repr__(), 'repr("")'),
)
test_map['ne()'] = (
    (lambda: 'a'.__ne__('a'), 'ne("a", "a")'),
    (lambda: 'a'.__ne__('AAA'), 'ne("a", "AAA")'),
    (lambda: 'AAA'.__ne__('a'), 'ne("AAA", "a")'),
    (lambda: 'a'.__ne__(''), 'ne("a", "")'),
    (lambda: ''.__ne__('a'), 'ne("", "a")'),
    (lambda: ''.__ne__(''), 'ne("", "")'),
)
test_map['capitalize()'] = (
    (lambda: 'a'.capitalize(), 'capitalize("a")'),
    (lambda: 'a abc'.capitalize(), 'capitalize("a abc")'),
    (lambda: 'A ABC'.capitalize(), 'capitalize("A ABC")'),
    (lambda: 'A Abc'.capitalize(), 'capitalize("A Abc")'),
    (lambda: 'abc'.capitalize(), 'capitalize("abc")'),
    (lambda: 'ABC'.capitalize(), 'capitalize("ABC")'),
    (lambda: 'Abc'.capitalize(), 'capitalize("Abc")'),
    (lambda: '98'.capitalize(), 'capitalize("98")'),
    (lambda: '%$'.capitalize(), 'capitalize("%$")'),
    (lambda: ''.capitalize(), 'capitalize("")'),
)
test_map['center()'] = (
    (lambda: 'a'.center(1), 'center("a", 1)'),
    (lambda: 'a'.center(2), 'center("a", 2)'),
    (lambda: 'a'.center(3), 'center("a", 3)'),
    (lambda: 'a'.center(4), 'center("a", 4)'),
    (lambda: 'aa'.center(2), 'center("aa", 2)'),
    (lambda: 'aa'.center(3), 'center("aa", 3)'),
    (lambda: 'aa'.center(4), 'center("aa", 4)'),
    (lambda: 'aa'.center(5), 'center("aa", 5)'),
    (lambda: 'A A '.center(9), 'center("A A ", 9)'),
    (lambda: 'A A '.center(10), 'center("A A ", 10)'),
    (lambda: 'A A '.center(11), 'center("A A ", 11)'),
    (lambda: 'A A '.center(15), 'center("A A ", 15)'),
    (lambda: 'a'.center(0), 'center("a", 0)'),
    (lambda: 'a'.center(-1), 'center("a", -1)'),
    (lambda: 'a'.center(2, '@'), 'center("a", 2, "@")'),
    (lambda: 'abc'.center(10, '@'), 'center("abc", 10, "@")'),
    (lambda: 'a'.center(1, '@@'), 'center("a", 1, "@@")'),
    (lambda: 'a'.center(1, ''), 'center("a", 1, "")'),
    (lambda: ''.center(2), 'center("", 2)'),
)
test_map['count()'] = (
    (lambda: 'a'.count('a'), 'count("a", "a")'),
    (lambda: 'abc'.count('a'), 'count("abc", "a")'),
    (lambda: 'abcab'.count('ab'), 'count("abcab", "ab")'),
    (lambda: ''.count('a'), 'count("", "a")'),
    (lambda: 'a'.count(''), 'count("a", "")'),
    (lambda: ''.count(''), 'count("", "")'),
    (lambda: 'abcab'.count('a', 1, 3), 'count("abcab", "a", 1, 3)'),
    (lambda: 'abcab'.count('a', 1, 4), 'count("abcab", "a", 1, 4)'),
    (lambda: 'abcab'.count('ab', 1, 3), 'count("abcab", "ab", 1, 3)'),
    (lambda: 'abcab'.count('ab', 1, 4), 'count("abcab", "ab", 1, 4)'),
    (lambda: 'abcab'.count('a', 1), 'count("abcab", "a", 1)'),
    (lambda: 'abcab'.count('a', 4), 'count("abcab", "a", 4)'),
    (lambda: 'abcab'.count('', 1, 3), 'count("abcab", "", 1, 3)'),
    (lambda: 'abcab'.count('ab', 999), 'count("abcab", "ab", 999)'),
    (lambda: 'abcab'.count('ab', 1, 999), 'count("abcab", "ab", 1, 999)'),
)
test_map['endswith() with single suffix'] = (
    (lambda: 'a'.endswith('a'), 'endswith("a", "a")'),
    (lambda: 'abc'.endswith('a'), 'endswith("abc", "a")'),
    (lambda: 'abc'.endswith('c'), 'endswith("abc", "c")'),
    (lambda: 'abcab'.endswith('ab'), 'endswith("abcab", "ab")'),
    (lambda: 'abcab'.endswith('ac'), 'endswith("abcab", "ac")'),
    (lambda: ''.endswith('a'), 'endswith("", "a")'),
    (lambda: 'a'.endswith(''), 'endswith("a", "")'),
    (lambda: ''.endswith(''), 'endswith("", "")'),
    (lambda: 'abcab'.endswith('a', 1, 3), 'endswith("abcab", "a", 1, 3)'),
    (lambda: 'abcab'.endswith('a', 1, 4), 'endswith("abcab", "a", 1, 4)'),
    (lambda: 'abcab'.endswith('ab', 1, 3), 'endswith("abcab", "ab", 1, 3)'),
    (lambda: 'abcab'.endswith('ab', 1, 4), 'endswith("abcab", "ab", 1, 4)'),
    (lambda: 'abcab'.endswith('a', 1), 'endswith("abcab", "a", 1)'),
    (lambda: 'abcab'.endswith('a', 4), 'endswith("abcab", "a", 4)'),
    (lambda: 'abcab'.endswith('', 1, 3), 'endswith("abcab", "", 1, 3)'),
    (lambda: 'abcab'.endswith('ab', 999), 'endswith("abcab", "ab", 999)'),
)
test_map['endswith() with multiple suffixes'] = (
    (lambda: 'abc'.endswith(('a', 'b', 'c')), 'endswith("abc", (std::vector<std::string>{"a", "b", "c"}))'),
    (lambda: 'acb'.endswith(('a', 'b', 'c')), 'endswith("acb", (std::vector<std::string>{"a", "b", "c"}))'),
    (lambda: 'ddd'.endswith(('a', 'b', 'c')), 'endswith("ddd", (std::vector<std::string>{"a", "b", "c"}))'),
    (lambda: 'abc'.endswith(('ab', 'bc')), 'endswith("abc", (std::vector<std::string>{"ab", "bc"}))'),
    (lambda: 'acb'.endswith(('ab', 'bc')), 'endswith("acb", (std::vector<std::string>{"ab", "bc"}))'),
    (lambda: 'abc'.endswith(tuple()), 'endswith("abc", (std::vector<std::string>{}))'),
)
test_map['expandtabs()'] = (
    (lambda: 'a'.expandtabs(), 'expandtabs("a")'),
    (lambda: 'a\t'.expandtabs(), 'expandtabs("a\\t")'),
    (lambda: '\ta'.expandtabs(), 'expandtabs("\\ta")'),
    (lambda: '\ta\t'.expandtabs(), 'expandtabs("\\ta\\t")'),
    (lambda: '\t\t\t'.expandtabs(), 'expandtabs("\\t\\t\\t")'),
    (lambda: '\ta  a\t'.expandtabs(), 'expandtabs("\\ta  a\\t")'),
    (lambda: '\ta\na\t'.expandtabs(), 'expandtabs("\\ta\\na\\t")'),
    (lambda: 'a'.expandtabs(4), 'expandtabs("a", 4)'),
    (lambda: 'a\t'.expandtabs(4), 'expandtabs("a\\t", 4)'),
    (lambda: '\ta'.expandtabs(4), 'expandtabs("\\ta", 4)'),
    (lambda: '\ta\t'.expandtabs(4), 'expandtabs("\\ta\\t", 4)'),
    (lambda: '\t\t\t'.expandtabs(4), 'expandtabs("\\t\\t\\t", 4)'),
    (lambda: '\ta  a\t'.expandtabs(4), 'expandtabs("\\ta  a\\t", 4)'),
    (lambda: '\ta\na\t'.expandtabs(4), 'expandtabs("\\ta\\na\\t", 4)'),
    (lambda: 'a\t'.expandtabs(1), 'expandtabs("a\\t", 1)'),
    (lambda: 'a\t'.expandtabs(0), 'expandtabs("a\\t", 0)'),
    (lambda: 'a\t'.expandtabs(-1), 'expandtabs("a\\t", -1)'),
    (lambda: ''.expandtabs(), 'expandtabs("")'),
)
test_map['find()'] = (
    (lambda: 'abc'.find('a'), 'find("abc", "a")'),
    (lambda: 'abc'.find('d'), 'find("abc", "d")'),
    (lambda: 'abc'.find('bc'), 'find("abc", "bc")'),
    (lambda: 'abc'.find('ac'), 'find("abc", "ac")'),
    (lambda: 'abcabc'.find('abc'), 'find("abcabc", "abc")'),
    (lambda: 'abcab'.find('a', 1, 3), 'find("abcab", "a", 1, 3)'),
    (lambda: 'abcab'.find('a', 1, 4), 'find("abcab", "a", 1, 4)'),
    (lambda: 'abcab'.find('ab', 1, 3), 'find("abcab", "ab", 1, 3)'),
    (lambda: 'abcab'.find('ab', 1, 4), 'find("abcab", "ab", 1, 4)'),
    (lambda: 'abcab'.find('a', 1), 'find("abcab", "a", 1)'),
    (lambda: 'abcab'.find('a', 4), 'find("abcab", "a", 4)'),
    (lambda: 'abcab'.find('', 1, 3), 'find("abcab", "", 1, 3)'),
    (lambda: 'abcab'.find('ab', 999), 'find("abcab", "ab", 999)'),
    (lambda: 'abcab'.find('ab', 1, 999), 'find("abcab", "ab", 1, 999)'),
    (lambda: ''.find('a'), 'find("", "a")'),
    (lambda: 'a'.find(''), 'find("a", "")'),
    (lambda: ''.find(''), 'find("", "")'),
)
test_map['index()'] = (
    (lambda: 'abc'.index('a'), 'index("abc", "a")'),
    (lambda: 'abc'.index('d'), 'index("abc", "d")'),
    (lambda: 'abc'.index('bc'), 'index("abc", "bc")'),
    (lambda: 'abc'.index('ac'), 'index("abc", "ac")'),
    (lambda: 'abcabc'.index('abc'), 'index("abcabc", "abc")'),
    (lambda: 'abcab'.index('a', 1, 3), 'index("abcab", "a", 1, 3)'),
    (lambda: 'abcab'.index('a', 1, 4), 'index("abcab", "a", 1, 4)'),
    (lambda: 'abcab'.index('ab', 1, 3), 'index("abcab", "ab", 1, 3)'),
    (lambda: 'abcab'.index('ab', 1, 4), 'index("abcab", "ab", 1, 4)'),
    (lambda: 'abcab'.index('a', 1), 'index("abcab", "a", 1)'),
    (lambda: 'abcab'.index('a', 4), 'index("abcab", "a", 4)'),
    (lambda: 'abcab'.index('', 1, 3), 'index("abcab", "", 1, 3)'),
    (lambda: 'abcab'.index('ab', 999), 'index("abcab", "ab", 999)'),
    (lambda: 'abcab'.index('ab', 1, 999), 'index("abcab", "ab", 1, 999)'),
    (lambda: ''.index('a'), 'index("", "a")'),
    (lambda: 'a'.index(''), 'index("a", "")'),
    (lambda: ''.index(''), 'index("", "")'),
)
test_map['isalnum()'] = (
    (lambda: 'a'.isalnum(), 'isalnum("a")'),
    (lambda: 'A'.isalnum(), 'isalnum("A")'),
    (lambda: 'abc'.isalnum(), 'isalnum("abc")'),
    (lambda: 'aBc'.isalnum(), 'isalnum("aBc")'),
    (lambda: 'a c'.isalnum(), 'isalnum("a c")'),
    (lambda: '3'.isalnum(), 'isalnum("3")'),
    (lambda: '3F'.isalnum(), 'isalnum("3F")'),
    (lambda: ''.isalnum(), 'isalnum("")'),
    (lambda: '@'.isalnum(), 'isalnum("@")'),
    (lambda: ' '.isalnum(), 'isalnum(" ")'),
    (lambda: '3F@'.isalnum(), 'isalnum("3F@")'),
    (lambda: '\n'.isalnum(), 'isalnum("\\n")'),
)
test_map['isalpha()'] = (
    (lambda: 'a'.isalpha(), 'isalpha("a")'),
    (lambda: 'A'.isalpha(), 'isalpha("A")'),
    (lambda: 'abc'.isalpha(), 'isalpha("abc")'),
    (lambda: 'aBc'.isalpha(), 'isalpha("aBc")'),
    (lambda: 'a c'.isalpha(), 'isalpha("a c")'),
    (lambda: '3'.isalpha(), 'isalpha("3")'),
    (lambda: '3F'.isalpha(), 'isalpha("3F")'),
    (lambda: ''.isalpha(), 'isalpha("")'),
    (lambda: '@'.isalpha(), 'isalpha("@")'),
    (lambda: ' '.isalpha(), 'isalpha(" ")'),
    (lambda: '3F@'.isalpha(), 'isalpha("3F@")'),
    (lambda: '\n'.isalpha(), 'isalpha("\\n")'),
)
test_map['isdigit()'] = (
    (lambda: 'a'.isdigit(), 'isdigit("a")'),
    (lambda: 'A'.isdigit(), 'isdigit("A")'),
    (lambda: 'abc'.isdigit(), 'isdigit("abc")'),
    (lambda: 'aBc'.isdigit(), 'isdigit("aBc")'),
    (lambda: 'a c'.isdigit(), 'isdigit("a c")'),
    (lambda: '3'.isdigit(), 'isdigit("3")'),
    (lambda: '3F'.isdigit(), 'isdigit("3F")'),
    (lambda: ''.isdigit(), 'isdigit("")'),
    (lambda: '@'.isdigit(), 'isdigit("@")'),
    (lambda: ' '.isdigit(), 'isdigit(" ")'),
    (lambda: '3F@'.isdigit(), 'isdigit("3F@")'),
    (lambda: '\n'.isdigit(), 'isdigit("\\n")'),
)
test_map['islower()'] = (
    (lambda: 'a'.islower(), 'islower("a")'),
    (lambda: 'A'.islower(), 'islower("A")'),
    (lambda: 'abc'.islower(), 'islower("abc")'),
    (lambda: 'aBc'.islower(), 'islower("aBc")'),
    (lambda: 'a c'.islower(), 'islower("a c")'),
    (lambda: '3'.islower(), 'islower("3")'),
    (lambda: '3F'.islower(), 'islower("3F")'),
    (lambda: ''.islower(), 'islower("")'),
    (lambda: '@'.islower(), 'islower("@")'),
    (lambda: ' '.islower(), 'islower(" ")'),
    (lambda: '3F@'.islower(), 'islower("3F@")'),
    (lambda: '\n'.islower(), 'islower("\\n")'),
)
test_map['isspace()'] = (
    (lambda: 'a'.isspace(), 'isspace("a")'),
    (lambda: 'A'.isspace(), 'isspace("A")'),
    (lambda: 'abc'.isspace(), 'isspace("abc")'),
    (lambda: 'aBc'.isspace(), 'isspace("aBc")'),
    (lambda: 'a c'.isspace(), 'isspace("a c")'),
    (lambda: '3'.isspace(), 'isspace("3")'),
    (lambda: '3F'.isspace(), 'isspace("3F")'),
    (lambda: ''.isspace(), 'isspace("")'),
    (lambda: '@'.isspace(), 'isspace("@")'),
    (lambda: ' '.isspace(), 'isspace(" ")'),
    (lambda: '3F@'.isspace(), 'isspace("3F@")'),
    (lambda: '\n'.isspace(), 'isspace("\\n")'),
)
test_map['istitle()'] = (
    (lambda: 'a'.istitle(), 'istitle("a")'),
    (lambda: 'aaa'.istitle(), 'istitle("aaa")'),
    (lambda: 'aAa'.istitle(), 'istitle("aAa")'),
    (lambda: 'Aaa'.istitle(), 'istitle("Aaa")'),
    (lambda: 'aAa AAA aaA'.istitle(), 'istitle("aAa AAA aaA")'),
    (lambda: 'AAa AAA AaA'.istitle(), 'istitle("AAa AAA AaA")'),
    (lambda: 'Aaa Bbb Ccc'.istitle(), 'istitle("Aaa Bbb Ccc")'),
    (lambda: 'aAa\naaA'.istitle(), 'istitle("aAa\\naaA")'),
    (lambda: 'aAa0aaA'.istitle(), 'istitle("aAa0aaA")'),
    (lambda: 'aAa-aaA'.istitle(), 'istitle("aAa-aaA")'),
    (lambda: 'aAa/aaA'.istitle(), 'istitle("aAa/aaA")'),
    (lambda: 'aAa\'aaA'.istitle(), 'istitle("aAa\'aaA")'),
    (lambda: 'AAa-AaA'.istitle(), 'istitle("AAa-AaA")'),
    (lambda: 'Aaa-Abc'.istitle(), 'istitle("Aaa-Abc")'),
    (lambda: ' aA a '.istitle(), 'istitle(" aA a ")'),
    (lambda: ''.istitle(), 'istitle("")'),
)
test_map['isupper()'] = (
    (lambda: 'a'.isupper(), 'isupper("a")'),
    (lambda: 'A'.isupper(), 'isupper("A")'),
    (lambda: 'abc'.isupper(), 'isupper("abc")'),
    (lambda: 'aBc'.isupper(), 'isupper("aBc")'),
    (lambda: 'a c'.isupper(), 'isupper("a c")'),
    (lambda: '3'.isupper(), 'isupper("3")'),
    (lambda: '3F'.isupper(), 'isupper("3F")'),
    (lambda: ''.isupper(), 'isupper("")'),
    (lambda: '@'.isupper(), 'isupper("@")'),
    (lambda: ' '.isupper(), 'isupper(" ")'),
    (lambda: '3F@'.isupper(), 'isupper("3F@")'),
    (lambda: '\n'.isupper(), 'isupper("\\n")'),
)
test_map['join()'] = (
    (lambda: ''.join([]), 'join("", (std::vector<std::string>{}))'),
    (lambda: 'a'.join([]), 'join("a", (std::vector<std::string>{}))'),
    (lambda: ''.join(['a', 'b', 'c']), 'join("", (std::vector<std::string>{"a", "b", "c"}))'),
    (lambda: 'a'.join(['a', 'b', 'c']), 'join("a", (std::vector<std::string>{"a", "b", "c"}))'),
    (lambda: ''.join(['ab', 'bc']), 'join("", (std::vector<std::string>{"ab", "bc"}))'),
    (lambda: 'a'.join(['ab', 'bc']), 'join("a", (std::vector<std::string>{"ab", "bc"}))'),
)
test_map['ljust()'] = (
    (lambda: 'a'.ljust(1), 'ljust("a", 1)'),
    (lambda: 'a'.ljust(2), 'ljust("a", 2)'),
    (lambda: 'a'.ljust(3), 'ljust("a", 3)'),
    (lambda: 'a'.ljust(4), 'ljust("a", 4)'),
    (lambda: 'aa'.ljust(2), 'ljust("aa", 2)'),
    (lambda: 'aa'.ljust(3), 'ljust("aa", 3)'),
    (lambda: 'aa'.ljust(4), 'ljust("aa", 4)'),
    (lambda: 'aa'.ljust(5), 'ljust("aa", 5)'),
    (lambda: 'A A '.ljust(9), 'ljust("A A ", 9)'),
    (lambda: 'A A '.ljust(10), 'ljust("A A ", 10)'),
    (lambda: 'A A '.ljust(11), 'ljust("A A ", 11)'),
    (lambda: 'A A '.ljust(15), 'ljust("A A ", 15)'),
    (lambda: 'a'.ljust(0), 'ljust("a", 0)'),
    (lambda: 'a'.ljust(-1), 'ljust("a", -1)'),
    (lambda: 'a'.ljust(2, '@'), 'ljust("a", 2, "@")'),
    (lambda: 'abc'.ljust(10, '@'), 'ljust("abc", 10, "@")'),
    (lambda: 'a'.ljust(1, '@@'), 'ljust("a", 1, "@@")'),
    (lambda: 'a'.ljust(1, ''), 'ljust("a", 1, "")'),
    (lambda: ''.ljust(0), 'ljust("", 0)'),
    (lambda: ''.ljust(1), 'ljust("", 1)'),
    (lambda: ''.ljust(2), 'ljust("", 2)'),
)
test_map['lower()'] = (
    (lambda: 'a'.lower(), 'lower("a")'),
    (lambda: 'Ab'.lower(), 'lower("Ab")'),
    (lambda: 'abc'.lower(), 'lower("abc")'),
    (lambda: 'aBc'.lower(), 'lower("aBc")'),
    (lambda: 'a c'.lower(), 'lower("a c")'),
    (lambda: '3'.lower(), 'lower("3")'),
    (lambda: '3F'.lower(), 'lower("3F")'),
    (lambda: ''.lower(), 'lower("")'),
    (lambda: '@'.lower(), 'lower("@")'),
    (lambda: ' '.lower(), 'lower(" ")'),
    (lambda: '3F@'.lower(), 'lower("3F@")'),
    (lambda: '\n'.lower(), 'lower("\\n")'),
)
test_map['lstrip()'] = (
    (lambda: 'ab ab '.lstrip('a'), 'lstrip("ab ab ", "a")'),
    (lambda: 'ab ab '.lstrip('ab'), 'lstrip("ab ab ", "ab")'),
    (lambda: 'ab ab '.lstrip('ba'), 'lstrip("ab ab ", "ba")'),
    (lambda: ' ab ab'.lstrip('a'), 'lstrip(" ab ab", "a")'),
    (lambda: ' ab ab'.lstrip('ab'), 'lstrip(" ab ab", "ab")'),
    (lambda: ' ab ab'.lstrip('ba'), 'lstrip(" ab ab", "ba")'),
    (lambda: ' ab ab '.lstrip(), 'lstrip(" ab ab ")'),
    (lambda: ' ab ab '.lstrip(' '), 'lstrip(" ab ab ", " ")'),
    (lambda: ' ab ab '.lstrip(''), 'lstrip(" ab ab ", "")'),
    (lambda: ''.lstrip('a'), 'lstrip("", "a")'),
    (lambda: 'a'.lstrip(''), 'lstrip("a", "")'),
    (lambda: ''.lstrip(''), 'lstrip("", "")'),
)
test_map['partition()'] = (
    (lambda: 'abc'.partition('a'), 'partition("abc", "a")'),
    (lambda: 'abc'.partition('b'), 'partition("abc", "b")'),
    (lambda: 'abc'.partition('c'), 'partition("abc", "c")'),
    (lambda: 'abc'.partition('d'), 'partition("abc", "d")'),
    (lambda: 'ab ab '.partition('a'), 'partition("ab ab ", "a")'),
    (lambda: 'ab ab '.partition('b'), 'partition("ab ab ", "b")'),
    (lambda: 'ab ab '.partition('ab'), 'partition("ab ab ", "ab")'),
    (lambda: 'ab ab '.partition('ba'), 'partition("ab ab ", "ba")'),
    (lambda: 'ab ab '.partition('b a'), 'partition("ab ab ", "b a")'),
    (lambda: ' ab ab '.partition(' '), 'partition(" ab ab ", " ")'),
    (lambda: ' ab ab '.partition(''), 'partition(" ab ab ", "")'),
    (lambda: ''.partition('a'), 'partition("", "a")'),
    (lambda: ''.partition(''), 'partition("", "")'),
)
test_map['replace()'] = (
    (lambda: 'abc'.replace('b', 'a'), 'replace("abc", "b", "a")'),
    (lambda: 'abc'.replace('d', 'a'), 'replace("abc", "d", "a")'),
    (lambda: 'abc'.replace('bc', 'dd'), 'replace("abc", "bc", "dd")'),
    (lambda: 'abc'.replace('cb', 'dd'), 'replace("abc", "cb", "dd")'),
    (lambda: 'abc'.replace('bc', 'd'), 'replace("abc", "bc", "d")'),
    (lambda: 'abc'.replace('cb', 'd'), 'replace("abc", "cb", "d")'),
    (lambda: 'abc'.replace('', 'a'), 'replace("abc", "", "a")'),
    (lambda: 'abc'.replace('b', ''), 'replace("abc", "b", "")'),
    (lambda: 'abc'.replace('', ''), 'replace("abc", "", "")'),
    (lambda: ''.replace('', 'a'), 'replace("", "", "a")'),
    (lambda: ''.replace('b', ''), 'replace("", "b", "")'),
    (lambda: ''.replace('', ''), 'replace("", "", "")'),
    (lambda: 'abcabcabc'.replace('bc', 'dd', 4), 'replace("abcabcabc", "bc", "dd", 4)'),
    (lambda: 'abcabcabc'.replace('bc', 'dd', 3), 'replace("abcabcabc", "bc", "dd", 3)'),
    (lambda: 'abcabcabc'.replace('bc', 'dd', 2), 'replace("abcabcabc", "bc", "dd", 2)'),
    (lambda: 'abcabcabc'.replace('bc', 'dd', 1), 'replace("abcabcabc", "bc", "dd", 1)'),
    (lambda: 'abcabcabc'.replace('bc', 'dd', 0), 'replace("abcabcabc", "bc", "dd", 0)'),
    (lambda: 'abcabcabc'.replace('bc', 'dd', -1), 'replace("abcabcabc", "bc", "dd", -1)'),
)
test_map['rfind()'] = (
    (lambda: 'abc'.rfind('a'), 'rfind("abc", "a")'),
    (lambda: 'abc'.rfind('d'), 'rfind("abc", "d")'),
    (lambda: 'abc'.rfind('bc'), 'rfind("abc", "bc")'),
    (lambda: 'abc'.rfind('ac'), 'rfind("abc", "ac")'),
    (lambda: 'abcabc'.rfind('abc'), 'rfind("abcabc", "abc")'),
    (lambda: 'abcab'.rfind('a', 1, 3), 'rfind("abcab", "a", 1, 3)'),
    (lambda: 'abcab'.rfind('a', 1, 4), 'rfind("abcab", "a", 1, 4)'),
    (lambda: 'abcab'.rfind('ab', 1, 3), 'rfind("abcab", "ab", 1, 3)'),
    (lambda: 'abcab'.rfind('ab', 1, 4), 'rfind("abcab", "ab", 1, 4)'),
    (lambda: 'abcab'.rfind('a', 1), 'rfind("abcab", "a", 1)'),
    (lambda: 'abcab'.rfind('a', 4), 'rfind("abcab", "a", 4)'),
    (lambda: 'abcab'.rfind('', 1, 3), 'rfind("abcab", "", 1, 3)'),
    (lambda: 'abcab'.rfind('ab', 999), 'rfind("abcab", "ab", 999)'),
    (lambda: 'abcab'.rfind('ab', 1, 999), 'rfind("abcab", "ab", 1, 999)'),
    (lambda: ''.rfind('a'), 'rfind("", "a")'),
    (lambda: 'a'.rfind(''), 'rfind("a", "")'),
    (lambda: ''.rfind(''), 'rfind("", "")'),
)
test_map['rindex()'] = (
    (lambda: 'abc'.rindex('a'), 'rindex("abc", "a")'),
    (lambda: 'abc'.rindex('d'), 'rindex("abc", "d")'),
    (lambda: 'abc'.rindex('bc'), 'rindex("abc", "bc")'),
    (lambda: 'abc'.rindex('ac'), 'rindex("abc", "ac")'),
    (lambda: 'abcabc'.rindex('abc'), 'rindex("abcabc", "abc")'),
    (lambda: 'abcab'.rindex('a', 1, 3), 'rindex("abcab", "a", 1, 3)'),
    (lambda: 'abcab'.rindex('a', 1, 4), 'rindex("abcab", "a", 1, 4)'),
    (lambda: 'abcab'.rindex('ab', 1, 3), 'rindex("abcab", "ab", 1, 3)'),
    (lambda: 'abcab'.rindex('ab', 1, 4), 'rindex("abcab", "ab", 1, 4)'),
    (lambda: 'abcab'.rindex('a', 1), 'rindex("abcab", "a", 1)'),
    (lambda: 'abcab'.rindex('a', 4), 'rindex("abcab", "a", 4)'),
    (lambda: 'abcab'.rindex('', 1, 3), 'rindex("abcab", "", 1, 3)'),
    (lambda: 'abcab'.rindex('ab', 999), 'rindex("abcab", "ab", 999)'),
    (lambda: 'abcab'.rindex('ab', 1, 999), 'rindex("abcab", "ab", 1, 999)'),
    (lambda: ''.rindex('a'), 'rindex("", "a")'),
    (lambda: 'a'.rindex(''), 'rindex("a", "")'),
    (lambda: ''.rindex(''), 'rindex("", "")'),
)
test_map['rjust()'] = (
    (lambda: 'a'.rjust(1), 'rjust("a", 1)'),
    (lambda: 'a'.rjust(2), 'rjust("a", 2)'),
    (lambda: 'a'.rjust(3), 'rjust("a", 3)'),
    (lambda: 'a'.rjust(4), 'rjust("a", 4)'),
    (lambda: 'aa'.rjust(2), 'rjust("aa", 2)'),
    (lambda: 'aa'.rjust(3), 'rjust("aa", 3)'),
    (lambda: 'aa'.rjust(4), 'rjust("aa", 4)'),
    (lambda: 'aa'.rjust(5), 'rjust("aa", 5)'),
    (lambda: 'A A '.rjust(9), 'rjust("A A ", 9)'),
    (lambda: 'A A '.rjust(10), 'rjust("A A ", 10)'),
    (lambda: 'A A '.rjust(11), 'rjust("A A ", 11)'),
    (lambda: 'A A '.rjust(15), 'rjust("A A ", 15)'),
    (lambda: 'a'.rjust(0), 'rjust("a", 0)'),
    (lambda: 'a'.rjust(-1), 'rjust("a", -1)'),
    (lambda: 'a'.rjust(2, '@'), 'rjust("a", 2, "@")'),
    (lambda: 'abc'.rjust(10, '@'), 'rjust("abc", 10, "@")'),
    (lambda: 'a'.rjust(1, '@@'), 'rjust("a", 1, "@@")'),
    (lambda: 'a'.rjust(1, ''), 'rjust("a", 1, "")'),
    (lambda: ''.rjust(0), 'rjust("", 0)'),
    (lambda: ''.rjust(1), 'rjust("", 1)'),
    (lambda: ''.rjust(2), 'rjust("", 2)'),
)
test_map['rpartition()'] = (
    (lambda: 'abc'.rpartition('a'), 'rpartition("abc", "a")'),
    (lambda: 'abc'.rpartition('b'), 'rpartition("abc", "b")'),
    (lambda: 'abc'.rpartition('c'), 'rpartition("abc", "c")'),
    (lambda: 'abc'.rpartition('d'), 'rpartition("abc", "d")'),
    (lambda: 'ab ab '.rpartition('a'), 'rpartition("ab ab ", "a")'),
    (lambda: 'ab ab '.rpartition('b'), 'rpartition("ab ab ", "b")'),
    (lambda: 'ab ab '.rpartition('ab'), 'rpartition("ab ab ", "ab")'),
    (lambda: 'ab ab '.rpartition('ba'), 'rpartition("ab ab ", "ba")'),
    (lambda: 'ab ab '.rpartition('b a'), 'rpartition("ab ab ", "b a")'),
    (lambda: ' ab ab '.rpartition(' '), 'rpartition(" ab ab ", " ")'),
    (lambda: ' ab ab '.rpartition(''), 'rpartition(" ab ab ", "")'),
    (lambda: 'a'.rpartition(''), 'rpartition("a", "")'),
    (lambda: ''.rpartition('a'), 'rpartition("", "a")'),
    (lambda: ''.rpartition(''), 'rpartition("", "")'),
)
test_map['rsplit() with sep'] = (
    (lambda: 'abc'.rsplit('a'), 'rsplit("abc", "a")'),
    (lambda: 'abc'.rsplit('b'), 'rsplit("abc", "b")'),
    (lambda: 'abc'.rsplit('c'), 'rsplit("abc", "c")'),
    (lambda: 'abc'.rsplit('d'), 'rsplit("abc", "d")'),
    (lambda: 'ab ab '.rsplit('a'), 'rsplit("ab ab ", "a")'),
    (lambda: 'ab ab '.rsplit('b'), 'rsplit("ab ab ", "b")'),
    (lambda: 'ab ab '.rsplit('ab'), 'rsplit("ab ab ", "ab")'),
    (lambda: 'ab ab '.rsplit('ba'), 'rsplit("ab ab ", "ba")'),
    (lambda: 'ab ab '.rsplit('b a'), 'rsplit("ab ab ", "b a")'),
    (lambda: 'aabb  aabb  '.rsplit('a'), 'rsplit("aabb  aabb  ", "a")'),
    (lambda: 'aabb  aabb  '.rsplit('b'), 'rsplit("aabb  aabb  ", "b")'),
    (lambda: 'aabb  aabb  '.rsplit(' '), 'rsplit("aabb  aabb  ", " ")'),
    (lambda: 'aabb  aabb  '.rsplit('b  a'), 'rsplit("aabb  aabb  ", "b  a")'),
    (lambda: ' ab ab '.rsplit(' '), 'rsplit(" ab ab ", " ")'),
    (lambda: ' ab ab '.rsplit(''), 'rsplit(" ab ab ", "")'),
    (lambda: 'a'.rsplit(''), 'rsplit("a", "")'),
    (lambda: ''.rsplit('a'), 'rsplit("", "a")'),
    (lambda: ''.rsplit(''), 'rsplit("", "")'),
    (lambda: 'abc'.rsplit('a', 1), 'rsplit("abc", "a", 1)'),
    (lambda: 'abc'.rsplit('b', 1), 'rsplit("abc", "b", 1)'),
    (lambda: 'abc'.rsplit('c', 1), 'rsplit("abc", "c", 1)'),
    (lambda: 'abc'.rsplit('d', 1), 'rsplit("abc", "d", 1)'),
    (lambda: 'ab ab '.rsplit('a', 1), 'rsplit("ab ab ", "a", 1)'),
    (lambda: 'ab ab '.rsplit('b', 1), 'rsplit("ab ab ", "b", 1)'),
    (lambda: 'ab ab '.rsplit('ab', 1), 'rsplit("ab ab ", "ab", 1)'),
    (lambda: 'ab ab '.rsplit('ba', 1), 'rsplit("ab ab ", "ba", 1)'),
    (lambda: 'ab ab '.rsplit('b a', 1), 'rsplit("ab ab ", "b a", 1)'),
    (lambda: 'aabb  aabb  '.rsplit('a', 1), 'rsplit("aabb  aabb  ", "a", 1)'),
    (lambda: 'aabb  aabb  '.rsplit('b', 1), 'rsplit("aabb  aabb  ", "b", 1)'),
    (lambda: 'aabb  aabb  '.rsplit(' ', 1), 'rsplit("aabb  aabb  ", " ", 1)'),
    (lambda: 'aabb  aabb  '.rsplit('b  a', 1), 'rsplit("aabb  aabb  ", "b  a", 1)'),
    (lambda: ' ab ab '.rsplit(' ', 1), 'rsplit(" ab ab ", " ", 1)'),
    (lambda: ' ab ab '.rsplit('', 1), 'rsplit(" ab ab ", "", 1)'),
    (lambda: 'a'.rsplit('', 1), 'rsplit("a", "", 1)'),
    (lambda: ''.rsplit('a', 1), 'rsplit("", "a", 1)'),
    (lambda: ''.rsplit('', 1), 'rsplit("", "", 1)'),
    (lambda: 'abc'.rsplit('a', 2), 'rsplit("abc", "a", 2)'),
    (lambda: 'abc'.rsplit('b', 2), 'rsplit("abc", "b", 2)'),
    (lambda: 'abc'.rsplit('c', 2), 'rsplit("abc", "c", 2)'),
    (lambda: 'abc'.rsplit('d', 2), 'rsplit("abc", "d", 2)'),
    (lambda: 'ab ab '.rsplit('a', 2), 'rsplit("ab ab ", "a", 2)'),
    (lambda: 'ab ab '.rsplit('b', 2), 'rsplit("ab ab ", "b", 2)'),
    (lambda: 'ab ab '.rsplit('ab', 2), 'rsplit("ab ab ", "ab", 2)'),
    (lambda: 'ab ab '.rsplit('ba', 2), 'rsplit("ab ab ", "ba", 2)'),
    (lambda: 'ab ab '.rsplit('b a', 2), 'rsplit("ab ab ", "b a", 2)'),
    (lambda: 'aabb  aabb  '.rsplit('a', 2), 'rsplit("aabb  aabb  ", "a", 2)'),
    (lambda: 'aabb  aabb  '.rsplit('b', 2), 'rsplit("aabb  aabb  ", "b", 2)'),
    (lambda: 'aabb  aabb  '.rsplit(' ', 2), 'rsplit("aabb  aabb  ", " ", 2)'),
    (lambda: 'aabb  aabb  '.rsplit('b  a', 2), 'rsplit("aabb  aabb  ", "b  a", 2)'),
    (lambda: ' ab ab '.rsplit(' ', 2), 'rsplit(" ab ab ", " ", 2)'),
    (lambda: ' ab ab '.rsplit('', 2), 'rsplit(" ab ab ", "", 2)'),
    (lambda: 'a'.rsplit('', 2), 'rsplit("a", "", 2)'),
    (lambda: ''.rsplit('a', 2), 'rsplit("", "a", 2)'),
    (lambda: ''.rsplit('', 2), 'rsplit("", "", 2)'),
    (lambda: 'abc'.rsplit('b', 10), 'rsplit("abc", "b", 10)'),
    (lambda: 'abc'.rsplit('b', 0), 'rsplit("abc", "b", 0)'),
    (lambda: 'abc'.rsplit('b', -1), 'rsplit("abc", "b", -1)'),
    (lambda: 'abc'.rsplit('b', -10000), 'rsplit("abc", "b", -10000)'),
)
test_map['rsplit() without sep'] = (
    (lambda: 'abc'.rsplit(), 'rsplit("abc")'),
    (lambda: 'ab ab '.rsplit(), 'rsplit("ab ab ")'),
    (lambda: 'aabb  aabb  '.rsplit(), 'rsplit("aabb  aabb  ")'),
    (lambda: ' ab ab '.rsplit(), 'rsplit(" ab ab ")'),
    (lambda: 'a'.rsplit(), 'rsplit("a")'),
    (lambda: ''.rsplit(), 'rsplit("")'),
    (lambda: 'abc'.rsplit(None, 1), 'rsplit("abc", 1)'),
    (lambda: 'ab ab '.rsplit(None, 1), 'rsplit("ab ab ", 1)'),
    (lambda: 'aabb  aabb  '.rsplit(None, 1), 'rsplit("aabb  aabb  ", 1)'),
    (lambda: ' ab ab '.rsplit(None, 1), 'rsplit(" ab ab ", 1)'),
    (lambda: 'a'.rsplit(None, 1), 'rsplit("a", 1)'),
    (lambda: ''.rsplit(None, 1), 'rsplit("", 1)'),
    (lambda: 'abc'.rsplit(None, 2), 'rsplit("abc", 2)'),
    (lambda: 'ab ab '.rsplit(None, 2), 'rsplit("ab ab ", 2)'),
    (lambda: 'aabb  aabb  '.rsplit(None, 2), 'rsplit("aabb  aabb  ", 2)'),
    (lambda: ' ab ab '.rsplit(None, 2), 'rsplit(" ab ab ", 2)'),
    (lambda: 'a'.rsplit(None, 2), 'rsplit("a", 2)'),
    (lambda: ''.rsplit(None, 2), 'rsplit("", 2)'),
    (lambda: 'abc'.rsplit(None, 10), 'rsplit("abc", 10)'),
    (lambda: 'abc'.rsplit(None, 0), 'rsplit("abc", 0)'),
    (lambda: 'abc'.rsplit(None, -1), 'rsplit("abc", -1)'),
    (lambda: 'abc'.rsplit(None, -10000), 'rsplit("abc", -10000)'),
)
test_map['rstrip()'] = (
    (lambda: 'ab ab'.rstrip('a'), 'rstrip("ab ab", "a")'),
    (lambda: 'ab ab'.rstrip('ab'), 'rstrip("ab ab", "ab")'),
    (lambda: 'ab ab'.rstrip('ba'), 'rstrip("ab ab", "ba")'),
    (lambda: ' ab ab '.rstrip('a'), 'rstrip(" ab ab ", "a")'),
    (lambda: ' ab ab '.rstrip('ab'), 'rstrip(" ab ab ", "ab")'),
    (lambda: ' ab ab '.rstrip('ba'), 'rstrip(" ab ab ", "ba")'),
    (lambda: ' ab ab '.rstrip(), 'rstrip(" ab ab ")'),
    (lambda: ' ab ab '.rstrip(' '), 'rstrip(" ab ab ", " ")'),
    (lambda: ' ab ab '.rstrip(''), 'rstrip(" ab ab ", "")'),
    (lambda: ''.rstrip('a'), 'rstrip("", "a")'),
    (lambda: 'a'.rstrip(''), 'rstrip("a", "")'),
    (lambda: ''.rstrip(''), 'rstrip("", "")'),
)
test_map['split() with sep'] = (
    (lambda: 'abc'.split('a'), 'split("abc", "a")'),
    (lambda: 'abc'.split('b'), 'split("abc", "b")'),
    (lambda: 'abc'.split('c'), 'split("abc", "c")'),
    (lambda: 'abc'.split('d'), 'split("abc", "d")'),
    (lambda: 'ab ab '.split('a'), 'split("ab ab ", "a")'),
    (lambda: 'ab ab '.split('b'), 'split("ab ab ", "b")'),
    (lambda: 'ab ab '.split('ab'), 'split("ab ab ", "ab")'),
    (lambda: 'ab ab '.split('ba'), 'split("ab ab ", "ba")'),
    (lambda: 'ab ab '.split('b a'), 'split("ab ab ", "b a")'),
    (lambda: 'aabb  aabb  '.split('a'), 'split("aabb  aabb  ", "a")'),
    (lambda: 'aabb  aabb  '.split('b'), 'split("aabb  aabb  ", "b")'),
    (lambda: 'aabb  aabb  '.split(' '), 'split("aabb  aabb  ", " ")'),
    (lambda: 'aabb  aabb  '.split('b  a'), 'split("aabb  aabb  ", "b  a")'),
    (lambda: ' ab ab '.split(' '), 'split(" ab ab ", " ")'),
    (lambda: ' ab ab '.split(''), 'split(" ab ab ", "")'),
    (lambda: 'a'.split(''), 'split("a", "")'),
    (lambda: ''.split('a'), 'split("", "a")'),
    (lambda: ''.split(''), 'split("", "")'),
    (lambda: 'abc'.split('a', 1), 'split("abc", "a", 1)'),
    (lambda: 'abc'.split('b', 1), 'split("abc", "b", 1)'),
    (lambda: 'abc'.split('c', 1), 'split("abc", "c", 1)'),
    (lambda: 'abc'.split('d', 1), 'split("abc", "d", 1)'),
    (lambda: 'ab ab '.split('a', 1), 'split("ab ab ", "a", 1)'),
    (lambda: 'ab ab '.split('b', 1), 'split("ab ab ", "b", 1)'),
    (lambda: 'ab ab '.split('ab', 1), 'split("ab ab ", "ab", 1)'),
    (lambda: 'ab ab '.split('ba', 1), 'split("ab ab ", "ba", 1)'),
    (lambda: 'ab ab '.split('b a', 1), 'split("ab ab ", "b a", 1)'),
    (lambda: 'aabb  aabb  '.split('a', 1), 'split("aabb  aabb  ", "a", 1)'),
    (lambda: 'aabb  aabb  '.split('b', 1), 'split("aabb  aabb  ", "b", 1)'),
    (lambda: 'aabb  aabb  '.split(' ', 1), 'split("aabb  aabb  ", " ", 1)'),
    (lambda: 'aabb  aabb  '.split('b  a', 1), 'split("aabb  aabb  ", "b  a", 1)'),
    (lambda: ' ab ab '.split(' ', 1), 'split(" ab ab ", " ", 1)'),
    (lambda: ' ab ab '.split('', 1), 'split(" ab ab ", "", 1)'),
    (lambda: 'a'.split('', 1), 'split("a", "", 1)'),
    (lambda: ''.split('a', 1), 'split("", "a", 1)'),
    (lambda: ''.split('', 1), 'split("", "", 1)'),
    (lambda: 'abc'.split('a', 2), 'split("abc", "a", 2)'),
    (lambda: 'abc'.split('b', 2), 'split("abc", "b", 2)'),
    (lambda: 'abc'.split('c', 2), 'split("abc", "c", 2)'),
    (lambda: 'abc'.split('d', 2), 'split("abc", "d", 2)'),
    (lambda: 'ab ab '.split('a', 2), 'split("ab ab ", "a", 2)'),
    (lambda: 'ab ab '.split('b', 2), 'split("ab ab ", "b", 2)'),
    (lambda: 'ab ab '.split('ab', 2), 'split("ab ab ", "ab", 2)'),
    (lambda: 'ab ab '.split('ba', 2), 'split("ab ab ", "ba", 2)'),
    (lambda: 'ab ab '.split('b a', 2), 'split("ab ab ", "b a", 2)'),
    (lambda: 'aabb  aabb  '.split('a', 2), 'split("aabb  aabb  ", "a", 2)'),
    (lambda: 'aabb  aabb  '.split('b', 2), 'split("aabb  aabb  ", "b", 2)'),
    (lambda: 'aabb  aabb  '.split(' ', 2), 'split("aabb  aabb  ", " ", 2)'),
    (lambda: 'aabb  aabb  '.split('b  a', 2), 'split("aabb  aabb  ", "b  a", 2)'),
    (lambda: ' ab ab '.split(' ', 2), 'split(" ab ab ", " ", 2)'),
    (lambda: ' ab ab '.split('', 2), 'split(" ab ab ", "", 2)'),
    (lambda: 'a'.split('', 2), 'split("a", "", 2)'),
    (lambda: ''.split('a', 2), 'split("", "a", 2)'),
    (lambda: ''.split('', 2), 'split("", "", 2)'),
    (lambda: 'abc'.split('b', 10), 'split("abc", "b", 10)'),
    (lambda: 'abc'.split('b', 0), 'split("abc", "b", 0)'),
    (lambda: 'abc'.split('b', -1), 'split("abc", "b", -1)'),
    (lambda: 'abc'.split('b', -10000), 'split("abc", "b", -10000)'),
)
test_map['split() without sep'] = (
    (lambda: 'abc'.split(), 'split("abc")'),
    (lambda: 'ab ab '.split(), 'split("ab ab ")'),
    (lambda: 'aabb  aabb  '.split(), 'split("aabb  aabb  ")'),
    (lambda: ' ab ab '.split(), 'split(" ab ab ")'),
    (lambda: 'a'.split(), 'split("a")'),
    (lambda: ''.split(), 'split("")'),
    (lambda: 'abc'.split(None, 1), 'split("abc", 1)'),
    (lambda: 'ab ab '.split(None, 1), 'split("ab ab ", 1)'),
    (lambda: 'aabb  aabb  '.split(None, 1), 'split("aabb  aabb  ", 1)'),
    (lambda: ' ab ab '.split(None, 1), 'split(" ab ab ", 1)'),
    (lambda: 'a'.split(None, 1), 'split("a", 1)'),
    (lambda: ''.split(None, 1), 'split("", 1)'),
    (lambda: 'abc'.split(None, 2), 'split("abc", 2)'),
    (lambda: 'ab ab '.split(None, 2), 'split("ab ab ", 2)'),
    (lambda: 'aabb  aabb  '.split(None, 2), 'split("aabb  aabb  ", 2)'),
    (lambda: ' ab ab '.split(None, 2), 'split(" ab ab ", 2)'),
    (lambda: 'a'.split(None, 2), 'split("a", 2)'),
    (lambda: ''.split(None, 2), 'split("", 2)'),
    (lambda: 'abc'.split(None, 10), 'split("abc", 10)'),
    (lambda: 'abc'.split(None, 0), 'split("abc", 0)'),
    (lambda: 'abc'.split(None, -1), 'split("abc", -1)'),
    (lambda: 'abc'.split(None, -10000), 'split("abc", -10000)'),
)
test_map['splitlines()'] = (
    (lambda: 'abc'.splitlines(), 'splitlines("abc")'),
    (lambda: 'a\rbc'.splitlines(), 'splitlines("a\\rbc")'),
    (lambda: 'a\nbc'.splitlines(), 'splitlines("a\\nbc")'),
    (lambda: 'a\rb\rc'.splitlines(), 'splitlines("a\\rb\\rc")'),
    (lambda: 'a\nb\nc'.splitlines(), 'splitlines("a\\nb\\nc")'),
    (lambda: 'a\r\nbc'.splitlines(), 'splitlines("a\\r\\nbc")'),
    (lambda: 'a\n\rbc'.splitlines(), 'splitlines("a\\n\\rbc")'),
    (lambda: '\r\ra\r\nbc\n'.splitlines(), 'splitlines("\\r\\ra\\r\\nbc\\n")'),
    (lambda: '\n\na\r\nbc\r'.splitlines(), 'splitlines("\\n\\na\\r\\nbc\\r")'),
    (lambda: '\r\na\r\nbc\r\n'.splitlines(), 'splitlines("\\r\\na\\r\\nbc\\r\\n")'),
    (lambda: ''.splitlines(), 'splitlines("")'),
    (lambda: 'abc'.splitlines(True), 'splitlines("abc", true)'),
    (lambda: 'a\rbc'.splitlines(True), 'splitlines("a\\rbc", true)'),
    (lambda: 'a\nbc'.splitlines(True), 'splitlines("a\\nbc", true)'),
    (lambda: 'a\r\nbc'.splitlines(True), 'splitlines("a\\r\\nbc", true)'),
    (lambda: 'a\n\rbc'.splitlines(True), 'splitlines("a\\n\\rbc", true)'),
    (lambda: '\r\ra\r\nbc\n'.splitlines(True), 'splitlines("\\r\\ra\\r\\nbc\\n", true)'),
    (lambda: '\n\na\r\nbc\r'.splitlines(True), 'splitlines("\\n\\na\\r\\nbc\\r", true)'),
    (lambda: '\r\na\r\nbc\r\n'.splitlines(True), 'splitlines("\\r\\na\\r\\nbc\\r\\n", true)'),
    (lambda: ''.splitlines(True), 'splitlines("", true)'),
)
test_map['startswith() with single prefix'] = (
    (lambda: 'a'.startswith('a'), 'startswith("a", "a")'),
    (lambda: 'abc'.startswith('a'), 'startswith("abc", "a")'),
    (lambda: 'abc'.startswith('c'), 'startswith("abc", "c")'),
    (lambda: 'abcab'.startswith('ab'), 'startswith("abcab", "ab")'),
    (lambda: 'abcab'.startswith('ac'), 'startswith("abcab", "ac")'),
    (lambda: ''.startswith('a'), 'startswith("", "a")'),
    (lambda: 'a'.startswith(''), 'startswith("a", "")'),
    (lambda: ''.startswith(''), 'startswith("", "")'),
    (lambda: 'abcab'.startswith('a', 1, 3), 'startswith("abcab", "a", 1, 3)'),
    (lambda: 'abcab'.startswith('a', 1, 4), 'startswith("abcab", "a", 1, 4)'),
    (lambda: 'abcab'.startswith('ab', 1, 3), 'startswith("abcab", "ab", 1, 3)'),
    (lambda: 'abcab'.startswith('ab', 1, 4), 'startswith("abcab", "ab", 1, 4)'),
    (lambda: 'abcab'.startswith('a', 1), 'startswith("abcab", "a", 1)'),
    (lambda: 'abcab'.startswith('a', 4), 'startswith("abcab", "a", 4)'),
    (lambda: 'abcab'.startswith('', 1, 3), 'startswith("abcab", "", 1, 3)'),
    (lambda: 'abcab'.startswith('ab', 999), 'startswith("abcab", "ab", 999)'),
)
test_map['startswith() with multiple prefixes'] = (
    (lambda: 'abc'.startswith(('a', 'b', 'c')), 'startswith("abc", (std::vector<std::string>{"a", "b", "c"}))'),
    (lambda: 'acb'.startswith(('a', 'b', 'c')), 'startswith("acb", (std::vector<std::string>{"a", "b", "c"}))'),
    (lambda: 'ddd'.startswith(('a', 'b', 'c')), 'startswith("ddd", (std::vector<std::string>{"a", "b", "c"}))'),
    (lambda: 'abc'.startswith(('ab', 'bc')), 'startswith("abc", (std::vector<std::string>{"ab", "bc"}))'),
    (lambda: 'acb'.startswith(('ab', 'bc')), 'startswith("acb", (std::vector<std::string>{"ab", "bc"}))'),
    (lambda: 'abc'.startswith(tuple()), 'startswith("abc", (std::vector<std::string>{}))'),
)
test_map['strip()'] = (
    (lambda: 'ab ab '.strip('a'), 'strip("ab ab ", "a")'),
    (lambda: 'ab ab '.strip('ab'), 'strip("ab ab ", "ab")'),
    (lambda: 'ab ab '.strip('ba'), 'strip("ab ab ", "ba")'),
    (lambda: ' ab ab'.strip('a'), 'strip(" ab ab", "a")'),
    (lambda: ' ab ab'.strip('ab'), 'strip(" ab ab", "ab")'),
    (lambda: ' ab ab'.strip('ba'), 'strip(" ab ab", "ba")'),
    (lambda: ' ab ab '.strip(), 'strip(" ab ab ")'),
    (lambda: ' ab ab '.strip(' '), 'strip(" ab ab ", " ")'),
    (lambda: ' ab ab '.strip(''), 'strip(" ab ab ", "")'),
    (lambda: ''.strip('a'), 'strip("", "a")'),
    (lambda: 'a'.strip(''), 'strip("a", "")'),
    (lambda: ''.strip(''), 'strip("", "")'),
)
test_map['swapcase()'] = (
    (lambda: 'a'.swapcase(), 'swapcase("a")'),
    (lambda: 'Ab'.swapcase(), 'swapcase("Ab")'),
    (lambda: 'abc'.swapcase(), 'swapcase("abc")'),
    (lambda: 'aBc'.swapcase(), 'swapcase("aBc")'),
    (lambda: 'a c'.swapcase(), 'swapcase("a c")'),
    (lambda: '3'.swapcase(), 'swapcase("3")'),
    (lambda: '3F'.swapcase(), 'swapcase("3F")'),
    (lambda: ''.swapcase(), 'swapcase("")'),
    (lambda: '@'.swapcase(), 'swapcase("@")'),
    (lambda: ' '.swapcase(), 'swapcase(" ")'),
    (lambda: '3F@'.swapcase(), 'swapcase("3F@")'),
    (lambda: '\n'.swapcase(), 'swapcase("\\n")'),
)
test_map['title()'] = (
    (lambda: 'a'.title(), 'title("a")'),
    (lambda: 'aaa'.title(), 'title("aaa")'),
    (lambda: 'aAa'.title(), 'title("aAa")'),
    (lambda: 'Aaa'.title(), 'title("Aaa")'),
    (lambda: 'aAa AAA aaA'.title(), 'title("aAa AAA aaA")'),
    (lambda: 'AAa AAA AaA'.title(), 'title("AAa AAA AaA")'),
    (lambda: 'Aaa Bbb Ccc'.title(), 'title("Aaa Bbb Ccc")'),
    (lambda: 'aAa\naaA'.title(), 'title("aAa\\naaA")'),
    (lambda: 'aAa0aaA'.title(), 'title("aAa0aaA")'),
    (lambda: 'aAa-aaA'.title(), 'title("aAa-aaA")'),
    (lambda: 'aAa/aaA'.title(), 'title("aAa/aaA")'),
    (lambda: 'aAa\'aaA'.title(), 'title("aAa\'aaA")'),
    (lambda: 'AAa-AaA'.title(), 'title("AAa-AaA")'),
    (lambda: 'Aaa-Abc'.title(), 'title("Aaa-Abc")'),
    (lambda: ' aA a '.title(), 'title(" aA a ")'),
    (lambda: ''.title(), 'title("")'),
)
test_map['upper()'] = (
    (lambda: 'a'.upper(), 'upper("a")'),
    (lambda: 'Ab'.upper(), 'upper("Ab")'),
    (lambda: 'abc'.upper(), 'upper("abc")'),
    (lambda: 'aBc'.upper(), 'upper("aBc")'),
    (lambda: 'a c'.upper(), 'upper("a c")'),
    (lambda: '3'.upper(), 'upper("3")'),
    (lambda: '3F'.upper(), 'upper("3F")'),
    (lambda: ''.upper(), 'upper("")'),
    (lambda: '@'.upper(), 'upper("@")'),
    (lambda: ' '.upper(), 'upper(" ")'),
    (lambda: '3F@'.upper(), 'upper("3F@")'),
    (lambda: '\n'.upper(), 'upper("\\n")'),
)
test_map['zfill()'] = (
    (lambda: '1'.zfill(5), 'zfill("1", 5)'),
    (lambda: '-1'.zfill(5), 'zfill("-1", 5)'),
    (lambda: 'a'.zfill(5), 'zfill("a", 5)'),
    (lambda: '-a'.zfill(5), 'zfill("-a", 5)'),
    (lambda: '100'.zfill(5), 'zfill("100", 5)'),
    (lambda: '-100'.zfill(5), 'zfill("-100", 5)'),
    (lambda: '1000'.zfill(5), 'zfill("1000", 5)'),
    (lambda: '-1000'.zfill(5), 'zfill("-1000", 5)'),
    (lambda: '10000'.zfill(5), 'zfill("10000", 5)'),
    (lambda: '-10000'.zfill(5), 'zfill("-10000", 5)'),
    (lambda: '----'.zfill(5), 'zfill("----", 5)'),
    (lambda: '123'.zfill(0), 'zfill("123", 0)'),
    (lambda: '123'.zfill(-1), 'zfill("123", -1)'),
    (lambda: '123'.zfill(-100), 'zfill("123", -100)'),
    (lambda: ''.zfill(5), 'zfill("", 5)'),
    (lambda: ''.zfill(0), 'zfill("", 0)'),
    (lambda: ''.zfill(-1), 'zfill("", -1)'),
    (lambda: ''.zfill(-100), 'zfill("", -100)'),
)


def create_case_header(name):
    return '\n'.join((
        '    CASE("{0}")'.format(name),
        '    {',
        '        using namespace ken3::pystr;',
        '',
    ))

def create_case_footer():
    return '\n'.join((
        '    },',
        '',
    ))


def esc_and_quotation(s):
    return ('"'
            + (s.replace('\\', '\\\\')
                .replace('"', '\\"')
                .replace('\n', '\\n')
                .replace('\r', '\\r')
                .replace('\t', '\\t'))
            + '"')


def create_expect(test):
    try:
        ret = test[0]()

        if isinstance(ret, bool):
            ret = str(ret).lower()
        elif isinstance(ret, str):
            ret = 'std::string(' + esc_and_quotation(ret) + ')'
        elif (isinstance(ret, (list, tuple)) and
                all(isinstance(r, str) for r in ret)):
            ret = '(std::vector<std::string>{{{0}}})'.format(
                      ', '.join(map(esc_and_quotation, ret))
                  )
        return '        EXPECT({0} == {1});'.format(ret, test[1])
    except BaseException as e:
        ret = e.__class__.__name__
        return '        EXPECT_THROWS_AS({0}, {1});'.format(test[1], ret)


def create_source():
    yield """\
/**
 * @file    unittest/pystr_test.cpp
 * @brief   Testing ken3::pystr using lest. 
 * @author  toda
 * @date    2016-06-29
 * @version 0.1.0
 * @remark  the target is C++11 or more
 * @note    This file is created by Python module to get proper required results.
 *          Please, do not modify this file by manual. 
 */

#include "ken3/pystr.hpp"
#include "unittest/lest.hpp"

namespace {

/**
 * @brief      helper function to create std::string, which is {0x00, 0x01, .., 0x0x7F}.
 * @param[in]  size: the size of createdstd::string. default is 128.
 * @return     created std::string.
 */
std::string str7F(size_t size=128)
{
    std::string s(size, '\\0');
    for (size_t i = 0; i < size; i++) {
        s[i] = static_cast<char>(i);
    }
    return s;
}
/////////////////////////////////////////////////////////////////////////////

} // namespace {

const lest::test specification[] =
{
"""

    for name, tests in test_map.items():
        yield create_case_header(name)
        yield '\n'.join(create_expect(test) for test in tests)
        yield create_case_footer()

    yield """\
};

int main(int argc, char* argv[])
{
    return lest::run(specification, argc, argv);
}
/////////////////////////////////////////////////////////////////////////////

"""


def main():
    with open('pystr_test.cpp', 'w') as file:
        file.write('\n'.join(create_source()))

if __name__ == '__main__':
    main()

