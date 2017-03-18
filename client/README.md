# Client

## Requirements:
* Python3.3 - 3.5+

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

*Note:* pyinstaller is s not a cross-compiler: to make a Windows app you run PyInstaller in Windows; to make a Linux app you run it in Linux, etc. 


## API

```
   	{	
    	'user_id' = user_id,
        'token': token,
        'command': command,
        'timestamp': time.time()
    }
```

