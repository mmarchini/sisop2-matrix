import os
import sys
import re


RE_PROFILE = re.compile("profile_(\d+)_(\d+)")
RE_PROFILING_FILE = re.compile("profiling-(\w+)-(\d+)-(\d+).log")
RE_ELAPSED_TIME = re.compile("Elapsed Time\(microseconds\): (\d+)")

if not os.path.exists("./tests"):
    sys.exit(1)

tests_dir = "tests/"

profiles = os.listdir(tests_dir)
test_cases_dicts = {}
for profile_path in profiles:
    profile = RE_PROFILE.match(profile_path).groups()
    test_cases_dicts[profile] = {}

    test_cases = os.listdir(tests_dir + profile_path)

    for test_case in test_cases:
        current_dir = tests_dir + profile_path + "/%s/"%test_case
        test_case_dict = {}
        for f in os.listdir(current_dir):
            re_match = RE_PROFILING_FILE.match(f)
            if not re_match:
                continue
            test_type = re_match.group(1)
            test_threads = re_match.group(2)
            if not test_case_dict.get(test_type, None):
                test_case_dict[test_type] = {}

            if not test_case_dict[test_type].get(test_threads, None):
                test_case_dict[test_type][test_threads] = []

            elapsed_time = -1
            with open(current_dir + f, "r") as file_:
                elapsed_string = filter(lambda a: 'Elapsed' in a, file_.readlines())[0]
                elapsed_time = int(RE_ELAPSED_TIME.match(elapsed_string).group(1))

            if elapsed_time == -1:
                raise Exception("Erro")

            if elapsed_time == 0:
                raise Exception("Erro")

            test_case_dict[test_type][test_threads].append(elapsed_time)
        test_cases_dicts[profile][test_case] = test_case_dict

os.mkdir("results")

files_dict = {}

for profile, test_cases in test_cases_dicts.iteritems():
    for test_case, test_case_dict in test_cases.iteritems():
        for test_type in test_case_dict.keys():
            filename="%s-%s_%s"%(profile+(test_type,))
            if not files_dict.get(filename, None):
                files_dict[filename] = {}
            if not files_dict[filename].get(int(test_case), None):
                files_dict[filename][int(test_case)] = {}
            for test_threads in test_case_dict[test_type].keys():
                files_dict[filename][int(test_case)][int(test_threads)] = int(1/sum(map(lambda r: 1.0/float(r), test_case_dict[test_type][test_threads])))

for filename, file_dict in files_dict.iteritems():
    x=[]
    y=[]
    test_case_legends = []
    for test_case, threads_dict in sorted(file_dict.iteritems(), key=lambda r: r[0]):
        test_case_legends.append(test_case)
        y_ = []
        for thread, elapsed_time in sorted(threads_dict.iteritems(), key=lambda r: r[0]):
            if thread not in x:
                x.append(thread)
            y_.append(elapsed_time)
        y.append(y_)

    with open("results/%s.oct"%filename, "w+") as file_:
        file_.write("x=%s;\n"%x)
        file_.write("y=[%s];\n"%";".join(map(str, y)))
        file_.write("plot(x,y,\"-@\");\n")
        file_.write("title(\"%s %s\");\n"%tuple(filename.split("_")))
        file_.write("xlabel(\"No Threads\");\n")
        file_.write("ylabel(\"Tempo Medio Execucao\");\n")
        file_.write("legend(%s);\n"%", ".join(map(lambda r: "\"%s\""%r, test_case_legends)))
        file_.write("print(\"results/%s.jpg\", \"-djpg\");\n"%filename)

