## ----------------------------------------------------------------------------------- ##
##                                                                                     ##
## EPITECH PROJECT - Sat, May, 2025                                                    ##
## Title           - FTRACE                                                            ##
## Description     -                                                                   ##
##     tools                                                                           ##
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

import config

def get_file_content(file_path):
    lines_in_file = set()
    try:
        with open(file_path, 'r') as f:
            for line in f:
                lines_in_file.add(line.strip())
        return lines_in_file
    except FileNotFoundError:
        print(f"{config.COLOR_RED}Error: tests/hard_test.txt not found.{config.COLOR_RESET}")


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
