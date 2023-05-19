def to_df(result):
    import io
    import pandas as pd
    f = io.BytesIO(result)
    df = pd.read_csv(f)
    return df

