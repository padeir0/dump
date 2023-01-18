package main

import (
	"fmt"
)

type Colour int

type Vertex int

type Edge struct {
	A Vertex
	B Vertex
}

type Graph struct {
	Vertexes  []Vertex
	Adjacency []Edge
}

type Colouring map[Vertex]Colour

func (this Colouring) String() string {
	inverse := map[Colour][]Vertex{}
	for v, c := range this {
		_, ok := inverse[c]
		if ok {
			inverse[c] = append(inverse[c], v)
		} else {
			inverse[c] = []Vertex{v}
		}
	}
	output := ""
	for c, v := range inverse {
		output += fmt.Sprintf("%v: %v;\n", c, v)
	}
	return output
}

type ColourSet map[Colour]struct{}

func (this ColourSet) Add(c Colour) {
	this[c] = struct{}{}
}

func GreedyColouring(g *Graph, numberOfColours Colour) Colouring {
	if numberOfColours <= 0 {
		return nil
	}
	colouring := Colouring{}
	for _, v := range g.Vertexes {
		c := findMinColour(findNeighbourColours(g, colouring, v), numberOfColours)
		if c == nil {
			return nil
		}
		colouring[v] = *c
	}
	return colouring
}

//                                                       *Colour because Go doesn't have optionals :)
func findMinColour(cs ColourSet, numberOfColours Colour) *Colour {
	for i := Colour(0); i < numberOfColours; i++ {
		_, ok := cs[i]
		if !ok {
			return &i
		}
	}
	return nil
}

func findNeighbourColours(g *Graph, c Colouring, v Vertex) ColourSet {
	colourSet := ColourSet{}
	for _, adj := range g.Adjacency {
		if adj.A == v {
			colour, ok := c[adj.B]
			if ok {
				colourSet.Add(colour)
			}
		}
		if adj.B == v {
			colour, ok := c[adj.A]
			if ok {
				colourSet.Add(colour)
			}
		}
	}
	return colourSet
}

func main() {
	g := MakeGraph()
	numClrs := Colour(8)
	clr := GreedyColouring(g, numClrs)
	if clr == nil {
		fmt.Printf("Can't colour this graph with %v colours\n", numClrs)
		return
	}
	fmt.Println(clr)
}

func MakeGraph() *Graph {
	a := Vertex(0)
	b := Vertex(1)
	c := Vertex(2)
	d := Vertex(3)
	e := Vertex(4)
	f := Vertex(5)
	return &Graph{
		Vertexes:  []Vertex{a, b, c, d, e, f},
		Adjacency: []Edge{{a, b}, {a, c}, {b, c}, {b, d}, {e, f}},
	}
}
