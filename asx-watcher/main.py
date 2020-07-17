import requests
import json
import stocks

def retrieve_json(ticker):
	payload = None
	try:
		payload = requests.get("https://www.asx.com.au/asx/1/share/{}".format(ticker)).json()

	except:
		print("Could not collect the data for the stock requested")

	return payload


def collect_data(comps):
	data = {}
	for stock in comps.list.values():
		data[stock.ticker] = retrieve_json(stock.ticker)

	return data


def main():
	nab = stocks.Stock("NAB", "National Australia Bank")
	kgn = stocks.Stock("KGN", "Kogan.com")
	s = stocks.Stocks([nab, kgn])

	data = collect_data(s)

	print(data)


if __name__ == '__main__':
	main()