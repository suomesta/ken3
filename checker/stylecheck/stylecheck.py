# -*- coding: utf-8 -*-
"""stylecheck does style check of ken3 source code.

check all header and source files are written in common style.
"""

from collections import namedtuple
import glob
import sys

__author__ = 'toda'
__version__ = '1.0.0'


def pick_names(root_dir):
    """Pick hpp and cpp files from root_dir.

    param[in]  root_dir: appointed path of root directory.
                         normaly source root directory "../../ken3/"
    yield      target file names in string-list
    """
    yield from glob.glob(root_dir + '*.hpp')
    yield from glob.glob(root_dir + '*.cpp')
    yield from glob.glob(root_dir + '*/*.hpp')
    yield from glob.glob(root_dir + '*/*.cpp')


def create_indices(filename, lines):
    """Create index list from lines.

    param[in]  filename: appointed file name in str. already processed to
                         handle easier.
    param[in]  lines: lines in file.
    return     index numbers in tuple.
    """
    def find(key, condition):
        """Find and return index from str-list."""
        for i, line in enumerate(lines):
            if condition(line, key):
                return i
        return None

    guard = ('INCLUDE_GUARD_KEN3_' +
             filename.replace('/', '_').replace('.', '_').upper())

    return (
        # doxygen comment in header. [0] to [7]
        find('/**\n', str.__eq__),
        find(' * @file    ken3/{0}\n'.format(filename), str.__eq__),
        find(' * @brief ', str.startswith),
        find(' * @author  toda\n', str.__eq__),
        find(' * @date ', str.startswith),
        find(' * @version ', str.startswith),
        find(' * @remark ', str.startswith),
        find(' */\n', str.__eq__),
        # first blank line. [8]
        find('\n', str.__eq__),
        # start include guard (only in .hpp files). [9] and [10]
        find('#ifndef {0}\n'.format(guard), str.__eq__),
        find('#define {0}\n'.format(guard), str.__eq__),
        # include macro (optional). [11]
        find('#include ', str.startswith),
        # start and end namespace ken3. [12] and [13]
        find('namespace ken3 {\n', str.__eq__),
        find('} // namespace ken3 {\n', str.__eq__),
        # end include guard (only in .hpp files). [14]
        find('#endif // #ifndef {0}\n'.format(guard), str.__eq__),
    )


def check(filename, lines):
    """Check a file and yield found problem.

    param[in]  filename: appointed file name in str.
    param[in]  lines: lines in file.
    yield      (filename, message)
               if no problem is found then empty.
    """
    Condition = namedtuple('Condition', ('mandatory', 'fix', 'message'))
    conditions = (
        # doxygen comment in header. [0] to [7]
        Condition(True, True, 'doxygen comments are not from 1st line.'),
        Condition(True, True, '@file is not in 2nd line.'),
        Condition(True, True, '@brief is not in 3rd line.'),
        Condition(True, False, '@author is not mentioned.'),
        Condition(True, False, '@date is not mentioned.'),
        Condition(True, False, '@version is not mentioned.'),
        Condition(True, False, '@remark is not mentioned.'),
        Condition(True, False, 'doxygen comments do not close.'),
        Condition(True, False, 'no blank line after doxygen comment.'),
        # start include guard (only in .hpp files). [9] and [10]
        Condition(False, False, 'wrong place include guard check.'),
        Condition(False, True, 'wrong place include guard start.'),
        # include macro (optional). [11]
        Condition(False, False, '#include is not in correct place.'),
        # start and end namespace ken3. [12] and [13]
        Condition(True, False, 'namespace ken3 does not start.'),
        Condition(True, False, 'namespace ken3 does not end.'),
        # end include guard (only in .hpp files). [14]
        Condition(False, False, 'wrong place include guard end.'),
    )

    indices = create_indices(filename, lines)
    assert len(conditions) == len(indices)

    last_index = -1
    for index, condition in zip(indices, conditions):
        if index is None:
            if condition.mandatory:
                yield (filename, condition.message)
            else:
                pass
        else:
            if condition.fix and index == (last_index + 1):
                last_index = index
            elif (not condition.fix) and index > last_index:
                last_index = index
            else:
                yield (filename, condition.message)

    if filename.endswith('.hpp'):
        if any(indices[i] is None for i in (9, 10, 14)):
            yield (filename, 'not correct include guard.')
    else:
        if any(indices[i] is not None for i in (9, 10, 14)):
            yield (filename, 'not necessary include guard.')

    if any('\t' in line for line in lines):
        yield (filename, 'includes \\t.')


def run(filenames, root_dir):
    """Check for all files.

    param[in]  filenames: appointed target file names.
    param[in]  root_dir: appointed path of root directory.
                         normaly source root directory "../../ken3/"
    yield      (filename, message)
               if no problem is found then empty.
    """
    for filename in filenames:
        with open(filename, encoding='utf-8') as file:
            filename = filename.replace('\\', '/')[len(root_dir)::]
            yield from check(filename, file.readlines())


def main():
    """Parse args by argparse and run each tests.

    return     the number of problems.
    """
    import argparse

    # parse sys.argv
    parser = argparse.ArgumentParser(description='stylecheck')
    parser.add_argument('-v', '--version', action='version',
                        version=('%(prog)s ' + __version__))
    parser.add_argument('-r', '--root_dir', type=str, default='../../ken3/',
                        help='root dir path (default: \'../../ken3/\')')
    args = parser.parse_args()

    # run each test
    result = list(run(pick_names(args.root_dir), args.root_dir))
    if result:
        print(result)
    return len(result)


if __name__ == "__main__":
    sys.exit(main())
