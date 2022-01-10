port := $(shell arduino-cli board list | grep "Arduino Uno" | awk '{ print $$1 }')

install:
	brew update && brew install arduino-cli
	arduino-cli core update-index
	arduino-cli core install arduino:avr

# Example: make upload led_strip_demo
upload:
	echo "Uploading for sketch: $(SKETCH)"
	cd $(SKETCH) && arduino-cli compile --fqbn arduino:avr:uno
	cd $(SKETCH) && arduino-cli upload --port $(port) --fqbn arduino:avr:uno

push_github:
	git commit -am "moar stuff"
	git pull origin master --rebase
	git push origin master

port:
	echo $(port)

serial:
	sudo cu -s 9600 -l /dev/cu.usbmodem142401
