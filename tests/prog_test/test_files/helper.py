## ----------------------------------------------------------------------------------- ##
##                                                                                     ##
## EPITECH PROJECT - Sat, May, 2025                                                    ##
## Title           - FTRACE                                                            ##
## Description     -                                                                   ##
##     helper                                                                          ##
##                                                                                     ##
## ----------------------------------------------------------------------------------- ##
##                                                                                     ##
##       _|_|_|_|  _|_|_|    _|_|_|  _|_|_|_|_|  _|_|_|_|    _|_|_|  _|    _|          ##
##       _|        _|    _|    _|        _|      _|        _|        _|    _|          ##
##       _|_|_|    _|_|_|      _|        _|      _|_|_|    _|        _|_|_|_|          ##
##       _|        _|          _|        _|      _|        _|        _|    _|          ##
##       _|_|_|_|  _|        _|_|_|      _|      _|_|_|_|    _|_|_|  _|    _|          ##
##                                                                                     ##
## ----------------------------------------------------------------------------------- ##

import config
import os
import test_files.tools as tools

def helper_test():
    print(f"{config.COLOR_GREEN}============Running helper test...============{config.COLOR_RESET}")
    os.system(f'./ftrace -help > {config.S_FLAG_TEST_FILE} 2>&1')
    file_content = tools.get_file_content(config.S_FLAG_TEST_FILE)
    if not file_content:
        print(f"{config.COLOR_RED}Error: {config.S_FLAG_TEST_FILE} is empty or not found.{config.COLOR_RESET}")
        return False
    for line in file_content:
        if "USAGE: " in line:
            print(f"{config.COLOR_GREEN}USAGE is correct !{config.COLOR_RESET}")
            return True
    print(f"{config.COLOR_RED}HELPER test not passed.{config.COLOR_RESET}")
    return True

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

