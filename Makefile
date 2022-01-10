port := $(shell arduino-cli board list | grep "Arduino Uno" | awk '{ print $$1 }')

install:
	brew update && brew install arduino-cli
	arduino-cli core update-index
	arduino-cli core install arduino:avr

port:
	echo $(port)

# Example: make upload led_strip_demo
upload:
	echo "Uploading for sketch: $(SKETCH)"
	cd $(SKETCH) && arduino-cli compile --fqbn arduino:avr:uno
	cd $(SKETCH) && arduino-cli upload --port $(port) --fqbn arduino:avr:uno

serial:
	echo "Exit by typing: ~."
	sudo cu -s 9600 -l /dev/cu.usbmodem142401

upload_and_serial: upload serial

push_github:
	git add . -A
	git commit -am "moar stuff"
	git pull origin master --rebase
	git push origin master
