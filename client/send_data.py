import requests
import datetime
import time
import config

def send_command(user_id, command, token, endpoint):
    data = {
    	'user_id': user_id,
        'token': token,
        'command': command,
        'timestamp': time.time()
    }
    r = requests.post(endpoint, json=data)
    return r.text


def make_popcorn():
	user_id = 1
	command = "popcorn"
	r = send_command(1, command, config.token, config.endpoint)
	if config.debug:
		print(r)

def main():
	make_popcorn()


if __name__ == "__main__":
    main()