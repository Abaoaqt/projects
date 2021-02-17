import os 
import numpy as np

'''
concept : 	from a dataset with imbalanced classes, artificially create new data points from the chosen class subset and balance the ratios

class assets :
	data array		[m x n]		continuous numerical (for now)
	sample number	[1, p) 		integer
	noise modifier  [0, 1]		floating point

output : 
	[p x n] array

todo :
- implement class structure and methods (done)
- extend to discrete/non-numeric values (done)
- allow for full dataset inclusion, not just the relevant subset. 
- extend to multi class situations
- implement automated balancing
'''
class Oversampler:

	def __init__(self, subset, n, noise):
		self.class_col = None
		# type checking the inputs
		# subset
		if type(subset) is not np.ndarray or subset.shape[0] < 1:
			raise TypeError("`subset` must be an array with mxn dims")
		self.data = subset

		# samples
		if not np.issubdtype(type(n), np.integer) or not n >= 1:
			raise ValueError("`n` must be a non-negative integer")
		self.size = n

		# noise
		if noise > 1 or noise < 0:
			raise ValueError("'noise must be a value between 0 and 1")
		self.noise = noise


	def run(self):
		# instantiate a new array for the artificial 
		
		# start an iteration of size n
		
		#	on each iter:
		#	randomly select two samples from the subset
		#	take the average of the two values for each column
		#	apply the random noise modifier to each average
		# 	if the column contains the class value, skip over this and set the value to the class
		# 	append the results as a new observation in the new array
		
		# create the new array
		newarray = list()

		#determine the column types of the data
		ctypes = self.check_discrete()

		for i in range(0, self.size):
			#determine the indices to be used
			if self.data.shape[0] > 2:
				a, b = self.select_idx()
			
			elif self.data.shape[0] == 2:
				a, b= 0, 1
			
			else:
				a, b = 0, 0 

			new_obs = list()
			for j in range(0, self.data.shape[1]):
				if "float" in str(ctypes[j]):
					# do continuous
					new_obs.append(self.noise_factor(self.data[a][j], self.data[b][j]))

				elif "int" in str(ctypes[j]):
					# do ordinal
					new_obs.append(int(self.noise_factor(self.data[a][j], self.data[b][j])))

				else:
					# do factor/unkown
					new_obs.append(self.data[a][j] if np.random.uniform() < 0.5 else self.data[b][j])

			newarray.append(np.array(new_obs))

		return np.array(newarray)


	# select two indices from the subset to use in the creation of a new sample 
	def select_idx(self):
		selected = np.random.randint(0, self.data.shape[0], 2)
		while selected[0] == selected[1]:
			selected[1] = np.random.randint(0, self.data.shape[0])
		return selected


	# randomly select the value from an range bounded by a proportion of the range of the two original values
	def noise_factor(self, a, b):
		avg = (a + b) * 0.5
		# noise = 0 -> output exactly the average
		# noise = 1 -> output can be in range from min to max
		# noise = n -> some range smaller

		if a > b: 
			upper  = (a - avg) * self.noise + avg
			lower  = avg - (avg - b) * self.noise

		elif b > a:
			upper  = (b - avg) * self.noise + avg
			lower  = avg - (avg - a) * self.noise

		else:
			lower = avg
			upper = avg 

		return round(np.random.uniform(lower, upper), 3)


	# attempt to infer the column data type from a selection of values
	def check_discrete(self):
		# create a dictionary for storing the type by column idx
		ctypes = {}

		#iterate through the columns
		for i in range(0, self.data.shape[1]):
			# isolate the columns
			column  = self.data[:, i]

			ctype = None

			# use 2-3 obs to (almost) ensure the data consistency
			start = type(column[0])
			end = type(column[-1])

			if len(column) > 2:
				rand = type(column[np.random.randint(1, len(column)-1)])
				
				# if all of the types match, then return that type
				if start is end and start is rand:
					ctype = start
				# default to a string type otherwise 
				else:
					ctype = str
					
			else:
				if start is end:
					ctype = start
				else:
					ctype = str

			# add to the dictionary		
			ctypes[i] = ctype

		# return the resulting dict
		return ctypes