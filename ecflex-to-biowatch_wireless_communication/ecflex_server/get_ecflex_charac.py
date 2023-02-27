######################################################################
###      A python script to print services and characteristics     ###
######################################################################


import asyncio
import platform
import sys

from bleak import BleakClient, BleakScanner
from bleak.exc import BleakError

mac_addr = "00:35:ff:0b:ae:4c"                            # Mac address of the ec-Flex
vendor_service = "00002d8d-0000-1000-8000-00805f9b34fb"   # Vendor sevice 

async def main(mac_addr: str):

     device = await BleakScanner.find_device_by_address(mac_addr, timeout=10.0)      # Scan BLE and try to find the ec-Flex during 10 secondes
     if not device:
          raise BleakError(f"The device with address {mac_addr} could not be found.")
     async with BleakClient(device) as client:           # Async with allows functioning multiple operations without waiting time.
          svcs = await client.get_services()             # Gets services
          print("Services:")                             
          for service in svcs:
               print(service)                            # Print the different services available
          gap = svcs[vendor_service]                     # GAP = generic attribute protocol
          print("Charac:")
          for c in gap.characteristics:              
               print(c)                                  # Print the different characteristics (handle) available

     await asyncio.sleep(10.0)                           # Suspend the task for 10 seconds
     await client.stop_notify(mac_addr)                  

if __name__ == "__main__":
     print("Start bluetooth scanning")
     asyncio.run(main(sys.argv[1] if len(sys.argv) == 2 else mac_addr))
     









