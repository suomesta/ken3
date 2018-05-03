# -*- coding: utf-8 -*-
""" stylecheck

check all header and source files are written in common style.

"""

import glob
import os
import sys

__author__ = 'toda'
__version__ = '1.0.0'


def filenames(root_dir):
    """ pick hpp and cpp files from root_dir

    param[in]  root_dir: appointed path of root directory.
                         normaly source root directory ("ken3")
    return     targer file names in string-list
    """
    yield from glob.glob(root_dir + '*.hpp')
    yield from glob.glob(root_dir + '*.cpp')
    yield from glob.glob(root_dir + '*/*.hpp')
    yield from glob.glob(root_dir + '*/*.cpp')


def check(filename, lines):
    def find(key, condition):
        for i, line in enumerate(lines):
            if condition(line, key):
                return i
        return None

    filename = filename.replace('\\', '/')
    guard = ('INCLUDE_GUARD_KEN3_'
             + filename.replace('/', '_').replace('.', '_').upper())

    indices = ((
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
    ))

    last_index = -1
    # doxygen comment in header. [0] to [7]
    index = indices[0]
    if index is not None and index == 0:
        last_index = index
    else:
        yield (filename, 'doxygen comment does not start from 1st line.')
    index = indices[1]
    if index is not None and index == 1:
        last_index = index
    else:
        yield (filename, '@file does not in 2nd line.')
    index = indices[2]
    if index is not None and index == 2:
        last_index = index
    else:
        yield (filename, '@brief does not in 3rd line.')
    index = indices[3]
    if index is not None and index > last_index:
        last_index = index
    else:
        yield (filename, '@author is not mentioned.')
    index = indices[4]
    if index is not None and index > last_index:
        last_index = index
    else:
        yield (filename, '@date is not mentioned.')
    index = indices[5]
    if index is not None and index > last_index:
        last_index = index
    else:
        yield (filename, '@version is not mentioned.')
    index = indices[6]
    if index is not None and index > last_index:
        last_index = index
    else:
        yield (filename, '@remark is not mentioned.')
    index = indices[7]
    if index is not None and index > last_index:
        last_index = index
    else:
        yield (filename, 'doxygen comment does not close.')
    # first blank line. [8]
    index = indices[8]
    if index is not None and index > last_index:
        last_index = index
    else:
        yield (filename, 'no blank line after doxygen comment.')
    # start include guard (only in .hpp files). [9] and [10]
    if filename.endswith('.hpp'):
        index = indices[9]
        if index is not None and index > last_index:
            last_index = index
        else:
            yield (filename, 'no include gurad check.')
        index = indices[10]
        if index is not None and index == (last_index + 1):
            last_index = index
        else:
            yield (filename, 'not include gurad start.')
    # include macro (optional). [11]
    index = indices[11]
    if index is not None:
        if index > last_index:
            last_index = index
        else:
            yield (filename, '#include is not in correct place.')
    # start and end namespace ken3. [12] and [13]
    index = indices[12]
    if index is not None and index > last_index:
        last_index = index
    else:
        yield (filename, 'namespace ken3 does not start.')
    index = indices[13]
    if index is not None and index > last_index:
        last_index = index
    else:
        yield (filename, 'namespace ken3 does not end.')
    # end include guard (only in .hpp files). [14]
    if filename.endswith('.hpp'):
        index = indices[14]
        if index is not None and index > last_index:
            last_index = index
        else:
            yield (filename, 'not include gurad end.')

    if any('\t' in line for line in lines):
        yield (filename, 'includes \\t.')


def run(files):
    """ run each test programs.

    param[in]  names: appointed target file names. normally .cpp files.
    param[in]  full_description: a flag to show detailed message and
                                 compiler's message
    """
    for i in files:
        with open(i, 'r', encoding='utf-8') as file:
            yield from check(i, file.readlines())


def main():
    """ main function """
    import argparse

    # parse sys.argv
    parser = argparse.ArgumentParser(description='stylecheck')
    parser.add_argument('-v', '--version', action='version',
                        version=('%(prog)s ' + __version__))
    parser.add_argument('-r', '--root_dir', type=str, default='',
                        help='root dir path (default: \'\')')
    args = parser.parse_args()

    # run each test
    result = list(run(filenames(args.root_dir)))
    print(result)
    return len(result)

if __name__ == "__main__":
    sys.exit(main())
