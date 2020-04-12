#!/usr/bin/env python

with open(".Xresources", "r+") as f:
    x = f.readlines()[:4]
    for (i, line) in enumerate(x):
        if line[0] == '!':
            x[i] = x[i][2:]
        else:
            x[i] = "! " + x[i]
    f.seek(0)
    for line in x:
        f.write(line)


