###############################################################################
###    A python script to recover the data from the server (the ec-Flex),   ###
###          send it to the client and print user-friendly values           ###
###############################################################################

#### Imports ####
import asyncio
import struct
import sqlite3
import os
from bleak import BleakClient, BleakScanner
from bleak.exc import BleakError
from multiprocessing import Value, Process
from threading import Thread
from server import run_tcp_server
from commons import *


#### Constants definition ####
DB_FILE = '/home/vivien/Documents/GitHub/biowatch/ecflex-to-biowatch_wireless_communication/database.db'     # Enter the access path of the database.db file
SCHEMA_FILE = '/home/vivien/Documents/GitHub/biowatch/ecflex-to-biowatch_wireless_communication/schema.sql'  # Enter the access path of the schema.sql file
MULTIPROCES_VALUES = EcFlexValues()
N0, D0, X0, N1, D1, N2 = 1,1,1,1,1,1


#### Addresses definition ####
mac_addr = "00:35:ff:0b:ae:4c"                            # Ec-Flex mac address 
vendor_service = "00002d8d-0000-1000-8000-00805f9b34fb"   # Vendor sevice address
handle17 = "00002da7-0000-1000-8000-00805f9b34fb"         # Handle 17 | from Vendor service
handle24 = "00002da9-0000-1000-8000-00805f9b34fb"         # Handle 24 | N0 | ADC reference voltage
handle21 = "00002da8-0000-1000-8000-00805f9b34fb"         # Handle 21 | D0 | ADC resolution
handle27 = "00002daa-0000-1000-8000-00805f9b34fb"         # Handle 27 | X0 | Virtual ground level
handle30 = "00002dab-0000-1000-8000-00805f9b34fb"         # Handle 30 | D1 | Current-to-voltage amplification
handle96 = "00002e01-0000-1000-8000-00805f9b34fb"         # Handle 96 | N1 | Scale factor for current
handle99 = "00002e02-0000-1000-8000-00805f9b34fb"         # Handle 99 | N2 | Scale-factor for non-offset linear conversion


#### Database setup ####
with open(SCHEMA_FILE, 'r') as rf:
    schema = rf.read()                           # Read the schema from the file.
#    print(schema, SCHEMA_FILE)
conn = sqlite3.connect(DB_FILE)
print('Connection to database established') 
conn.executescript(schema)                       # Execute the SQL query to create the table.
conn.commit()
print('Database table created')


##### Data updater #####
def update_value(**kwargs):
    global MULTIPROCES_VALUES
    for k in kwargs:
        v = kwargs[k]
        MULTIPROCES_VALUES[k] = v


##### Data processing #####
def read_callback(sender, read_value):                   # This function is called on notification
#   print("read_value: "read_value)
    read_value = struct.unpack('<4H', read_value)        # Convert bytesarray readed into bytes (for each line). '<' shows reading direction.
    id_value = read_value[0]                             # ID value of the byte sent
    timer_value = round(read_value[1] / 10**3, 1)        # Timer value in milliseconds
    temperature_value = read_value[2] / 10               # Temperature value
    v0 = N0/D0 * read_value[3] - X0                      # v0 is the voltage readout
    i = -v0 * N1/D1                                      # Current
    cg = i/N2                                            # Glucose concentration
# See ec-Flex quick-start document for more information.

    print("ID: ", id_value, "| Timer: ", timer_value, "s ", "| Temperature: ", temperature_value, "°F ", "| Glucose concentration: ", round(cg, 3), "mMol")
    update_value(id=id_value, timer=timer_value, temperature=temperature_value, glucose_concentration=cg)
    conn.execute("insert into ecFlex_data values (?, ?, ?, ?)", (id_value, timer_value, temperature_value, cg))
    conn.commit()
    return id_value, timer_value, temperature_value, cg


##### Bluetooth scanner #####
async def main(mac_addr: str):
    global D0, N0, X0, D1, N1, N2

    device = await BleakScanner.find_device_by_address(mac_addr, timeout=10.0)      # Scan BLE and try to find the ec-Flex during 10 secondes
    if not device:
        raise BleakError(f"The device with address {mac_addr} could not be found.")

    async with BleakClient(device) as client:  

        await client.start_notify(handle17, read_callback)       # Activate notification for the handle / characteristic 17. Call read_callback function on notification.


##### Constants acquisition #####
        print("N0: ", struct.unpack('i', bytes(await client.read_gatt_char(handle24))))
        print("D0*100: ", struct.unpack('i', bytes(await client.read_gatt_char(handle21))))
        print("X0*100: ", struct.unpack('i', bytes(await client.read_gatt_char(handle27))))
        print("N1: ", struct.unpack('i', bytes(await client.read_gatt_char(handle96))))
        print("D1*100: ", struct.unpack('i', bytes(await client.read_gatt_char(handle30))))        
        print("N2: ", struct.unpack('i', bytes(await client.read_gatt_char(handle99))))

        N0 = int(struct.unpack('i', bytes(await client.read_gatt_char(handle24)))[0])      # ADC reference voltage
        D0 = int(struct.unpack('i', bytes(await client.read_gatt_char(handle21)))[0])      # ADC resolution
        X0 = int(struct.unpack('i', bytes(await client.read_gatt_char(handle27)))[0])      # Virtual ground level
        N1 = int(struct.unpack('i', bytes(await client.read_gatt_char(handle96)))[0])      # Scale factor for current
        D1 = int(struct.unpack('i', bytes(await client.read_gatt_char(handle30)))[0])      # Current-to-voltage amplification        
        N2 = int(struct.unpack('i', bytes(await client.read_gatt_char(handle99)))[0])      # Scale-factor for non-offset linear conversion

        await asyncio.sleep(1000.0)           # Suspend the task for 1 second
        await client.stop_notify(handle17)    # Stop wainting for a notification on the handle / characteristic 17.


#### main ####
if __name__ == "__main__":
    print("Start bluetooth scanning")
    Thread(target=run_tcp_server, args=(MULTIPROCES_VALUES,)).start()   # Allow to have shared memory
    asyncio.run(main(mac_addr))                                         # Execute the coroutine and return the result

