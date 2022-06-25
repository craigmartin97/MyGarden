import Adafruit_DHT
import time
import smbus

SLAVE_ADDRESS = 0x08 # I2C Address of Arduino 1

# Create the I2C bus
I2Cbus = smbus.SMBus(1)

# Set sensor type options are DHT11 or DHT22. Using DHT11 for this project
tempAndHumiditySensor = Adafruit_DHT.DHT11

# Set the GPIO the DHT11 is connected to
tempAndHumidityGpio = 17
 
# Reading the DHT11 is very sensitive to timings and occasionally
# the Pi might fail to get a valid reading. So check if readings are valid.
while True:
    print(I2Cbus.read_byte(SLAVE_ADDRESS))
    # Use read_retry method. This will retry up to 15 times to
    # get a sensor reading (waiting 2 seconds between each retry).
    humidity, temperature = Adafruit_DHT.read_retry(tempAndHumiditySensor, tempAndHumidityGpio)
    if humidity is not None and temperature is not None:
        print('Temp={0:0.1f}*C  Humidity={1:0.1f}%'.format(temperature, humidity))
    time.sleep(1)