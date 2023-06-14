package main

import "fmt"

func main() {
	for i := 0; i < 5; i++ {
		fmt.Printf("fact(%v) = %v\n", i, fact(i))
	}
	for i := 0; i < 5; i++ {
		fmt.Printf("factIter(%v) = %v\n", i, factIter(i))
	}
}

func fact(n int) int {
	if n <= 0 {
		return 1
	} else {
		return n * fact(n-1)
	}
}

func factIter(n int) int {
	acumulator := 1
	for n > 0 {
		acumulator *= n
		n--
	}
	return acumulator
}
