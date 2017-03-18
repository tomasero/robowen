# Client

## Requirements:
* Python3.3 - 3.5+
* OS in which you want to run the application in order to build executable


## Installation:

To install dependencies from the `client` folder run

```
pip install -r requirements.txt
```


## Building:

Run 

```
pyinstaller --windowed app.py
```


## API

```
   	{	
    	'user_id' = user_id,
        'token': token,
        'command': command,
        'timestamp': time.time()
    }
```