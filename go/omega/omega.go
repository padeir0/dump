package main

import "fmt"

type Mtype func(Mtype)

func M(f Mtype) {
	f(f)
	fmt.Println("M")
}

func nothing(f Mtype) {
	fmt.Println("nothing")
}

func main() {
	// M(nothing)
	M(M)
}
