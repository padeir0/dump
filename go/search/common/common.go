package common

import (
	"fmt"
)

type Evaluator func(n *Node) float64

type Node struct {
	Score  float64
	Leaves []*Node
}

func (this *Node) String() string {
	return ast(this, 0)
}

const (
	letterBlack     = "\u001b[30m"
	backgroundGreen = "\u001b[42m"
	backgroundBlue  = "\u001b[44m"
	reset           = "\u001b[0m"
)

func ast(n *Node, depth int) string {
	output := fmt.Sprintf("%.2f", n.Score) + reset + "\n"
	for _, leaf := range n.Leaves {
		output += ident(depth) + ast(leaf, depth+1)
	}
	return output
}

func ident(size int) string {
	output := ""
	for i := 0; i < size+1; i++ {
		output += "    "
	}
	return output
}

func (this *Node) AddLeaf(breadth int, n *Node) {
	if this.Leaves == nil {
		this.Leaves = make([]*Node, breadth/2)[:0]
	}
	this.Leaves = append(this.Leaves, n)
}

func MakeTree(breadth, depth int) *Node {
	output := &Node{Leaves: make([]*Node, breadth)}
	if depth == 0 {
		return output
	}
	for i := 0; i < breadth; i++ {
		n := MakeTree(breadth, depth-1)
		output.Leaves[i] = n
	}
	return output
}
