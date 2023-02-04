package main

import (
	"math/rand"
	//	"time"

	. "search/common"

	"search/conc_lazy_alphabeta"
	"search/eager_alphabeta"
	"search/lazy_alphabeta"
	"search/minimax"
)

func main() {
	e := fourthousand

	index = 0
	minimax.Run(40, 4, e)

	index = 0
	eager_alphabeta.Run(40, 4, e)

	index = 0
	lazy_alphabeta.Run(40, 5, e)

	index = 0
	conc_lazy_alphabeta.Run(40, 5, e)
}

var scores = [128]float64{}

func init() {
	//a := time.Now().UnixNano()
	rand.Seed(1)
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
