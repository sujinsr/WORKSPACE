package main

import (
	"fmt"
)

func main() {
	var choice int8

	fmt.Println("1 - Memory Information")
	fmt.Println("2 - CPU Stat\n")
	fmt.Println("Enter the Option ?")

	fmt.Scanf("%d", &choice)

	switch choice {
		case 1: memstat()
		case 2: cpustat()
		default: fmt.Println("Unknow choice")
	}
}
