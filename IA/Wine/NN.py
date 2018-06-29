import pandas
import numpy as np
from sklearn.neural_network import MLPRegressor
from sklearn.preprocessing import StandardScaler
from sklearn.externals import joblib
from sklearn.model_selection import train_test_split
from sklearn.metrics import explained_variance_score, mean_absolute_error, mean_squared_error, r2_score

WinePrice = pandas.read_csv('PriceVSQuality.csv')

WinePrice = pandas.concat([WinePrice[['Normalized_Score']],WinePrice[['Price']]],axis=1)

WineQuality = pandas.read_csv('WineQuality_Clean-White.csv')

quality_param = WineQuality.drop('quality',axis=1)
quality_sol = np.ravel(WineQuality.quality)

price_param = WinePrice.drop(['Price'],axis=1)
price_sol = WinePrice.Price

quality_param_train, quality_param_test, quality_sol_train, quality_sol_test = train_test_split(quality_param, quality_sol, test_size = 0.20, stratify = quality_sol)  

price_param_train = price_param[:-75]
price_param_test = price_param[-74:]
price_sol_train = price_sol[:-75]
price_sol_test = price_sol[-74:]

sclQ = StandardScaler().fit(quality_param_train)
sclP = StandardScaler().fit(price_param_train)

quality_param_train = sclQ.transform(quality_param_train)
quality_param_test = sclQ.transform(quality_param_test)
price_param_train = sclP.transform(price_param_train)
price_param_test = sclP.transform(price_param_test)

mlpQ = MLPRegressor(hidden_layer_sizes=(64,64,64), activation="tanh", max_iter=1000, solver="sgd", learning_rate="adaptive", learning_rate_init=0.002, shuffle=True, nesterovs_momentum=True, momentum=0.95)  
mlpQ.fit(quality_param_train, quality_sol_train) 

predictQ = mlpQ.predict(quality_param_test)

mse = mean_squared_error(quality_sol_test,predictQ)
mae = mean_absolute_error(quality_sol_test,predictQ)
evs = explained_variance_score(quality_sol_test,predictQ)
r2 = r2_score(quality_sol_test,predictQ)
   
print(mse)
print(mae)  
print(evs)
print(r2)

mlpP = MLPRegressor(hidden_layer_sizes=(100), max_iter=10000, shuffle=True)  
mlpP.fit(price_param_train, price_sol_train) 

predictP = mlpP.predict(price_param_test)

mse = mean_squared_error(price_sol_test,predictP)
mae = mean_absolute_error(price_sol_test,predictP)
evs = explained_variance_score(price_sol_test,predictP)
r2 = r2_score(price_sol_test,predictP)

print(mse)
print(mae)  
print(evs)
print(r2)

NN_Q = 'NN_Q.sav'
NN_P = 'NN_P.sav'
joblib.dump(mlpQ, NN_Q)
joblib.dump(mlpP, NN_P)

