package main

import (
	"fmt"
	"os"
	"strconv"
	"time"
)

func main() {
	if len(os.Args) < 2 {
		fmt.Println("Usage: timer <time>\nWhere time can be: '<hours> h <min> m <sec> s'")
		fmt.Println("eg: timer 10h25m31s")
		return
	}
	sec := 0
	buff := ""
	n := 0
	for _, c := range os.Args[1] {
		switch c {
		case 'h':
			n, _ = strconv.Atoi(buff)
			n *= 60 * 60
		case 'm':
			n, _ = strconv.Atoi(buff)
			n *= 60
		case 's':
			n, _ = strconv.Atoi(buff)
		default:
			if isNum(c) {
				buff += string(c)
			}
			continue
		}
		sec += n
		buff = ""
	}

	timer(sec)
}

func timer(sec int) {
	s := time.Duration(sec)
	fmt.Print("\033[s")
	finish := time.Now().Add(s * time.Second)
	ticker := time.NewTicker(time.Second)
	defer ticker.Stop()
	done := make(chan bool)

	go func() {
		time.Sleep(s * time.Second)
		done <- true
	}()

	for {
		select {
		case <-done:
			rewrite("TIME IS UP!\n")
			return
		case t := <-ticker.C:
			rewrite(finish.Sub(t).Round(time.Second))
		}
	}
}

func rewrite(args ...interface{}) {
	fmt.Print("\033[u\033[K")
	fmt.Print(args...)
}

func isNum(c rune) bool {
	if c >= '0' && c <= '9' {
		return true
	}
	return false
}