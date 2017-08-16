import sys
import os
import re

aut = re.compile("^#include \"([^\"]+)\"\\s*$")


sources = sys.argv[1]
headers = sys.argv[2]

names = []

for root, dirs, files in os.walk(headers):
    for f in files:
        names.append(os.path.join(root, f).replace(headers, ""))
print names

def lol(pah):
    for root, dirs, files in os.walk(pah):
        for f in files:
            if f.endswith(".cpp") or f.endswith(".h"):
                ppp = os.path.join(root, f)
                with open(ppp) as currfile:
                    lines = currfile.readlines()
                with open(ppp, "w") as file:
                    for line in lines:
                        m = aut.match(line)
                        if m:
                            Found = False
                            for name in names:
                                if not Found and name == m.group(1):
                                    file.write("#include \"%s\"\n"%name)
                                    Found = True
                            if not Found:
                                for name in names:
                                    if not Found and name.endswith(m.group(1)):
                                        file.write("#include \"%s\"\n"%name)
                                        Found = True
                            if not Found:
                                file.write(line)
                                print "sad but true"
                        else:
                            file.write(line)
lol(sources)
lol(headers)
