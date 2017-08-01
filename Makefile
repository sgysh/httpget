TARGETS := httpget
TEST_OPTIONS :=
TEST_OPTIONS += -d yes

.PHONY : all clean test

all: $(TARGETS)

httpget: httpget.cc url.cc http.cc
	g++-4.9 -std=c++11 -o $@ $^

test: unit_test
	./$< $(TEST_OPTIONS)
	rm -v $<

unit_test: unit_test.cc url.cc http.cc
	g++-4.9 -std=c++11 -o $@ $^

clean:
	rm -v $(TARGETS)

