# -*- coding: utf-8 -*-
""" error test

run compiler with test code, which causes compile error.

"""

import glob
import os
import subprocess
import sys

__author__ = 'toda'
__version__ = '1.0.0'

# compile command
COMMAND = 'g++'
# options of compile command
OPTIONS = ['--std=c++11', '-c', '-I../../']
# '#elif defined D0001_TEST_FUNC_ACTIVATED'
DEF_LENGTH = 39
DEF_PREFIX = '#elif defined D'
DEF_SUFFIX = '_TEST_FUNC_ACTIVATED'


def filenames(targets, exclude):
    """ pick cpp files from current directory

    param[in]  targets: appointed targets file names.
                        if None, pick all files with extension '.cpp'
                        should be string-list or None
    param[in]  exclude: appointed file names to be excluded.
                        should be string-list or None
    return     targer file names in string-list
    """
    if targets:
        names = list(targets)
    else:
        names = [i for i in glob.glob('*.cpp')]
        names += [i for i in glob.glob('*/*.cpp')]

    if exclude:
        names = [i for i in names if i not in exclude]

    return sorted(names)


def execute(name, full_description):
    """ execute test program.

    param[in]  name: appointed target file name. normally .cpp file.
    param[in]  full_description: a flag to show detailed message and
                                 compiler's message
    return     names of NG defines in string-list.
    """
    # open file and get lines
    with open(name, 'r', encoding='utf-8') as file:
        lines = file.readlines()

    # pick up defines
    defines = set()
    for line in lines:
        line = line.strip('\r\n')
        if (len(line) == DEF_LENGTH and
                line.startswith(DEF_PREFIX) and
                line.endswith(DEF_SUFFIX)):
            defines.add(line.split(' ')[2])

    # output file name
    out = '.o'.join(name.rsplit('.cpp', 1))

    # try to compile and get result
    oks = []
    ngs = []

    for define in sorted(defines):
        cmd = ' '.join([COMMAND, name, '-D', define, '-o', out] + OPTIONS)
        proc = subprocess.Popen(cmd, shell=True, cwd=None,
                                stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE)
        stdout, stderr = proc.communicate()
        # record a program if its result is NG
        if proc.returncode != 0:
            oks.append(define)
        else:  # success to compile
            ngs.append(define)
            # remove object file
            os.remove(out)

        if full_description:  # print program's output
            print(stdout.decode('utf-8'))
            print(stderr.decode('utf-8'))

    if full_description:
        print('Result in ' + name)
        print('OK: {0} ({1})'.format(len(oks), ', '.join(oks)))
        print('NG: {0} ({1})'.format(len(ngs), ', '.join(ngs)))

    return ngs


def run_tests(names, full_description):
    """ run each test programs.

    param[in]  names: appointed target file names. normally .cpp files.
    param[in]  full_description: a flag to show detailed message and
                                 compiler's message
    """
    # run all test programs and record NG prgrams
    results = []
    print('Start errortest!')
    for i, name in enumerate(names):
        # print program name
        if full_description:
            print()
        print('{0}/{1}: {2}'.format(i + 1, len(names), name))

        # run a program
        ngs = execute(name, full_description)

        # record a program if its result is NG
        if len(ngs):
            results.append(name)

    # show results
    print()
    print('Results:')
    print('  OK:' + str(len(names) - len(results)))
    print('  NG:' + str(len(results)))
    if results:
        print()
        print('NG Programs:')
        print('\n'.join('  ' + i for i in results))

    return len(results)


def main():
    """ main function """
    import argparse

    # parse sys.argv
    parser = argparse.ArgumentParser(description='errortest')
    parser.add_argument('-v', '--version', action='version',
                        version=('%(prog)s ' + __version__))
    parser.add_argument('-f', '--full_description', action='store_true',
                        help='full description')
    parser.add_argument('-e', '--exclude', type=str, nargs='+',
                        help='file names to be excluded')
    parser.add_argument('-t', '--targets', type=str, nargs='+',
                        help='target file names (default: all)')
    args = parser.parse_args()

    # run each test
    return (
        run_tests(filenames(args.targets, args.exclude),
                  args.full_description)
    )

if __name__ == "__main__":
    sys.exit(main())
