#!/bin/bash

# Couleurs
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
CYAN='\033[0;36m'
MAGENTA='\033[0;35m'
NC='\033[0m'

# Variables
TOTAL_TESTS=0
FAILED_TESTS=0
VALGRIND_OUTPUT_FILE="valgrind_output.tmp"

run_valgrind_test() {
    local input="$1"
    local description="$2"
    
    ((TOTAL_TESTS++))
    
    # Affichage de l'entête du test en couleur
    echo -e "\n${CYAN}=== Test: ${MAGENTA}${description}${CYAN} ===${NC}"
    echo -e "${YELLOW}Input:${NC} ${input}"
    
    # Exécution avec Valgrind
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
             --log-file=${VALGRIND_OUTPUT_FILE} ./push_swap ${input} >/dev/null 2>&1
    
    # Vérifier les erreurs
    if grep -q "ERROR SUMMARY: [1-9]" ${VALGRIND_OUTPUT_FILE} || \
       grep -q "definitely lost: [1-9]" ${VALGRIND_OUTPUT_FILE}; then
        echo -e "${RED}✗ Problems detected${NC}"
        ((FAILED_TESTS++))
        # Afficher la sortie brute de Valgrind
        cat ${VALGRIND_OUTPUT_FILE}
    else
        echo -e "${GREEN}✓ No problems detected${NC}"
        # Afficher quand même le résumé pour confirmation
        grep -E "ERROR SUMMARY|total heap usage|definitely lost" ${VALGRIND_OUTPUT_FILE}
    fi
    
    rm -f ${VALGRIND_OUTPUT_FILE}
}

# Entête des tests
echo -e "${CYAN}======= Memory Tests =======${NC}"

# Tests
run_valgrind_test "1 2 3 4 5" "Already sorted"
run_valgrind_test "5 4 3 2 1" "Reverse sorted"
run_valgrind_test "42" "Single number"
run_valgrind_test "abc" "Non-numeric input"
run_valgrind_test "1 2 3 abc" "Mixed valid/invalid"
run_valgrind_test "1 2 3 3" "Duplicates"
run_valgrind_test "2147483648" "Above INT_MAX"
run_valgrind_test "-2147483649" "Below INT_MIN"
run_valgrind_test "65498491616212316546546546212165465456465465465849846541616546561" "Enormous int"
run_valgrind_test "0" "Zero value"
run_valgrind_test "-0" "Negative zero"
run_valgrind_test "0005" "Leading zeros valid number"
run_valgrind_test "1 2 3 4 5 6 7 8 9 10 11 12" "Medium sorted list"
run_valgrind_test "12 11 10 9 8 7 6 5 4 3 2 1" "Medium reverse sorted"
run_valgrind_test "$(seq 1 100 | tr '\n' ' ')" "Large sorted list" 
run_valgrind_test "$(seq 1 100 | sort -nr | tr '\n' ' ')" "Large reverse sorted"
run_valgrind_test "1 2 3 4 5 6 7 8 9 10 1 2 3 4 5" "Repeated sequence"
run_valgrind_test "1 100 2 99 3 98 4 97 5 96" "Alternating high-low"
run_valgrind_test "5 3 9 1 4 6 8 2 7" "Random medium set"
run_valgrind_test "18446744073709551615" "64-bit unsigned max"
run_valgrind_test "1  2   3    4     5" "Multiple spaces between"
run_valgrind_test " 1 2 3 " "Leading/trailing spaces"
# Test de très grandes listes (attention à la durée)
if [ "$RUN_LONG_TESTS" = "1" ]; then
    run_valgrind_test "$(seq 1 500 | tr '\n' ' ')" "500 elements sorted"
    run_valgrind_test "$(seq 1 500 | sort -nr | tr '\n' ' ')" "500 elements reverse sorted"
fi

# Rapport final
echo -e "\n${CYAN}======= Final Report =======${NC}"
echo -e "Total tests: ${MAGENTA}${TOTAL_TESTS}${NC}"
echo -e "Failed tests: ${RED}${FAILED_TESTS}${NC}"

if [ ${FAILED_TESTS} -eq 0 ]; then
    echo -e "${GREEN}✓ All tests passed successfully${NC}"
else
    echo -e "${RED}✗ Some tests failed - check Valgrind output above${NC}"
fi