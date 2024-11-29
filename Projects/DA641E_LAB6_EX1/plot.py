import matplotlib.pyplot as plt
import pandas as pd


file_path = 'data/exp_mov_avg.csv'

data = pd.read_csv(file_path)

data.columns = data.columns.str.strip()


x_raw  = data['xRaw']
y_raw  = data['yRaw']
x_filtered = data['xFiltered']
y_filtered = data['yFiltered']

plt.figure(figsize=(10, 5))

plt.plot(x_raw, label='xRaw', linestyle='-')
plt.plot(x_filtered, label='xFiltered', linestyle='--')

plt.plot(y_raw, label='yRaw', linestyle='-')
plt.plot(y_filtered, label='yFiltered', linestyle='--')

plt.xlabel('Sample')
plt.ylabel('Value')
plt.title('Raw vs Exponential Moving Average')
plt.legend()
plt.grid(True)

plt.savefig('plots/raw_vs_exp_mov_avg.png')
