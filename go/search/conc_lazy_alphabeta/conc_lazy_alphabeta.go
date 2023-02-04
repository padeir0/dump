package conc_lazy_alphabeta

import (
	"fmt"
	. "search/common"
	"sync"
	"time"
)

func Run(breadth, depth int, eval Evaluator) {
	fmt.Println("Concurrent Lazy Alpha-Beta ------")
	start := time.Now()
	startNode := genNode()

	outcome := ConcAlphaBeta(startNode, breadth, depth, true, eval)

	fmt.Printf("\tTime: %v\n", time.Since(start))
	fmt.Printf("\tOutcome: %0.2f\n", outcome)
	fmt.Println()
}

var minusInf float64 = -(1 << 16)
var plusInf float64 = (1 << 16)

func ConcAlphaBeta(n *Node, breadth, depth int, isMax bool, eval Evaluator) float64 {
	if breadth == 0 {
		return 0
	}
	if breadth == 1 {
		return alphaBeta(n, breadth, depth, minusInf, plusInf, isMax, eval)
	}
	// if we have multiple, we set the alpha, then paralelize
	leaf := genNode()
	n.AddLeaf(leaf)
	alpha := alphaBeta(leaf, breadth, depth-1, minusInf, plusInf, !isMax, eval)

	var wg sync.WaitGroup
	for i := 1; i < breadth; i++ {
		wg.Add(1)
		leaf := genNode()
		n.AddLeaf(leaf)
		go func() {
			defer wg.Done()
			alphaBeta(leaf, breadth, depth-1, alpha, plusInf, !isMax, eval)
		}()
	}

	wg.Wait()

	return best(n, isMax)
}

func best(root *Node, isMax bool) float64 {
	if isMax {
		maxEval := minusInf
		for _, leaf := range root.Leaves {
			if leaf.Score > maxEval {
				maxEval = leaf.Score
			}
		}
		root.Score = maxEval
		return maxEval
	}
	minEval := plusInf
	for _, leaf := range root.Leaves {
		if leaf.Score < minEval {
			minEval = leaf.Score
		}
	}
	root.Score = minEval
	return minEval
}

func alphaBeta(n *Node, breadth, depth int, alpha, beta float64, IsMax bool, eval Evaluator) float64 {
	if depth == 0 {
		n.Score = eval(n)
		return n.Score
	}
	if IsMax {
		maxEval := minusInf
		for i := 0; i < breadth; i++ {
			leaf := genNode()
			n.AddLeaf(leaf)

			score := alphaBeta(leaf, breadth, depth-1, alpha, beta, false, eval)
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
	for i := 0; i < breadth; i++ {
		leaf := genNode()
		n.AddLeaf(leaf)

		score := alphaBeta(leaf, breadth, depth-1, alpha, beta, true, eval)
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

func genNode() *Node {
	return &Node{Leaves: []*Node{}}
}