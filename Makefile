.PHONY: build test run
build:
	cmake -S . -B build -G Ninja
	cmake --build build
	npx tsc --

test: build
	ctest --test-dir build --output-on-failure
	python3 -m unittest discover -s test -p 'test_*.py'
	npm test --silent

run: build
	python3 server/app.py
