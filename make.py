# g++ -shared -o outfile.so -fPIC infile.cpp
# nm -D ./libhello.so

files = {
    # "src/N1vsX/Heterogeneity Analysis static.cpp": 'n1vsx_static',
    # "src/N1vsX/Heterogeneity Analysis dynamic.cpp": 'n1vsx_dynamic',
    "src/spacetime/dynamic.cpp": 'spt_dynamic',
    "src/spacetime/static.cpp": 'spt_static',
}

import os

for infile, outfile in files.items():
    cmd = f'g++ -std=c++11 -shared -fPIC "{infile}" -o "build/{outfile}.so"'
    print(cmd)
    os.system(cmd)
