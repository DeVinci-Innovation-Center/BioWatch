#####################################################################
###     A python script to send the data to the client by WiFi    ###
#####################################################################


from commons import *
from flask import Flask

app = Flask(__name__)                         # Set the app / the server.

data = b''
@app.route("/get_data")                       # Define what happened when the WeMos get data.
def send_data():
     return data.to_string()

def run_tcp_server(buffer: EcFlexValues):
     global data
     data = buffer
     print("Starting server")
     app.run(host = '0.0.0.0', port = 1235)   # Accept all IP addresses.
