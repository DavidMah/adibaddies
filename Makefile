# Sadly, --format json does not have as much data in it!
port := $(shell arduino-cli board list --format yaml | yq eval -o json | jq -r '.[] | select(.matchingboards[0].name | index("Arduino")) | .port.address')
fqbn := $(shell arduino-cli board list --format yaml | yq eval -o json | jq -r '.[] | select(.matchingboards[0].name | index("Arduino")) | .matchingboards[0].fqbn')


install:
	@if [ "$(uname)" = "Linux" ]; then\
		sudo snap install arduino-cli yq; \
		sudo apt update && apt install -y jq astyle \
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

serial:
	# Make sure to exit when done. The Serial port cannot be used concurrently, which includes uploading sketches
	sudo putty -serial -sercfg 9600,8,n,1,N $(port) &

compile:
	cd $(SKETCH) && \
		arduino-cli compile \
			--fqbn $(fqbn) \
			$(shell find lib -type d -maxdepth 1 -exec echo "--libraries ../{}" \;) \
			$(shell find lib_vendored -type d -maxdepth 1 -exec echo "--libraries ../{}" \;) \
			$(COMPILE_ARGS)

# Example:
# 	SKETCH=led_strip_demo make upload
upload: compile
	# Uploading for sketch: $(SKETCH)
	cd $(SKETCH) && sudo arduino-cli upload --port $(port) --fqbn $(fqbn)

upload_and_serial: upload serial

push_github: format
	git add . -A
	git commit -am "EDITED: $(shell git diff --name-only | tr "\n" ",")"
	git pull origin master --rebase
	git push origin master

format:
	astyle lib/*/*/*.cpp
	astyle */*.ino
