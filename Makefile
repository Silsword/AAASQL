CURR_DIR = $(shell pwd)

build: fs-module/bin/fs_module intermediate-module/target/release/intemediate-module aaasql

fs-module/bin/fs_module:
	cd fs-module; \
	$(MAKE); \
	cd ..

intermediate-module/target/release/intemediate-module:
	cd intermediate-module; \
	cargo build --release; \
	cd ..

aaasql:
	chmod u+x interface-module/main.py
	ln -sf $(CURR_DIR)/interface-module/main.py $(CURR_DIR)/aaasql
