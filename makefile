all: $(clean)
	$(MAKE) --no-print-directory preprocess
	cp preprocess/output/main.cpp stage1/source/main.cpp
	$(MAKE) --no-print-directory stage1


preprocess:
	$(MAKE) --no-print-directory -C preprocess all

stage1:
	$(MAKE) --no-print-directory -C stageI all

clean:
	$(MAKE) --no-print-directory -C preprocess clean
	$(MAKE) --no-print-directory -C stageI clean

.PHONY: all clean stage1 preprocess