#!/usr/bin/python
# -*- encoding: UTF-8 -*-
ROBOT_IP = "localhost"

import os
import sys
import time

from naoqi import ALProxy

def main():
        """ Parse command line arguments,
        run recordData and write the results
        into a csv file

        """

        nao_ip = ROBOT_IP

        key = "asdf"

        if len(sys.argv) != 2:
                sys.stderr.write("Expected one argument: key\n")
                sys.exit()

        key = sys.argv[1]

        memory = ALProxy("ALMemory", nao_ip, 9559)
        value = memory.getData(key)

        print value


if __name__ == "__main__":
        main()
