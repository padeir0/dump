package main

import (
	"fmt"
	"math/rand"
	"os"
	"runtime/pprof"
	"time"

	. "search/common"

	"search/conc_lazy_alphabeta"
	//"search/eager_alphabeta"
	//"search/lazy_alphabeta"
	//"search/minimax"
)

func main() {
	file := fmt.Sprintf("profile_%v_%v_%v",
		time.Now().Hour(),
		time.Now().Minute(),
		time.Now().Second())
	f, err := os.Create(file)
	if err != nil {
		panic(err)
	}
	pprof.StartCPUProfile(f)
	defer pprof.StopCPUProfile()

	e := onehundred

	//index = 0
	//minimax.Run(40, 4, e)

	//index = 0
	//eager_alphabeta.Run(40, 4, e)

	//index = 0
	//lazy_alphabeta.Run(40, 7, e)

	for i := 0; i < 10; i++ {
		gen()
		index = 0
		conc_lazy_alphabeta.Run(40, 7, e)
	}
}

var scores = [128]float64{}

func gen() {
	a := time.Now().UnixNano()
	rand.Seed(a)
	for i := range scores {
		scores[i] = float64(rand.Int31n(10)-5) + rand.Float64()
	}
}

var index = 0

func e(n *Node) float64 {
	//score := float64(rand.Int31n(10)-5) + rand.Float64()
	score := scores[index%len(scores)]
	index++
	return score
}

func onehundred(n *Node) float64 {
	score := scores[index%len(scores)]
	index++
	for i := 0; i < 100; i++ {
		score += float64(int(score) ^ int(score))
	}
	return score
}

func fourthousand(n *Node) float64 {
	score := scores[index%len(scores)]
	index++
	for i := 0; i < 64*64; i++ {
		score += float64(int(score) ^ int(score))
	}
	return score
}
