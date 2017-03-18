import requests
import datetime
import time
import config

def send_command(user_id, command, endpoint):
    data = {
    	'user_id': user_id,
        'token': config.token,
        'command': command,
        'timestamp': time.time()
    }
    r = requests.post(endpoint, json=data)
    return r.text


def main():
	user_id = 1
	command = "popTheCorn"
	print(config)
	send_command(1, command, config.endpoint)


if __name__ == "__main__":
    main()