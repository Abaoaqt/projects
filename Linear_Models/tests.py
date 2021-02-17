import numpy as np 
import pandas as pd 
import os
import sys
from LinReg import LinearRegression

data = pd.read_csv("2018.csv")
data.head()

LR = LinearRegression()
LR.attach_data(data, response = 8)
LR.show_data()

LR.fit_analytic(norm= True)
LR.get_coefs()

scores = LR.predict_score(data)

print(scores["MSE"])




