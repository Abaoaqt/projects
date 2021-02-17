import os
import numpy as np
import pandas as pd

#	Implementation of a simple linear regression model class
#	functionality includes, preprocessing, fitting to data (iterative and analytic), predicting new data, normalising 

#	TODO:
#	implement all current functions
#	handle factors 
#	adding non-linear terms
#	regularisation 
#	conform data for predictions and allow for singular input rather than y, X.

class LinearRegression:
	def __init__(self):
		self.thetas = None
		self.loss = 0
		self.response = 0
		self.data = None
		self.y = None
		self.X = None
		self.warnings = {"empty_data": True, "invalid_resp" : True, "invalid_preds": True, "diff_lengths": True}
		self.untrained = True
		self.norm = False
	

	#	add an internal representation of the dataset
	#	includes an optional parameter for specifying the response column
	def attach_data(self, data, response = 0):
		# 	add the dataset unchanged
		if isinstance(data, pd.DataFrame):
			self.data = data
		
		else:
			self.data = pd.DataFrame(np.array(data))
		
		self.set_response(response)

		assert self.data.shape[0] > 0

		if self.warnings['invalid_resp'] == False:
			self.X = self.data.drop(self.response, axis = 1)
			# 	remove identity variables and factors (for now)
			self.X = self.X.drop(list(self.X.columns[self.X.dtypes == "object"]), axis = 1)

		if self.X is not None:
			self.warnings['invalid_preds'] = False

		if self.X.shape[0] == self.y.shape[0]:
			self.warnings["diff_lengths"] = False

		self.warnings["empty_data"] = False


	#	select the response factor to perform regression upon
	def set_response(self, response):
		#	check that the response is not an identity variable
		#	allow for column indexing and column names
		#	if there are any errors trigger the warning, this will prevent the user from moving forward until it is resolved

		#	string type response
		if isinstance(response, str):
			if self.data[response].dtypes == "object":
				self.warnings["invalid_resp"] = True

			else:
				self.response = response
				self.y = self.data[response]
				self.warnings["invalid_resp"] = False

		# 	integer type response
		elif isinstance(response, int):
			if self.data[self.data.columns[response]].dtypes == "object":
				self.warnings["invalid_resp"] = True

			else:
				self.response = self.data.columns[response]
				self.y = self.data[self.response]
				self.warnings["invalid_resp"] = False

		#	illegal response
		else:
			self.warnings["invalid_resp"] = True

		if self.warnings['invalid_resp'] == True:
			print("Innapropriate response variable selected!")


	def normalise(self, y, X):
		norm_y = (y - np.mean(y))/np.std(y)
		norm_X = (X - np.mean(X))/np.std(X)
		self.norm = True
		return norm_y, norm_X


	def fit_analytic(self, norm = False):
		#	ensure that all warnings are cleared
		if self.check_warnings() == False:
			if norm:
				y, X = self.normalise(self.y, self.X)

			else:
				y = self.y
				X = self.X

			#	coefs can be calculated using formula (X'X)^-1 X'y
			#	(X'X)^-1
			inv = np.linalg.inv(np.matmul(np.transpose(np.array(X)), np.array(X)))
			#	X'y
			num = np.matmul(np.transpose(np.array(X)), np.array(y))

			self.thetas = np.matmul(inv, num).reshape(1, X.shape[1])
		
		else:
			print("The data does not meet the constraints to allow for Linear Regression.\nPlease reconfigure the data.")

		self.untrained = False


	def fit_iterative(self):
		return None


	# enter unseen data and predict the values using the regression 
	def predict_score(self, data):
		if self.untrained:
			print("No model has been trained yet, please fit a model to the training data first.")
		
		else:
			y, X = self.conform_data(data)

			y_preds = np.dot(self.thetas, X.T)
			MAE = np.mean(np.abs(np.array(y).reshape(-1, 1) - y_preds.T))
			MSE = np.mean(np.array(y).reshape(-1, 1)**2 - y_preds.T**2)
			y_dict = {"y_preds" : y_preds, "MAE": MAE, "MSE": MSE }

			return y_dict



	# 	print a section rows 
	def show_data(self, start = 0, stop = 5):
		if self.warnings['invalid_resp']  or self.warnings['invalid_preds']:
			print("Please ensure the integrity of the data before continuing.")

		else:
			if start >= 0 and stop > start:
				print("response values:")
				print(self.y[start : stop])

				print("predictors:")
				print(self.X[start : stop])

			else: 
				print("Invalid indices selected")


	def check_warnings(self):
		warnings = False
		for w in self.warnings:
			print(w, ":", self.warnings[w])
			if self.warnings[w] == True:
				warnings = True
		return warnings

	#	
	def conform_data(self, new_data):
		y = new_data[self.response]
		X = new_data.drop(self.response, axis = 1)
		X = X.drop(list(X.columns[X.dtypes == "object"]), axis = 1)
		
		if self.norm:
			y, X = self.normalise(y, X)
		assert X.shape[1] == self.X.shape[1]
		
		return y, X

	def get_coefs(self):
		print(self.thetas)

