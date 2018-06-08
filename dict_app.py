import json
from difflib import get_close_matches
data =json.load(open("data.json"))
global new_word
def translate(w):
	if w in data:
		return data[word]
	elif w.lower() in data:
		return data[word]
		
	elif len(get_close_matches(w,data.keys()))>0:
		yn =input("Did you mean %s(y/n)?" % get_close_matches(w,data.keys())[0])
		if yn =="y":
			return data[get_close_matches(w,data.keys())[0]]
		else:
			exit(0)
		
	else:
		return "Word doesn't exist.Check it"

word = input("Enter word:")

print(translate(word))
