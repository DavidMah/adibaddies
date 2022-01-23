# Sadly, --format json does not have as much data in it!
port := $(shell arduino-cli board list --format yaml | yq eval -o json | jq -r '.[] | select(.matchingboards[0].name | index("Arduino")) | .port.address')
fqbn := $(shell arduino-cli board list --format yaml | yq eval -o json | jq -r '.[] | select(.matchingboards[0].name | index("Arduino")) | .matchingboards[0].fqbn')


install:
	@if [ "$(uname)" = "Linux" ]; then\
		sudo snap install arduino-cli yq; \
		sudo apt update && apt install -y jq \
	fi
	@if [ "$(uname)" = "Darwin" ]; then \
		brew update && brew install arduino-cli; \
		brew install jq yq
	fi
	arduino-cli core update-index
	arduino-cli core install arduino:avr
	arduino-cli core install arduino:sam

port:
	echo $(port)

# Example: make upload led_strip_demo
upload:
	echo "Uploading for sketch: $(SKETCH)"
	cd $(SKETCH) && arduino-cli compile --fqbn $(fqbn) --libraries ../lib/FastLED-3.5.0 --libraries ../lib/Servo-1.1.8 $(COMPILE_ARGS)
	cd $(SKETCH) && sudo arduino-cli upload --port $(port) --fqbn $(fqbn)

serial:
	echo "Make sure to exit when done. The Serial port cannot be used concurrently, which includes uploading sketches"
	sudo putty $(port) -serial -sercfg 9600,8,n,1,N &

upload_and_serial: upload serial

push_github:
	git add . -A
	git commit -am "moar stuff"
	git pull origin master --rebase
	git push origin master

format:
	sudo apt install -y astyle
