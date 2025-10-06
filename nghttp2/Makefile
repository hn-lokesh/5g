# Makefile to clone and build nghttp2 stack

# Git repo and install location
NGHTTP2_REPO ?= https://github.com/nghttp2/nghttp2.git
NGHTTP2_DIR ?= nghttp2
PREFIX ?= /usr/local
NGHTTP2_TAG ?= v1.67.1

# Compiler flags for using installed nghttp2 headers and libraries
CFLAGS=-I$(PREFIX)/include
LDFLAGS=-L$(PREFIX)/lib -lnghttp2
TAG_EXISTS=$(shell git -C $(NGHTTP2_DIR) tag -l $(NGHTTP2_TAG))

# SUDO variable allows overriding sudo usage (set SUDO= for non-root installs)
SUDO ?= sudo

# Default target: build everything
all: nghttp2_install

# Step 1: Clone nghttp2 repo if not already present
$(NGHTTP2_DIR):
	@echo "======>>> CLONING NGHTTP2 REPO AND TAG TO ${NGHTTP2_TAG} <<<======"
	git clone $(NGHTTP2_REPO) $(NGHTTP2_DIR) && \
	cd ${NGHTTP2_DIR} && \
	git fetch --tags && \
	if git rev-parse --verify "refs/tags/$(NGHTTP2_TAG)" > /dev/null 2>&1; then \
		git checkout -B nghttp2-$(NGHTTP2_TAG) $(NGHTTP2_TAG); \
	else \
		echo "Tag $(NGHTTP2_TAG) not found. Aborting."; \
		exit 1; \
	fi

# Step 2: Build nghttp2 from source
nghttp2_build: $(NGHTTP2_DIR)
	cd $(NGHTTP2_DIR) && autoreconf -i && \
	./configure --enable-lib-only --prefix=$(PREFIX) && \
	make -j$(nproc)
		cd $(NGHTTP2_DIR) && sudo make install
	# The following command refreshes the dynamic linker cache and requires root privileges.
	# If installing to a user directory (non-root), you can skip this step.
		sudo ldconfig  # Refresh dynamic linker cache
nghttp2_install: nghttp2_build
	cd $(NGHTTP2_DIR) && $(SUDO) make install
	$(SUDO) ldconfig  # Refresh dynamic linker cache

# Clean everything: binaries and source tree
clean:
	rm -rf $(NGHTTP2_DIR)

# Declare targets that aren't real files
.PHONY: all clean nghttp2_build nghttp2_install
