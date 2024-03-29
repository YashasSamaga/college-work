import os
import requests
from bs4 import BeautifulSoup
import csv

fetch_url = "https://www.amazon.com/gp/bestsellers/books/?pg={}&ajax=1"
fetch_params = [1, 2, 3, 4, 5]

outputDir = "output"
outputFile = "in_book.csv"
url_domain = "https://www.amazon.in"
errmsg = "Not Available"
delimiter = ';'

try: os.mkdir(outputDir); os.system("touch " + outputDir + '/' + outputFile)
except: pass

with open(outputDir + '/' + outputFile, "w") as outFile:
	header = ["Name", "URL", "Author", "Price", "Number of ratings", "Average Rating"]
	writer = csv.writer(outFile, delimiter = delimiter)
	writer.writerow(header)

	for params in fetch_params:
		full_fetch_url = fetch_url.format(params)		
		data = requests.get(full_fetch_url)
		soup = BeautifulSoup(data.content, "lxml")
		
		for wrapper in soup.find_all("div", attrs = { "class" : "zg_itemWrapper" }):
			book = wrapper.find("div", attrs = { "class" : "a-section" }, recursion = False)
			
			try: title = book.find("img")['alt']
			except:	title = errmsg
				
			try: url = url_domain + book.find("a", recursion = False)["href"]
			except:	url = errmsg
				
			try: author = book.find("a", attrs = { "class" : "a-size-small a-link-child" }).decode_contents()
			except:	
				try: author = book.find("span", attrs = { "class" : "a-size-small a-color-base" }).decode_contents()
				except: author = errmsg
				
			try: price = book.find("span", attrs = { "class" : "p13n-sc-price" }).decode_contents().split()[-1]
			except:	price = errmsg
				
			try:
				ratings = book.find("div", attrs = { "class" : "a-icon-row a-spacing-none" }).find_all("a")
				try: total_ratings = ratings[1].decode_contents()
				except:	total_ratings = errmsg
				
				try: avg_rating = ratings[0].find("span").decode_contents()
				except:	avg_rating = errmsg
			except:
				total_ratings = avg_rating = errmsg
			
			writer.writerow([title, url, author, price, total_ratings, avg_rating])	
