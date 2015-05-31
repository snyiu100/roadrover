# Shim DLL for logging operations of the serial port #

To monitor the data exchange over the serial port on Windows CE devices:
  1. Download [ShimCom archive](http://code.google.com/p/roadrover/downloads/detail?name=ShimCom.zip).
  1. Unzip to SD-card.
  1. Run appverif.exe on Windows CE device.
  1. Click the "Add..." and add the application(s) you want to monitor.
  1. Click the "Add shim..." and select SimCom.dll.
  1. Select the application in the "Applications" list and check the "COM Logger" in the "Test settings" list.
  1. Start the application by pressing the "Run" or directly from Windows Explorer.
  1. File com\_log.txt should appear in the root folder.

More information (in Russian) is [here](http://progandhack.blogspot.com/2011/08/shim-dll-com.html).