import plotly.express as px
import pandas as pd

df = pd.read_csv("test_dataset.csv")

#print(df.to_string())
fig = px.line(df, x="_Date_", y="_MPH_", title='Speed (MPH) Over Time')
fig.show()
