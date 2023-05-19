import ctypes
from pathlib import Path
base = Path(__file__).parent

def to_df(result):
    import io
    import pandas as pd
    f = io.BytesIO(result)
    df = pd.read_csv(f)
    return df

def static_sw(n, k, n1, p, b, c):
    wd = base.parent/'build'
    lib = ctypes.cdll.LoadLibrary(wd/'spt_static.so')
    func = lib.static_sw
    func.argtypes = [ctypes.c_int, ctypes.c_int,
                     ctypes.c_int, ctypes.c_double,
                     ctypes.c_double, ctypes.c_double]
    func.restype = ctypes.c_char_p
    result = func(n, k, n1, p, b, c)
    result = to_df(result)
    return result

def regular_sw(n, k, n1, b, c):
    return static_sw(n, k, n1, 0, b, c)

def dynamic_sw(n, k, n1, p, b, c):
    wd = base.parent/'build'
    lib = ctypes.cdll.LoadLibrary(wd/'spt_dynamic.so')
    func = lib.dynamic_sw
    func.argtypes = [ctypes.c_int, ctypes.c_int,
                     ctypes.c_int, ctypes.c_double,
                     ctypes.c_double, ctypes.c_double]
    func.restype = ctypes.c_char_p
    result = func(n, k, n1, p, b, c)
    result = to_df(result)
    return result

if __name__=='__main__':
    # Print the result
    from timeit import timeit
    from tqdm import tqdm
    df = dynamic_sw(10, 2, 3, 0.1, 1, 1)

    # r = []
    # for n in tqdm([5, 10, 20, 40, 80, 100]):
    #     t = timeit(lambda: dynamic_sw(n, 2, 2, 0.1, 1, 1),
    #                         number=1)
    #     r.append([n, t])
    # import pandas as pd
    # df = pd.DataFrame(r, columns=['n', 't'])
