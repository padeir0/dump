package eager_alphabeta

import (
	"fmt"
	. "search/common"
	"time"
)

func Run(breadth, depth int, eval Evaluator) {
	fmt.Println("Eager Alpha-Beta ----------")

	start := time.Now()
	tree := MakeTree(breadth, depth) // (breadth ^ depth) nodes

	outcome := AlphaBeta(tree, depth, minusInf, plusInf, true, eval)

	fmt.Printf("\tTime: %v\n", time.Since(start))
	fmt.Printf("\tOutcome: %0.2f\n", outcome)
	fmt.Println()
}

var minusInf float64 = -(1 << 16)
var plusInf float64 = (1 << 16)

func AlphaBeta(n *Node, depth int, alpha, beta float64, IsMax bool, eval Evaluator) float64 {
	if depth == 0 || len(n.Leaves) == 0 {
		n.Score = eval(n)
		return n.Score
	}
	if IsMax {
		maxEval := minusInf
		for _, leaf := range n.Leaves {
			score := AlphaBeta(leaf, depth-1, alpha, beta, false, eval)
			if score > maxEval {
				maxEval = score
			}
			if score > alpha {
				alpha = score
			}
			if beta <= alpha {
				break
			}
		}
		n.Score = maxEval
		return maxEval
	}
	minEval := plusInf
	for _, leaf := range n.Leaves {
		score := AlphaBeta(leaf, depth-1, alpha, beta, true, eval)
		if score < minEval {
			minEval = score
		}
		if score < beta {
			beta = score
		}
		if beta <= alpha {
			break
		}
	}
	n.Score = minEval
	return minEval
}
