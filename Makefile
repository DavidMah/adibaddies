port := $(shell arduino-cli board list | grep "Arduino Uno" | awk '{ print $$1 }')

install:
	@if [ "$(uname)" = "Linux" ]; then\
		sudo snap install arduino-cli;\
	fi
	@if [ "$(uname)" = "Darwin" ]; then \
		brew update && brew install arduino-cli \
	fi
	arduino-cli core update-index
	arduino-cli core install arduino:avr

port:
	echo $(port)

# Example: make upload led_strip_demo
upload:
	echo "Uploading for sketch: $(SKETCH)"
	cd $(SKETCH) && arduino-cli compile --fqbn arduino:avr:uno --libraries ../lib/FastLED-3.5.0 --libraries ../lib/Servo-1.1.8
	cd $(SKETCH) && sudo arduino-cli upload --port $(port) --fqbn arduino:avr:uno

serial:
	echo "Make sure to exit when done. The Serial port cannot be used concurrently, which includes uploading sketches"
	sudo putty $(port) -serial -sercfg 9600,8,n,1,N &

upload_and_serial: upload serial

push_github:
	git add . -A
	git commit -am "moar stuff"
	git pull origin master --rebase
	git push origin master
