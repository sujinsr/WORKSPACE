package main

import "github.com/gizak/termui"
import "github.com/nsf/termbox-go"

func main() {
	err := termui.Init()
	if err != nil {
		panic(err)
	}
	defer termui.Close()

	termui.UseTheme("helloworld")

	bc := termui.NewBarChart()
	data := []int{25, 50, 75, 100}
	bclabels := []string{"Usr", "Sys", "Wait", "Idle"}
	bc.Border.Label = "Bar Chart"
	bc.Data = data
	bc.Width = 50
	bc.Height = 15
	bc.DataLabels = bclabels
	bc.TextColor = termui.ColorGreen
	bc.BarColor = termui.ColorRed
	bc.NumColor = termui.ColorYellow
	bc.BarGap	= 5
	bc.BarWidth = 5

	termui.Render(bc)

	termbox.PollEvent()
}
