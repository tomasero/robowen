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

    try:
        response = requests.post(endpoint, json=data)

        # Consider any status other than 2xx an error
        if not response.status_code // 100 == 2:
            return "Error: Unexpected response {}".format(response)

        return response.text
    except requests.exceptions.RequestException as e:
        print(e)
        sys.exit(1)

def make_popcorn():
	user_id = 1
	command = "popcorn"
	return send_command(1, command, config.token, config.endpoint)


def open_door():
	user_id = 1
	command = "open_door"
	return send_command(1, command, config.token, config.endpoint)

def prop_open_door():
	user_id = 1
	command = "prop_open_door"
	return send_command(1, command, config.token, config.endpoint)



def main():
	make_popcorn()


if __name__ == "__main__":
    main()