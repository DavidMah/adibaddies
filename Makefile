port := $(shell arduino-cli board list | grep "Arduino Uno" | awk '{ print $$1 }')

install:
	arduino-cli core update-index
	arduino-cli core install arduino:avr

# Example: make upload led_strip_demo
upload:
	echo "Uploading for sketch: $(SKETCH)"
	cd $(SKETCH) && arduino-cli compile --fqbn arduino:avr:uno
	cd $(SKETCH) && arduino-cli upload --port $(port) --fqbn arduino:avr:uno
