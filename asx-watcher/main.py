import requests
import json
import stocks
import alerts
import win10toast

toaster = win10toast.ToastNotifier()


def push_notification(alert, data):
	toaster.show_toast("{} on {} has been triggered".format(alert.get_type(), alert.get_name()),
					   "the price was ${} and was last recorded at ${}".format(data[alert.get_code()]['previous_close_price'], data[alert.get_code()]['last_price']),
						duration = 10)
# accepts the ticker code in the form of a string
# returns the JSON payload of the data as a dictionary
def retrieve_json(ticker):
	return requests.get("https://www.asx.com.au/asx/1/share/{}".format(ticker)).json()


# accepts a list of company tickers 
# returns a dictionary associating the price data to each ticker
def collect_data(comps):
	data = {}
	for ticker in comps:
		pl = retrieve_json(ticker)
		if "error_code" not in pl.keys():
			data[ticker] = pl

	return data

# accept the full data payload
# return a reduced dictionary of the original payload
def parse_data(data):
	values = {}
	value_keys = ['previous_close_price', 'last_price', 'volume']
	for ticker in data.keys():
		values[ticker] = {}
		for vk in value_keys:
			values[ticker][vk] = data[ticker][vk]

	return values


def main():
	a = alerts.alerts()
	a.load_alerts()
	#nab = stocks.Stock("NAB", "National Australia Bank")
	#kgn = stocks.Stock("KGN", "Kogan.com")
	#s = stocks.Stocks([nab, kgn])

	# determine the required tickers based on the current active alerts
	codes = a.get_codes()
	
	# collect the data for each of these tickers
	data = collect_data(codes)

	# parse the payloads and keep what is needed
	parsed = parse_data(data)

	print(parsed)
	for alert_key in a.get_list_keys():
		alert = a.get_alert(alert_key)

		if alert.assess_alert(parsed[alert.get_code()]):
			print("it's stonks tiem")
			push_notification(alert, parsed)

		else:
			print("it's not stonks tiem")

if __name__ == '__main__':
	main()