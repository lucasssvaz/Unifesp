import pandas
import numpy as np

WQ_index = ['fixed_acidity','volatile_acidity','citric_acid','residual_sugar','chlorides','free_sulfur_dioxide','total_sulfur_dioxide','density','pH','sulphates','alcohol']
index = ['fixed_acidity','volatile_acidity','citric_acid','residual_sugar','chlorides','free_sulfur_dioxide','total_sulfur_dioxide','density','pH','sulphates','alcohol','quality']

PriceQuality = pandas.read_csv('PriceVSQuality.csv')
PriceQuality = PriceQuality.dropna()

WineQuality = pandas.read_csv('WineQuality-All.csv')

WineQuality = WineQuality[WineQuality[WQ_index].apply(lambda x: np.abs(x - x.mean()) / x.std() < 3).all(axis=1)]

WineQuality=pandas.concat([WineQuality[WQ_index],WineQuality[['quality']]],axis=1)

WineQuality=WineQuality[index]

print(WineQuality.describe())

WineQuality.to_csv('WineQuality_Clean-All.csv',mode='w',index=False)
PriceQuality.to_csv('PriceVSQuality.csv',mode='w',index=False)