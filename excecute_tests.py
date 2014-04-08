#coding=utf-8
import os
#import ConfigParser

def create_test(test_profile, index):
    path = "tests/" + "profile_%s_%s/"%test_profile + "%0.2d"%index
    os.makedirs(path)
    return path

def excecute_program(test_case, number_of_threads):
    print test_case, number_of_threads

# Generate test cases

# Define os perfils dos testes, ou seja, a "proporção" da matriz.
test_profiles = [
    (1,1),
    (2,1),
    (3,1),
    (3,2),
    (4,3),
]

tests_per_profile = 10

test_cases = []

for test_profile in test_profiles:
    for i in range(tests_per_profile):
        test_cases.append(create_test(test_profile, i))

# Excecute 10 vezes para cada matriz, para cada n

Ns = [1, 2, 4, 8]

for test_case in test_cases:
    for n in Ns:
        excecute_program(test_case, n)
