import json

# 	class for maintaining stocks and the alerts set for each one

class Stocks:

	def __init__(self, stock_list):
		self.list = {}
		for stock in stock_list:
			self.list[stock.name] = stock

class Stock:

	def __init__(self, ticker, name):
		self.ticker = ticker
		self.name = name
		self.alerts = {}

	def add_alert(self, alert, alert_id):
		result = None
		if alert_id not in self.alerts.keys():
			self.alerts[alert_id] = alert
			result = "Alert successfully added"

		else:
			result = "Alert already exists, if you would like to modify the alert, use the modify command"

		return result


	def modify_alert(self, alert, alert_id):
		result = None
		if alert_id in self.alerts.keys():
			self.alerts[alert_id] = alert
			result = "alert successfully changed"

		else:
			result = "Alert does not exist"

		return result


	def delete_alert(self, alert_id):
		try:
			del self.alerts[alert_id]
		
		except:
			print("Could not delete the requested alert")


	def remove_stock(self):
		for alert in self.alerts.keys():
			self.delete_alert(alert)
		
		del self


class alerts:
	types = ['crossing', 'crossing_up', 'crossing_down' ,'greater than', 'less than', 'moving up', 'moving down', 'volume']
	
	def __init__(self, a_type, value, date_end = None):
		assert a_type in types
		self.type = a_type
		self.value = value
		self.date_end = date_end