#!/bin/bash

RED='\x1b[91m'
GREEN='\x1b[92m'
YELLOW='\x1b[93m'
BLUE='\x1b[94m'
MAGENTA='\x1b[95m'
CYAN='\x1b[96m'
WHITE='\x1b[97m'
NC='\x1b[0m'  # No Color

color_print() {
	local color="$1"
		local message="$2"
		echo -e "${color}${message}${NC}"
}

color_print_value() {
	local color_value="$1"
		local message="$2"
		echo -e "\x1b[38;5;${color_value};1m${message}${NC}"
}

color_print_rgb() {
	local r="$1"
		local g="$2"
		local b="$3"
		local style="$4"
		local message="$5"

		local color_code="38;2;${r};${g};${b}"

	case "$style" in
		'B') color_code+=";1" ;;
		'N') color_code+=";22" ;;
		'I') color_code+=";3" ;;
		'U') color_code+=";4" ;;
		*) echo "Unknown style: $style" ;;
		esac

			echo -e "\x1b[${color_code}m${message}${NC}"
}

color_print_rgb_bg() {
    local r="$1"
    local g="$2"
    local b="$3"
    local styles="$4"
    local message="$5"

    local color_code="48;2;${r};${g};${b}"

    case "$styles" in
        'B') color_code+=";1" ;;
        'N') color_code+=";22" ;;
        'I') color_code+=";3" ;;
        'U') color_code+=";4" ;;
        'BU' | 'UB') color_code+=";1;4" ;;  # Combine bold and underline
        *) echo "Unknown style: $styles" ;;
    esac

    echo -e "\x1b[${color_code}m${message}${NC}"
}

test_values() {
	for i in {1..256}; do
		color_print_value $i "color ${i}"
			done
}

#color_print_rgb 0 0 255 N "$(color_print_rgb_bg 255 0 0 B 'Blue Bold text on red backgorund')"

