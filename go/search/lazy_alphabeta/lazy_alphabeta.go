package lazy_alphabeta

import (
	"fmt"
	. "search/common"
	"time"
)

func Run(breadth, depth int, eval Evaluator) {
	fmt.Println("Lazy Alpha-Beta ------")
	start := time.Now()
	startNode := &Node{}

	outcome := AlphaBeta(startNode, breadth, depth, minusInf, plusInf, true, eval)

	fmt.Printf("\tTime: %v\n", time.Since(start))
	fmt.Printf("\tOutcome: %0.2f\n", outcome)
	fmt.Println()
}

var minusInf float64 = -(1 << 16)
var plusInf float64 = (1 << 16)

func AlphaBeta(n *Node, breadth, depth int, alpha, beta float64, IsMax bool, eval Evaluator) float64 {
	if depth == 0 {
		n.Score = eval(n)
		return n.Score
	}
	if IsMax {
		maxEval := minusInf
		for i := 0; i < breadth; i++ {
			leaf := &Node{}

			score := AlphaBeta(leaf, breadth, depth-1, alpha, beta, false, eval)
			if score > maxEval {
				n.AddLeaf(breadth, leaf)
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
	for i := 0; i < breadth; i++ {
		leaf := &Node{}

		score := AlphaBeta(leaf, breadth, depth-1, alpha, beta, true, eval)
		if score < minEval {
			n.AddLeaf(breadth, leaf)
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
