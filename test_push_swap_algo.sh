#!/bin/bash

# Colors for better readability
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
MAGENTA='\033[0;35m'
CYAN='\033[0;36m'
NC='\033[0m' # No Color

# Function to check for duplicates
has_duplicates() {
    local nums=($1)
    local sorted=($(printf "%s\n" "${nums[@]}" | sort -n))
    
    for ((i=1; i<${#sorted[@]}; i++)); do
        if [[ "${sorted[i]}" == "${sorted[i-1]}" ]]; then
            return 0
        fi
    done
    return 1
}

# Test function to check if solution is correct and count operations
test_push_swap() {
    local input="$1"
    local test_description="$2"
    local expect_error=${3:-0}

    if [ -n "$test_description" ]; then
        echo -e "${BLUE}Test: ${CYAN}${test_description}${NC}"
        echo -e "Input: '$input'"
    else
        echo -e "${BLUE}Testing: ${CYAN}'$input'${NC}"
    fi

    # Use a temporary file for the input
    echo "$input" > input.tmp

    # Execute push_swap and checker with the input file
    ./push_swap $(cat input.tmp) > output.tmp 2> error.tmp
    local exit_code=$?
    local output=$(cat output.tmp)
    local errors=$(cat error.tmp)

    # Pass the exact same input to checker
    local result=$(./push_swap $(cat input.tmp) | ./checker_linux $(cat input.tmp) 2>/dev/null)
    
    if [ $expect_error -eq 1 ]; then
        if [[ "$errors" == *"Error"* ]] || [ $exit_code -ne 0 ]; then
            echo -e "${GREEN}✓ Correct (Error detected as expected)${NC}"
            rm -f input.tmp output.tmp error.tmp
            return 0
        else
            echo -e "${RED}✗ Failed (Should have detected error)${NC}"
            rm -f input.tmp output.tmp error.tmp
            return 1
        fi
    else
        local ops_count=$(cat output.tmp | wc -l | tr -d ' ')

        if [ "$result" == "OK" ]; then
            echo -e "${GREEN}✓ Correct${NC} (Operations: $ops_count)"
            rm -f input.tmp output.tmp error.tmp
            return 0
        else
            echo -e "${RED}✗ Failed${NC}"
            echo -e "Checker result: ${result:-'(empty)'}"
            echo -e "Program output: $output"
            echo -e "Error output: $errors"
            rm -f input.tmp output.tmp error.tmp
            return 1
        fi
    fi
}

test_special_cases() {
    echo -e "\n${MAGENTA}====== TESTING SPECIAL CASES ======${NC}"
    
    # Fonction interne pour afficher de manière concise
    run_test() {
        local description="$1"
        local input="$2"
        local expect_error=${3:-0}
        
        echo -en "${BLUE}Test: ${CYAN}${description}${NC} - "
        
        if [ $expect_error -eq 1 ]; then
            ./push_swap $input >/dev/null 2>&1
            if [ $? -ne 0 ] || grep -q "Error" <<< "$(./push_swap $input 2>&1)"; then
                echo -e "${GREEN}✓ Error detected as expected${NC}"
            else
                echo -e "${RED}✗ Should have detected error${NC}"
            fi
        else
            result=$(./push_swap $input | ./checker_linux $input 2>/dev/null)
            ops_count=$(./push_swap $input | wc -l | tr -d ' ')
            
            if [ "$result" == "OK" ]; then
                echo -e "${GREEN}✓ OK${NC} (Ops: ${ops_count})"
            else
                echo -e "${RED}✗ KO${NC}"
            fi
        fi
    }
    
    # Tests avec caractères spéciaux
    run_test "Numbers with signs" "1 +2 -3" 0
    run_test "Multiple signs" "1 ++2 --3" 1
    run_test "Trailing plus" "1 2 3 +" 1
    run_test "Trailing minus" "1 2 3 -" 1
    run_test "Just a plus" "+" 1
    run_test "Just a minus" "-" 1
    
    # Tests avec espaces bizarres
    run_test "Extra spaces" "  1   2  3  " 0
    run_test "Japanese space" "1 2　3" 1
    
    # Tests avec caractères non-numériques
    run_test "Letter in middle" "1 2a 3" 1
    run_test "Special character" "1 2 3!" 1
    run_test "Accented character" "1 2 3é" 1
    run_test "Fraction character" "1 2 3½" 1
    
    # Tests avec combinaisons bizarres
    run_test "Mixed signs" "1 -+2 +-3" 1
    run_test "Leading zeros" "1 000000002 3" 0
    run_test "Huge number" "1 99999999999999999999 3" 1
    run_test "Huge negative" "1 -99999999999999999999 3" 1
    
    # Tests avec séparateurs bizarres
    run_test "Comma separated" "1,2,3" 1
    run_test "Semicolon separated" "1;2;3" 1
    run_test "Newline separated" "1\n2\n3" 1
}

# Function to generate unique random numbers including negatives
generate_random_numbers() {
    local size=$1
    local numbers=()
    local attempts=0
    local max_attempts=100
    
    while [ ${#numbers[@]} -lt $size ] && [ $attempts -lt $max_attempts ]; do
        local num=$((RANDOM % 20001 - 10000))
        
        # Check if number already exists in array
        if ! [[ " ${numbers[@]} " =~ " ${num} " ]]; then
            numbers+=($num)
        else
            ((attempts++))
        fi
    done
    
    if [ ${#numbers[@]} -ne $size ]; then
        echo -e "${RED}Error: Couldn't generate $size unique numbers${NC}" >&2
        return 1
    fi
    
    echo "${numbers[@]}"
}

# Enhanced performance testing function
test_performance() {
    local size=$1
    local iterations=$2
    local total_ops=0
    local max_ops=0
    local min_ops=999999
    local failed=0
    
    echo -e "\n${YELLOW}Performance test with ${CYAN}$size${YELLOW} random numbers (${CYAN}$iterations${YELLOW} iterations)${NC}"
    
    for ((i=1; i<=$iterations; i++)); do
        # Génération plus efficace des nombres
        local nums
        if [ "$size" -eq 1 ]; then
            nums=$((RANDOM % 20001 - 10000))  # Simple nombre aléatoire pour size=1
        else
            nums=$(generate_random_numbers $size)
            if [ $? -ne 0 ]; then
                echo -e "${RED}Error generating numbers${NC}"
                return 1
            fi
        fi
        
        local ops=$(./push_swap $nums | wc -l | tr -d ' ')
        total_ops=$((total_ops + ops))
        
        [ $ops -gt $max_ops ] && max_ops=$ops
        [ $ops -lt $min_ops ] && min_ops=$ops
        
        local result=$(./push_swap $nums | ./checker_linux $nums)
        if [ "$result" != "OK" ]; then
            echo -e "\n${RED}✗ Failed${NC} for random test $i: $nums"
            failed=$((failed + 1))
        fi
        
        # Affichage de progression plus robuste
        if [ "$iterations" -le 10 ] || [ $((i % 10)) -eq 0 ] || [ "$i" -eq "$iterations" ]; then
            echo -ne "\rTesting: $i/$iterations (Avg: $((total_ops/i))) (Min: $min_ops, Max: $max_ops)    "
        fi
    done
    
    if [ $failed -gt 0 ]; then
        echo -e "\n${RED}✗ $failed/$iterations tests failed${NC}"
    else
        echo -e "\n${GREEN}✓ All tests passed${NC}"
    fi
    
    echo -e "Average operations: $((total_ops / iterations))"
    echo -e "Min operations: $min_ops"
    echo -e "Max operations: $max_ops"
    
    check_recommended_limits $size $((total_ops / iterations)) $max_ops
}

# Function to check against recommended operation limits
check_recommended_limits() {
    local size=$1
    local avg=$2
    local max=$3
    
    local recommended_max=0
    case $size in
        3) recommended_max=3 ;;
        5) recommended_max=12 ;;
        100) recommended_max=700 ;;
        500) recommended_max=5500 ;;
        *) return ;;
    esac
    
    if [ $size -le 5 ] || [ $size -eq 100 ] || [ $size -eq 500 ]; then
        if [ $max -gt $recommended_max ]; then
            echo -e "${YELLOW}Warning: Max operations ($max) exceeds recommended limit ($recommended_max) for size $size${NC}"
        fi
    fi
}

# Function to test small sets exhaustively
test_small_sets() {
    local size=$1
    local total=0
    local passed=0
    local failed_tests=()
    
    echo -e "\n${YELLOW}Testing all permutations of size ${CYAN}$size${NC}"
    
    # Using Python to generate permutations
    while IFS= read -r perm; do
        total=$((total + 1))
        if ! test_push_swap "$perm" "" 0 >/dev/null; then
            failed_tests+=("$perm")
        else
            passed=$((passed + 1))
        fi
        
        # Afficher la progression
        if [ $((total % 50)) -eq 0 ] || [ "$total" -eq "$(python3 -c "from math import factorial; print(factorial($size))")" ]; then
            echo -ne "\rTested: $total, Passed: $passed/$total"
        fi
    done < <(python3 -c "
from itertools import permutations
for p in permutations(range(1, $size+1)):
    print(' '.join(map(str, p)))
")
    
    # Afficher le résumé
    echo -e "\n${GREEN}✓ $passed/$total tests passed${NC}"
    
    # Afficher les échecs s'il y en a
    if [ ${#failed_tests[@]} -gt 0 ]; then
        echo -e "\n${RED}✗ Failed tests (${#failed_tests[@]}):${NC}"
        for test in "${failed_tests[@]}"; do
            echo -e "  ${YELLOW}Input:${NC} '$test'"
            # Ré-exécuter le test pour afficher les détails
            test_push_swap "$test" "Failed case" 0
        done
    fi
}
# Function to analyze solution patterns
analyze_patterns() {
    echo -e "\n${YELLOW}Analyzing solution patterns...${NC}"
    
    # Testing various scenarios including negatives
    for set in "1" "2 1" "3 2 1" "-1 -2 -3" "1 -2 3 -4 5" "5 1 4 -2 3" "100 -200 300 -400 500"; do
        result=$(./push_swap $set | ./checker_linux $set 2>/dev/null)
        ops_count=$(./push_swap $set | wc -l | tr -d ' ')
        
        if [ "$result" == "OK" ]; then
            echo -e "${CYAN}Input:${NC} $set ${GREEN}✓ OK${NC} (Ops: $ops_count)"
        else
            echo -e "${CYAN}Input:${NC} $set ${RED}✗ KO${NC}"
            echo -e "${YELLOW}Solution attempt:${NC}"
            ./push_swap $set | cat
            echo -e "${YELLOW}Expected result:${NC} sorted list"
        fi
    done
}

# Main test routine
echo -e "${MAGENTA}======= PUSH_SWAP ALGORITHM TESTING =======${NC}"

# Basic tests
echo -e "\n${YELLOW}Standard tests${NC}"
test_push_swap "" "Empty input" 1
test_push_swap "42" "Single number" 0
test_push_swap "1 2 3 4 5" "Already sorted" 0
test_push_swap "5 4 3 2 1" "Reverse sorted" 0
test_push_swap "-1 -2 -3 -4 -5" "Negative numbers" 0
test_push_swap "1 -2 3 -4 5" "Mixed signs" 0

# Test des cas spéciaux
test_special_cases

# Small sets tests
test_small_sets 3
test_small_sets 4

# Performance tests with different sizes and iterations
echo -e "\n${YELLOW}Performance tests${NC}"
test_performance 1 100
test_performance 2 100
test_performance 3 100
test_performance 4 100
test_performance 5 75
test_performance 10 50
test_performance 50 20
test_performance 100 10
test_performance 200 5
test_performance 500 3
test_performance 1000 2

# Solution analysis
analyze_patterns

echo -e "\n${MAGENTA}======= ALGORITHM TESTING COMPLETE =======${NC}"