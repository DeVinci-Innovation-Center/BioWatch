# BioWatch
The BioWatch is a smartwatch prototyping for developing wearable biosensors and real-time data visualization. This electronic project aims at **facilitating the integration (or wireless connection) in a smartwatch of innovative wearable sensors**. The BioWatch allows rapid implementation of minimally invasive electrochemical biosensors. 

<p align="center">
  <img src=https://github.com/DeVinci-Innovation-Center/BioWatch/blob/main/images/bioWatch-V1.0.png?raw=true "BioWatch V1.0">
</p>

***

# System overview

<p align="center">
  <img src=https://github.com/DeVinci-Innovation-Center/BioWatch/blob/main/images/BioWatch-V1-V2-schemes.png?raw=true "BioWatch V1 and V2 overview">
</p>

# Requierments

To build the BioWatch you need the following components:
* A [CG9A01 round LCD screen](https://www.kubii.fr/ecrans-supports/3242-ecran-rond-lcd-1-28-pouces-3272496305625.html),
* An [ESP8266 WeMos D1 mini](https://www.amazon.fr/ESP8266-ESP-12F-D%C3%A9veloppement-NodeMCU-Compatible/dp/B093G72SHN/ref=sr_1_2?__mk_fr_FR=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=3EZYZ6R68PT6Z&keywords=wemos%2Bd1%2Bmini&qid=1677507885&s=electronics&sprefix=wemos%2Bd1%2Bmini%2Celectronics%2C98&sr=1-2&th=1),
* A [battery shield](https://www.amazon.fr/AZDelivery-Batterie-lithium-Arduino-incluant/dp/B07XG817P8/ref=sr_1_1?__mk_fr_FR=%C3%85M%C3%85%C5%BD%C3%95%C3%91&crid=QAPOVML7V5FP&keywords=wemos+d1+mini+battery+shield&qid=1677508193&s=electronics&sprefix=wemos+d1+mini+battery+shield%2Celectronics%2C97&sr=1-1-catcorr) for WeMos D1 mini,
* A 3.7V 250mAh battery ref [LP502030](https://www.amazon.fr/EEMB-Batterie-Rechargeable-Navigation-Enregistreur/dp/B08FD3V6TF).
  
# Quickstart

**1. Download and 3D-print the [watch case](https://github.com/DeVinci-Innovation-Center/BioWatch/tree/main/hardware) of your choice.** 

*Version 1.0 includes the battery in the case, while V1.1 provides for the battery to be integrated in the bracelet.*

**2. Assembled the shield with the WeMos. Weld the GC9A01 using wires with the following dimensions:**
<p align="center">
  <img src=https://github.com/DeVinci-Innovation-Center/BioWatch/blob/main/images/CG9A01-to-WeMos.jpeg?raw=true "Assembling the GC9A01 with the WeMos">
</p>

**3. Upload a code in the [graphic_design folder](https://github.com/DeVinci-Innovation-Center/BioWatch/tree/main/ecflex-to-biowatch_wireless_communication/biowatch_client/graphic_design) to program the GC9A01 driver. [print_graph-and_time](https://github.com/DeVinci-Innovation-Center/BioWatch/tree/main/ecflex-to-biowatch_wireless_communication/biowatch_client/graphic_design/print_graph_and_time) is the functional interface to print sensor data.**

**4. Insert the charged battery into the JST port of the shield and carefully insert the assembly into the case.**

**5. Close the case with the lid and add a standard watchband.**


***

**1. Download the project.** 

**2. In in the [get_ecflex_charac.py](https://github.com/DeVinci-Innovation-Center/Smartwatch/blob/main/get_ecflex_charac.py) script:**
* Enter the MAC address of the ec-Flex device.
* Run the code.
* Recover the addresses of handles 17, 21, 24, 27, 30, 96, and 99 in the vendor service. 

**3. In the [server.py](https://github.com/DeVinci-Innovation-Center/Biosensor-to-smartwatch_wireless_communication/blob/main/biosensor/server.py) script:**
* Define the port to use.

**4. In the [get_ecflex_data.py](https://github.com/DeVinci-Innovation-Center/Smartwatch/blob/main/get_ecflex_data.py) script:**
* Enter the handles addresses.
* Fill the access path of the database.db and schema.sql files.
* Run the code.

**5. In the [wifi_client.ino](https://github.com/DeVinci-Innovation-Center/Biosensor-to-smartwatch_wireless_communication/blob/main/smartwatch/wifi_client/wifi_client.ino) script:**
* Define your network SSID and password.
* Enter your domain.
* Define the port to use.
* Run the code.

# Biosensor-to-smartwatch wireless communication
This project includes a wireless communication solution between an ec-Flex from [Zimmer&Peacock](https://www.zimmerpeacocktech.com/products/) and a homemade smartwatch. Find the Quickstart to connect and configure an ecFlex to the BioWatch on the from [Biosensor-to-smartwatch_wireless_communication GitHub page](https://github.com/DeVinci-Innovation-Center/Biosensor-to-smartwatch_wireless_communication), and [a tutorial to buid a wearable glucose sensor connected to the BioWatch](https://dvic.devinci.fr/tutorial/glucose-biosensor). 


# Project advancement & Future works

- [x] Write an Arduino script using the GFX library that displays time, glucose concentration, and temperature (numerical values) on the GC9A01 screen.
- [x] Write an Arduino script using the GFX library that displays a curve representing the glucose concentration evolution on the GC9A01 screen.
- [x] Assemble the BioWatch V1.0.
- [x] Minimize the size of the BioWatch by assembling the BioWatch V1.1 with the battery in the bracelet. 
- [x] Connect the ec-Flex to the BioWatch.
- [x] Design the BioWatch interface. Print time, date, sensor value and history.
- [ ] Design the BioWatch V2 PCB.
- [ ] Integrate a modular pulse sensor to the BioWatch V2 and read the data in real-time.


<p align="center">
  <img src=https://github.com/DeVinci-Innovation-Center/BioWatch/blob/main/images/BioWatch-photo-white-box-profil.png?raw=true>
</p>