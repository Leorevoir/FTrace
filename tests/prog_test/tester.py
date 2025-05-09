## ----------------------------------------------------------------------------------- ##
##                                                                                     ##
## EPITECH PROJECT - Sat, May, 2025                                                    ##
## Title           - FTRACE                                                            ##
## Description     -                                                                   ##
##     tester                                                                          ##
##                                                                                     ##
## ----------------------------------------------------------------------------------- ##
##                                                                                     ##
##             ███████╗██████╗ ██╗████████╗███████╗ ██████╗██╗  ██╗                    ##
##             ██╔════╝██╔══██╗██║╚══██╔══╝██╔════╝██╔════╝██║  ██║                    ##
##             █████╗  ██████╔╝██║   ██║   █████╗  ██║     ███████║                    ##
##             ██╔══╝  ██╔═══╝ ██║   ██║   ██╔══╝  ██║     ██╔══██║                    ##
##             ███████╗██║     ██║   ██║   ███████╗╚██████╗██║  ██║                    ##
##             ╚══════╝╚═╝     ╚═╝   ╚═╝   ╚══════╝ ╚═════╝╚═╝  ╚═╝                    ##
##                                                                                     ##
## ----------------------------------------------------------------------------------- ##

import os

import config
import test_files.hard_test as ht
import test_files.s_flag_test as sft
import test_files.helper as hlp


def compile_and_copy_binary():
    os.system('cd ../../ && make re && cp ftrace tests/prog_test')
    os.system('chmod +x ftrace')

def clear_dir():
    os.system('rm ftrace')
    os.system('rm -rf tests/*.txt')

def main():
    valid_tests = 0
    compile_and_copy_binary()
    if ht.hard_test():
        valid_tests += 1
    if sft.s_flag_test():
        valid_tests += 1
    if hlp.helper_test():
        valid_tests += 1
    if valid_tests == 3:
        print(f"{config.COLOR_GREEN}============{valid_tests}/3 tests passed!============{config.COLOR_RESET}")
        print(f"{config.COLOR_GREEN}PERFECT congrats !{config.COLOR_RESET}")
    else:
        print(f"{config.COLOR_RED}============{valid_tests}/3 tests passed============{config.COLOR_RESET}")
        print(f"{config.COLOR_GREEN}make sure to fix the errors !{config.COLOR_RESET}")
    clear_dir()

if __name__ == "__main__":
    main()

## ----------------------------------------------------------------------------------- ##
##                                                                                     ##
## MIT License                                                                         ##
## Copyright (c) 2025 paul1.emeriau                                                    ##
##                                                                                     ##
## Permission is hereby granted, free of charge, to any person obtaining a copy        ##
## of this software and associated documentation files (the "Software"), to deal       ##
## in the Software without restriction, including without limitation the rights        ##
## to use, copy, modify, merge, publish, distribute, sublicense, and/or sell           ##
## copies of the Software, and to permit persons to whom the Software is               ##
## furnished to do so, subject to the following conditions:                            ##
##                                                                                     ##
## The above copyright notice and this permission notice shall be included in all      ##
## copies or substantial portions of the Software.                                     ##
##                                                                                     ##
## THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR          ##
## IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,            ##
## FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE         ##
## AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER              ##
## LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,       ##
## OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE       ##
## SOFTWARE.                                                                           ##
##                                                                                     ##
## ----------------------------------------------------------------------------------- ##
