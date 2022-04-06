build: fs-module/bin/fs_module intermediate-module/target/release/intemediate-module

fs-module/bin/fs_module:
	cd fs-module; \
	$(MAKE); \
	cd ..

intermediate-module/target/release/intemediate-module:
	cd intermediate-module;\
	cargo build --release; \
	cd ..
