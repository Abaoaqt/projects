import json

class alerts:

	def __init__(self, alert_list = []):
		self.list = {}
		for alert in alert_list:
			self.list[alert.name] = alert


	def add_alert(self, alert):
		self.list[alert.name] = alert


	def del_alert(self, alert_name):
		self.list.pop(alert_name)


	def get_list_keys(self):
		return self.list.keys()


	def get_alert(self, key):
		return self.list[key]


	def get_num_alerts(self):
		return len(self.list)


	def get_names(self):
		return list(self.list.keys())


	def get_codes(self):
		codes = set()
		for alert in self.list:
			codes.add(self.list[alert].get_code())
		return codes


	def save_alerts(self):
		with open('alerts.json', 'w') as outfile:
			to_save = {}
			for name in self.get_names():
				to_save[name] = self.list[name].get_dict()
			json.dump(to_save, outfile, indent = 4)		


	def load_alerts(self):
		with open('alerts.json') as infile:
			j_alerts = json.load(infile)
		for name in j_alerts.keys():
			self.list[name] = alert(name, j_alerts[name]['code'], j_alerts[name]['type'], j_alerts[name]['value'], j_alerts[name]['date_end'], j_alerts[name]['persistence'])


class alert:
	types = ['crossing', 'crossing_up', 'crossing_down' ,'greater than', 'less than', 'moving up', 'moving down', 'volume']

	def __init__(self, name, code, a_type, value, date_end = None, persistence = False):
		assert a_type in self.types
		
		self.name = name
		self.code = code
		self.type = a_type
		self.value = value
		self.date_end = date_end
		self.persistence = persistence

	def assess_alert(self, values):
		switch = {
		'crossing' : self.crossing(values['previous_close_price'], values['last_price']),
		'crossing_up' : self.crossing_up(values['previous_close_price'], values['last_price']),
		'crossing_down' : self.crossing_down(values['previous_close_price'], values['last_price']),
		}
		return switch[self.type]

	def crossing(self, old, new):
		 # accept three values, an old value, a current value and the required value
		 # if the required value falls in between the old and the new value, then it has crossed and return true to post notification
		 # otherwise don't do anything
		 response = False
		 if self.value < old and self.value > new:
		 	response = True
		 elif self.value < new and self.value > old:
		 	response = True
		 return response


	def crossing_up(self, old, new):
		# accept three values, an old value, a current value and the required value
		# if the the old value is less than the required and the new value is greater that the required return true
		# otherwise don't do anything
		response = False
		if self.value < new and self.value > old:
		 	response = True
		return response


	def crossing_down(self, old, new):
		# accept three values, an old value, a current value and the required value
		# if the the new value is less than the required and the old value is greater that the required return true
		# otherwise don't do anything
		response = False
		if self.value < old and self.value > new:
		 	response = True
		return response

	# change the type , value or expiry date for the alert
	# if the type is changed then the value and date must be reset too
	def modify_alert(self, type_val = None, value = None, date_end = None):
		if type_val != None:
			if value != None and date_end != None:
				self.type = type_val
				self.value = value
				self.date_end = date_end
			else:
				pass # change
		else:
			if value != None:
				self.value = value
			if date_end != None:
				self.date_end = date_end


	def print_alert(self):
		print("\nname: {} \ncode: {} \nalert type: {} \ntarget value: {} \ndate ending: {}\n".format(self.name, self.code, self.type, self.value, self.date_end))


	def get_dict(self):
		a_dict = {}
		a_dict['code'] = self.code
		a_dict['type'] = self.type
		a_dict['value'] = self.value
		a_dict['date_end'] = self.date_end
		a_dict['persistence'] = self.persistence
		return a_dict


	def get_code(self):
		return self.code


	def get_type(self):
		return self.type


	def get_name(self):
		return self.name



'''if __name__ == "__main__":
	a1 = alerts()
	a1.add_alert(alert("nab_1", "nab", "crossing_up", 10))
	a1.add_alert(alert("kgn_1", 'kgn', "crossing", 50, persistence = True))
	a1.add_alert(alert("kgn_2", 'kgn', "crossing", 40, persistence = False))

	data = {"code" : "abc", "previous_close_price" : 8, "last_price" : 12}

	print(a1.get_num_alerts())
	print(a1.get_names())
	print(a1.list['kgn_1'].assess_alert(data))

	print(a1.get_codes())
	a1.save_alerts()

	a2 = alerts()
	a2.load_alerts()
	print(a2.get_codes())'''