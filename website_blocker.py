import time
from datetime import datetime as dt 


hosts_path='D:\CSE\PYTHON\APPLICATIONS\Website Blocker\hosts' #address of hosts file
redirect='127.0.0.1'#redirected url
websites=['www.twitter.com','twitter.com','www.adobe.com','adobe.com']#blocked websites

while True:
    if (dt(dt.now().year,dt.now().month,dt.now().day,8) < dt.now() < dt(dt.now().year,dt.now().month,dt.now().day,18)):
    	
    	with open(hosts_path,'r+') as file:
    	    content=file.read()
    	    for website in websites:
    		    if website in content:
    			    pass
    		    else:
    			    file.write(redirect+' '+website+'\n')
    else:
    	
    	with open(hosts_path,'r+') as file:
    		content=file.readlines()
    		file.seek(0)
    		for line in content:
    			if not any(website in line for website in websites):
    				file.write(line)
    		file.truncate()
    	print("hi")

    	    

    time.sleep(5)#looop timer

