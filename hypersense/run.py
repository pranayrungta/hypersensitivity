def to_df(result):
    import io
    import pandas as pd
    f = io.BytesIO(result)
    df = pd.read_csv(f)
    return df


import ctypes
lib = ctypes.cdll.LoadLibrary('./test.so')

def static_sw(n, k, p, b, c):
    func = lib.static_sw
    func.argtypes = [ctypes.c_int, ctypes.c_int,
                     ctypes.c_double, ctypes.c_double,
                     ctypes.c_double]
    func.restype = ctypes.c_char_p
    result = func(n, k, p, b, c)
    result = to_df(result)
    return result

# Print the result
df = static_sw(10, 2, 0.1, 1, 1)
print(df)

