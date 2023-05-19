import ctypes
from pathlib import Path
base = Path(__file__).parent

def to_df(result):
    import io
    import pandas as pd
    f = io.BytesIO(result)
    df = pd.read_csv(f)
    return df

def get_func(ntype='static', function='static_sw'):
    wd = base.parent/'build'
    lib = ctypes.cdll.LoadLibrary(wd/f'spt_{ntype}.so')
    func = getattr(lib, function)
    func.argtypes = [ctypes.c_int, ctypes.c_int,
                     ctypes.c_int, ctypes.c_double,
                     ctypes.c_double, ctypes.c_double]
    func.restype = ctypes.c_char_p
    return func

def static_sw(n, k, n1, p, b, c):
    func = get_func('static', 'static_sw')
    result = func(n, k, n1, p, b, c)
    result = to_df(result)
    return result

def regular_sw(n, k, n1, b, c):
    return static_sw(n, k, n1, 0, b, c)

def dynamic_sw(n, k, n1, p, b, c):
    func = get_func('dynamic', 'dynamic_sw')
    result = func(n, k, n1, p, b, c)
    result = to_df(result)
    return result

def static_sw_mean(n, k, n1, p, b, c):
    func = get_func('static', 'static_sw_mean')
    result = func(n, k, n1, p, b, c)
    result = to_df(result)
    return result

def regular_sw_mean(n, k, n1, b, c):
    return static_sw_mean(n, k, n1, 0, b, c)

def dynamic_sw_mean(n, k, n1, p, b, c):
    func = get_func('dynamic', 'dynamic_sw_mean')
    result = func(n, k, n1, p, b, c)
    result = to_df(result)
    return result

if __name__=='__main__':
    # Print the result
    from timeit import timeit
    from tqdm import tqdm
    df = dynamic_sw_mean(10, 2, 3, 0.1, 1, 1)
