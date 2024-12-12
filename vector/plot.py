import matplotlib.pyplot as plt
import pandas as pd

columns = ['n_thread', 'size', 'mean', 'tmean', 'min', 'tmin', 'max', 'tmax', 'sum', 'tsum', 'euclid', 'teuclid']
df = pd.read_csv("CPP_parallelDSTU/vector/stat", sep=" ",
                 names = columns, index_col=False)
print(df.iloc[2])

