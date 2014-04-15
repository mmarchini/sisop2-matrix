#!/usr/bin/env python
#coding=utf-8

import os
import numpy
import random
#import ConfigParser

random.seed(3)
range_ = (1, 20)
numeric_range = (5, 40)

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

# Define os perfils dos testes, ou seja, a "proporção" da matriz.
test_profiles = [
    (1,1),
    (2,1),
    (3,1),
    (3,2),
    (4,3),
]

test_cases = []

tests_per_profile = 5

for test_profile in test_profiles:
    for i in range(1,tests_per_profile+1):
        test_cases.append(create_test(test_profile, i))

