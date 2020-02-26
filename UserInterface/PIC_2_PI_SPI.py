import spidev
import copy
spi=spidev.SpiDev()

# Helper Functions
def setup_spi():
    # Initialize SPI
    spi.open(0,1)
    spi.max_speed_hz = 5000000
    spi.mode = 1

setup_spi()
def send(data):
    dummy_byte = [0x00]
    spi.xfer(data)
    r = spi.xfer(dummy_byte)
    receved = copy.copy(r)
    print(receved)
    return receved

def main():
    setup_spi()

if __name__=="__main__":
    main()
