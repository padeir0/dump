package main

import (
	"fmt"
)

type Node struct {
	Parens  string
	Leaves  []*Node

	Id string
}

func NewNode(parens string, id string) *Node {
	return &Node {
		Parens: parens,
		Leaves: []*Node{},
		Id: id,
	}
}

func (n *Node) CountParens() int {
	counter := 0
	for _, r := range n.Parens {
		if r == '(' {
			counter++
		} else if r == ')' {
			counter--
		}
	}
	return counter
}

func IsBalanced(n *Node) bool {
	return _isBalanced(n, []*Node{}, 0)
}

func _isBalanced(n *Node, visited []*Node, counter int) bool {
	counter += n.CountParens()
	if counter < 0 { // dangling ')'
		return false
	}
	
	if HasVisited(visited, n) {
		x := counter
		for i := len(visited)-1; i >= 0; i-- { // backtrack
			v := visited[i]
			x -= v.CountParens()
			if v == n {
				break
			}
		}
		if x != counter { // divergent loop
			return false
		}
		return true
	}
	
	visited = append(visited, n)
	top := len(visited)
	
	for _, v := range n.Leaves {
		if !_isBalanced(v, visited[0:top], counter) {
			return false
		}
	}
	return true
}

func HasVisited(visited []*Node, n *Node) bool {
	for _, v := range visited {
		if n == v {
			return true
		}
	}
	return false
}

func Link(a *Node, b *Node) {
	a.Leaves = append(a.Leaves, b)
}

type Case func() *Node

func TrueCase0() *Node {
	a := NewNode("(" , "a")
	b := NewNode("(" , "b")
	c := NewNode("))", "c")
	d := NewNode("(" , "d")
	e := NewNode(")", "e")
	Link(a, b)
	Link(b, c)
	Link(c, d)
	Link(d, b)
	Link(d, e)
	return a
}

func TrueCase1() *Node {
	a := NewNode("(", "a")
	b := NewNode(")", "b")
	c := NewNode("(", "c")
	d := NewNode(")", "d")
	Link(a, b)
	Link(b, c)
	Link(c, b)
	Link(c, d)
	return a
}

func TrueCase2() *Node {
	a := NewNode("(", "a")
	b := NewNode(")(", "b")
	c := NewNode(")", "c")
	Link(a, b)
	Link(b, b)
	Link(b, c)
	return a
}

func TrueCase3() *Node {
	a := NewNode("(" , "a")
	b := NewNode("(" , "b")
	c := NewNode("))", "c")
	d := NewNode("(" , "d")
	e := NewNode("(" , "e")
	f := NewNode(")" , "f")
	Link(a, b)
	Link(b, c)
	Link(c, d)
	Link(d, b)
	Link(d, e)
	Link(d, f)
	Link(e, c)
	return a
}

func TrueCase4() *Node {
	a := NewNode("(", "a")
	b := NewNode("(", "b")
	c := NewNode(")", "c")
	d := NewNode(")", "d")
	Link(a, d)
	Link(a, b)
	Link(b, c)
	Link(c, d)
	return a
}

func FalseCase0() *Node {
	return NewNode(")", "a")
}

func FalseCase1() *Node {
	a := NewNode("(", "a")
	Link(a, a)
	return a
}

func FalseCase2() *Node {
	a := NewNode("(", "a")
	b := NewNode(")", "b")
	c := NewNode("(", "c")
	d := NewNode(")", "d")
	Link(a, b)
	Link(b, c)
	Link(b, b)
	Link(c, d)
	return a
}

func FalseCase3() *Node {
	a := NewNode("(", "a")
	b := NewNode("(", "b")
	c := NewNode(")", "c")
	Link(a, b)
	Link(a, c)
	Link(b, a)
	return a
}

func main() {
	fmt.Println("valid cases:")
	trueCases := []Case{TrueCase0, TrueCase1, TrueCase2, TrueCase3, TrueCase4}
	for i, c := range trueCases {
		ShouldBe(c, true, i)
	}
	
	fmt.Println("invalid cases:")
	falseCases := []Case{FalseCase0, FalseCase1, FalseCase2, FalseCase3}
	for i, c := range falseCases {
		ShouldBe(c, false, i)
	}
}

func ShouldBe(c Case, res bool, i int) {
	if IsBalanced(c()) == res {
		fmt.Println(i, " ok")
	} else {
		fmt.Println(i, " fail")
	}
}
