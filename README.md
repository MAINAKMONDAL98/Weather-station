# Weather-station
Wiring BME280 Sensor to ESP8266 NodeMCU
Connections are fairly simple. Start by connecting VIN pin to the 3.3V output on the 
ESP8266 NodeMCU and connect GND to ground. Next, 
Connect the SCL pin to the I2C clock D1 pin on your ESP8266 and 
connect the SDA pin to the I2C data D2 pin on your ESP8266.
nodemcu    neo6m
5v          vcc
gnd          gnd
rx           tx
tx           rx
