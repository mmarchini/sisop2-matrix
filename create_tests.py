#!/usr/bin/env python
#coding=utf-8

import shutil
import os
import numpy
import random
from config import Config

config = Config()

if config.get("seed"):
    random.seed(config.get("seed"))

numeric_range = config.get("cells_range")

def create_test(test_profile, index):
    path = "tests/" + "profile_%s_%s/"%test_profile + "%0.2d"%index
    os.makedirs(path)

    test_case = map(lambda r: r*index, test_profile)
    print test_case

    m1 = []
    for i in range(test_case[0]):
        row = []
        for j in range(test_case[1]):
            row.append(random.randrange(*numeric_range))
        m1.append(row)

    m2 = []
    for i in range(test_case[1]):
        row = []
        for j in range(test_case[0]):
            row.append(random.randrange(*numeric_range))
        m2.append(row)

    with open("%s/in1.txt"%path, "w") as file_:
        file_.write("LINHAS = %s\n"%test_case[0])
        file_.write("COLUNAS = %s\n"%test_case[1])
        file_.writelines("\n".join([" ".join(map(str,row)) for row in m1]))

    with open("%s/in2.txt"%path, "w") as file_:
        file_.write("LINHAS = %s\n"%test_case[1])
        file_.write("COLUNAS = %s\n"%test_case[0])
        file_.writelines("\n".join([" ".join(map(str,row)) for row in m2]))

    result = numpy.matrix(m1)*numpy.matrix(m2)

    with open("%s/result.txt"%path, "w") as file_:
        file_.write("LINHAS = %s\n"%result.shape[0])
        file_.write("COLUNAS = %s\n"%result.shape[1])
        file_.writelines("\n".join([" ".join(map(str,row)) for row in result.tolist()]))

    return path

# Generate test cases
if os.path.exists("tests"):
    shutil.rmtree("tests")


# Define os perfils dos testes, ou seja, a "proporção" da matriz.
test_profiles = config.get("profiles")

test_cases = config.get("multipliers")

for test_profile in test_profiles:
    for i in test_cases:
        create_test(test_profile, i)

