package main

import (
	"bufio"
	"fmt"
	"os"
	"runtime/pprof"
	"sort"
)

var data = []line{}
var medianlinesize = 0
var threshold = 0

type EdgeID int
type StrID int

type line struct {
	text  string
	edges []int
	done  bool
}

type pair struct {
	a, b StrID
}

func main() {
	f, err := os.Create("prof.pprof")
	if err != nil {
		fatal(err)
	}
	pprof.StartCPUProfile(f)
	defer pprof.StopCPUProfile()
	getinput()
	threshold = 1 + int(float64(medianlinesize)*float64(25.0/100.0))
	print(medianlinesize, threshold)
	buildgraph()
	c := getclusters()
	for _, cluster := range c {
		fmt.Print("\n")
		for _, edge := range cluster {
			fmt.Println(data[edge.id].text)
		}
	}
}

type edge struct {
	id  StrID
	dis int
}

func getclusters() [][]edge {
	clusters := [][]edge{}

	for pivot, line := range data {
		if line.done {
			continue
		}

		m := map[StrID]int{}
		cluster(StrID(pivot), &m, 0)
		c := make([]edge, len(m))
		i := 0
		for id, dis := range m {
			data[id].done = true
			c[i] = edge{id, dis}
			i++
		}
		clusters = append(clusters, c)
	}
	return clusters
}

func cluster(curr StrID, nodes *map[StrID]int, currDist int) {
	if _, ok := (*nodes)[curr]; ok {
		return
	}
	if data[curr].done {
		return
	}
	(*nodes)[curr] = currDist

	sort.Ints(data[curr].edges)
	for otherID, dis := range data[curr].edges {
		if dis >= threshold {
			break
		}
		cluster(StrID(otherID), nodes, currDist+dis)
	}
}

func buildgraph() {
	done := map[pair]struct{}{}
	for i := range data {
		if data[i].edges == nil {
			data[i].edges = make([]int, len(data))
		}
	}
	print("building graph\n\n")
	for i := range data {
		s1 := StrID(i)
		Bar(i, len(data))
		print("edges for: \n", i)
		for j := range data {
			Bar(j, len(data))
			s2 := StrID(j)
			p := pair{s1, s2}
			if _, ok := done[p]; ok {
				continue
			}
			dis := levdis(0, s1, s2, 0, 0)
			data[i].edges[j] = dis
			data[j].edges[i] = dis
		}
	}
}

func levdis(currDis int, s1, s2 StrID, i, j int) int {
	ls1 := len(data[s1].text[i:])
	ls2 := len(data[s2].text[j:])
	if currDis >= threshold {
		return 1 << 32
	}
	if ls2 == 0 {
		return currDis + ls1
	}
	if ls1 == 0 {
		return currDis + ls2
	}
	if data[s1].text[i] == data[s2].text[j] {
		return levdis(currDis, s1, s2, i+1, j+1)
	}
	return min(
		levdis(currDis+1, s1, s2, i+1, j),
		levdis(currDis+1, s1, s2, i, j+1),
		levdis(currDis+1, s1, s2, i+1, j+1),
	)
}

func min(a ...int) int {
	m := 1 << 31
	for _, item := range a {
		if item < m {
			m = item
		}
	}
	return m
}

func getinput() {
	scanner := bufio.NewScanner(os.Stdin)
	lengthsum := 0
	for scanner.Scan() {
		l := line{
			text:  scanner.Text(),
			edges: nil,
		}
		lengthsum += len(l.text)
		data = append(data, l)
	}
	medianlinesize = lengthsum / len(data)
	if err := scanner.Err(); err != nil {
		fatal(err)
	}
}

func fatal(args ...interface{}) {
	fmt.Fprintln(os.Stderr, args...)
	os.Exit(0)
}

func sq(a int) int {
	return a * a
}

func print(args ...interface{}) {
	fmt.Fprint(os.Stderr, args...)
}

func Bar(processed, total int) {
	bar := makebar(processed, total)
	fmt.Fprintf(os.Stderr, "\033[1A\033[K%v %v / %v                       \n", bar, processed, total)
}

const backgroundGreen = "\u001b[42m"
const reset = "\u001b[0m"

func makebar(processed, total int) string {
	bars := (processed * 20 / total)
	output := "|" + backgroundGreen
	for i := 0; i < bars; i++ {
		output += " "
	}
	output += reset
	for i := bars; i < 20; i++ {
		output += " "
	}
	return output + "|"
}
