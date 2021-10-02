#!/usr/bin/env python3

import re

ASSETS = [ x for x in """
data/robots.txt
data/index.html
data/favicon.ico
data/redirect.html
data/assets/starter-template.css
data/assets/bootstrap.min.css
data/assets/core.js
data/assets/bootstrap.bundle.min.js
""".split("\n") if x and len(x.strip()) ]

def mapped_symbol_radical(file):
    filtered = re.sub(r'\W+', '_', file)

    return filtered

def main():
    print("""#pragma once

""")
    for file in ASSETS:
        radical = mapped_symbol_radical(file)
        print(f"""// {file}: {radical}
extern const uint8_t {radical}_start[]  asm("_binary_{radical}_start");
extern const uint8_t {radical}_end[] asm("_binary_{radical}_end");

extern const size_t {radical}_size = (size_t) ({radical}_end - {radical}_start + 1);        
""")


if __name__ == '__main__':
    main()