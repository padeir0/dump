package minimax

import (
	"fmt"
	. "search/common"
	"time"
)

func Run(breadth, depth int, eval Evaluator) {
	fmt.Println("Minimax ----------")
	start := time.Now()
	tree := MakeTree(breadth, depth) // (breadth ^ depth) nodes

	outcome := MiniMax(tree, depth, true, eval)

	fmt.Printf("\tTime: %v\n", time.Since(start))
	fmt.Printf("\tOutcome: %0.2f\n", outcome)
	fmt.Println()
}

var minusInf float64 = -(1 << 16)
var plusInf float64 = (1 << 16)

func MiniMax(n *Node, depth int, IsMax bool, eval Evaluator) float64 {
	if depth == 0 || len(n.Leaves) == 0 {
		n.Score = eval(n)
		return n.Score
	}
	if IsMax {
		maxEval := minusInf
		for _, leaf := range n.Leaves {
			score := MiniMax(leaf, depth-1, false, eval)
			if score > maxEval {
				maxEval = score
			}
		}
		n.Score = maxEval
		return maxEval
	}
	minEval := plusInf
	for _, leaf := range n.Leaves {
		score := MiniMax(leaf, depth-1, true, eval)
		if score < minEval {
			minEval = score
		}
	}
	n.Score = minEval
	return minEval
}
