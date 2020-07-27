# Weather-station
Wiring BME280 Sensor to ESP8266 NodeMCU<\br>
Connections are fairly simple. Start by connecting VIN pin to the 3.3V output on the <\br>
ESP8266 NodeMCU and connect GND to ground. Next, <\br>
Connect the SCL pin to the I2C clock D1 pin on your ESP8266 and <\br>
connect the SDA pin to the I2C data D2 pin on your ESP8266.<\br>
nodemcu    neo6m<\br>
5v          vcc<\br>
gnd          gnd<\br>
rx           tx<\br>
tx           rx<\br>
