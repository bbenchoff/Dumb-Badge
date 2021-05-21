import re
import sys


file = open(sys.argv[1],"rb")

esc_codes = [""]

regex = re.compile(br'''
    (?: # either 7-bit C1, two bytes, ESC Fe (omitting CSI)
        \x1B
        [@-Z\\-_]
    |   # or a single 8-bit byte Fe (omitting CSI)
        [\x80-\x9A\x9C-\x9F]
    |   # or CSI + control codes
        (?: # 7-bit CSI, ESC [ 
            \x1B\[
        |   # 8-bit CSI, 9B
            \x9B
        )
        [0-?]*  # Parameter bytes
        [ -/]*  # Intermediate bytes
        [@-~]   # Final byte
    )
''', re.VERBOSE)

with file:
    for line in file:
        result = regex.findall(line)
        esc_codes.append(result)



for i in esc_codes:
    print(i)
  


