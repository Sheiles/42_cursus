#!/bin/bash



RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m'

echo -e "${BLUE}â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•${NC}"
echo -e "${BLUE}  Testing All C++ Modules${NC}"
echo -e "${BLUE}â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•${NC}\n"

TOTAL_TESTS=0
PASSED_TESTS=0
FAILED_TESTS=0

test_exercise() {
	local module=$1
	local exercise=$2
	local dir="CPP_modules/${module}_folder/${module}/${exercise}"

	if [ ! -d "$dir" ]; then
		return
	fi


	if [ $(find "$dir" -name "*.cpp" | wc -l) -eq 0 ]; then
		return
	fi

	TOTAL_TESTS=$((TOTAL_TESTS + 1))

	echo -e "${YELLOW}Testing ${module}/${exercise}...${NC}"
	cd "$dir" || return

	if [ ! -f "Makefile" ]; then
		echo -e "${RED}  âœ— No Makefile${NC}"
		FAILED_TESTS=$((FAILED_TESTS + 1))
		cd - > /dev/null
		return
	fi


	make fclean > /dev/null 2>&1
	if make > /dev/null 2>&1; then
		echo -e "${GREEN}  âœ“ Compilation successful${NC}"
		PASSED_TESTS=$((PASSED_TESTS + 1))
		make fclean > /dev/null 2>&1
	else
		echo -e "${RED}  âœ— Compilation failed${NC}"
		echo -e "${YELLOW}    Running make again to show errors:${NC}"
		make
		FAILED_TESTS=$((FAILED_TESTS + 1))
	fi

	cd - > /dev/null
	echo ""
}


for ex in ex00 ex01 ex02; do
	test_exercise "CPP_module00" "$ex"
done


for ex in ex00 ex01 ex02 ex03 ex04 ex05 ex06; do
	test_exercise "CPP_module01" "$ex"
done


for ex in ex00 ex01 ex02 ex03; do
	test_exercise "CPP_module02" "$ex"
done


for ex in ex00 ex01 ex02 ex03; do
	test_exercise "CPP_module03" "$ex"
done


for ex in ex00 ex01 ex02; do
	test_exercise "CPP_module04" "$ex"
done


echo -e "${BLUE}â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•${NC}"
echo -e "${BLUE}  Test Summary${NC}"
echo -e "${BLUE}â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•â•${NC}"
echo -e "Total tests:   ${TOTAL_TESTS}"
echo -e "${GREEN}Passed:        ${PASSED_TESTS}${NC}"
if [ $FAILED_TESTS -gt 0 ]; then
	echo -e "${RED}Failed:        ${FAILED_TESTS}${NC}"
else
	echo -e "Failed:        0"
fi
echo ""

if [ $FAILED_TESTS -eq 0 ] && [ $TOTAL_TESTS -gt 0 ]; then
	echo -e "${GREEN}ðŸŽ‰ All tests passed!${NC}"
	exit 0
else
	echo -e "${RED}âŒ Some tests failed${NC}"
	exit 1
fi
