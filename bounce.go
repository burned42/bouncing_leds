package main

import (
	"fmt"
	"math"
	"math/rand"
	"time"
)

const td float64 = 0.05
const ballCount int = 5
const maxH float64 = 50

const g float64 = 9.8
const a float64 = -g * td

type ball struct {
	v float64
	h float64
	c rune
}

var balls = make([]ball, ballCount)

func main() {
	rand.Seed(time.Now().UTC().UnixNano())

	var maxV float64 = math.Sqrt(maxH * 2.0 * g)

	var runes = []rune("ABCDEFGHIJKLMNOPQRSTUVWXYZ")

	for i := 0; i < ballCount; i++ {
		balls[i] = ball{
			v: maxV * float64(rand.Intn(51)+50) / 100,
			h: 0,
			c: runes[rand.Intn(len(runes))],
		}
	}

	for {
		for i, ball := range balls {
			var v = ball.v
			var h = ball.h

			h = math.Max(
				0,
				(h + (v * td) + (0.5 * a * td * td)),
			)

			if h == 0 {
				v = -0.75 * v
			}

			v += a

			if int(v) == 0 && int(h) == 0 {
				v = maxV * float64(rand.Intn(11)+90) / 100
			}

			balls[i].v = v
			balls[i].h = h
		}

		fmt.Print("\033[H\033[2J")
		for h := int(maxH); h > 0; h-- {
			for _, ball := range balls {
				if int(ball.h) == h {
					fmt.Print(string(ball.c) + " ")
				}
			}
			fmt.Println()
		}

		time.Sleep(time.Second / 50)
	}
}
