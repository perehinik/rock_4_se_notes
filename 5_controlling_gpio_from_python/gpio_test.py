from periphery import GPIO
import time

GPIO4_A4=GPIO(132,"out")
GPIO4_A5=GPIO(133,"out")
GPIO4_A6=GPIO(134,"out")

while True:
    try:         
        GPIO4_A4.write(True)
        GPIO4_A5.write(False)
        GPIO4_A6.write(False)
        print("GPIO4_A4")
        time.sleep(1)

        GPIO4_A4.write(False)
        GPIO4_A5.write(True)
        GPIO4_A6.write(False)
        print("GPIO4_A5")
        time.sleep(1)

        GPIO4_A4.write(False)
        GPIO4_A5.write(False)
        GPIO4_A6.write(True)
        print("GPIO4_A6")
        time.sleep(1)

    except KeyboardInterrupt:
        GPIO4_A4.write(False)
        GPIO4_A5.write(False)
        GPIO4_A6.write(False)
        break
    except IOError:
        print("error")
        
GPIO4_A4.close()
GPIO4_A5.close()
GPIO4_A6.close()

