package main

import (
	"fmt"
	"io/ioutil"
	"strings"
	"strconv"
	"github.com/gizak/termui"
	"github.com/nsf/termbox-go"
)


type Swapinfo struct {
	Total	uint64
	Used	uint64
	Free	uint64
}

func memstat() {
	fmt.Println("*** At Memstat ***")
	swap_path := "/proc/swaps"	
	
	bs, err := ioutil.ReadFile(swap_path)
	if err != nil {
		fmt.Println("failed to open swap file")
	}

	content := string(bs)
	lines := strings.Split(content, "\n")
	
	var swapinfo Swapinfo
	
	for i,line := range lines{
		if i==0 {
			continue
		}
		subline := strings.Split(line, "\t")
		for j, data := range subline {
			if j==1 {
				r, _ := strconv.Atoi(data)
				swapinfo.Total = (uint64)(r / 1024)
			}
			if j==2 {
				r, _ := strconv.Atoi(data)
				swapinfo.Used = (uint64)(r / 1024)
			}
		}
	}
	swapinfo.Free = swapinfo.Total - swapinfo.Used
	fmt.Println("Total : ", swapinfo.Total, "MB")
	fmt.Println("Used  : ", swapinfo.Used, "MB")
	fmt.Println("Free  : ", swapinfo.Free, "MB")

	err1 := termui.Init()
	if err1 != nil {
		panic(err1)
	}
	defer termui.Close()

	termui.UseTheme("helloworld")

	g0 := termui.NewGauge()
	g0.Percent = 40
	g0.Width = 50
	g0.Height = 3
	g0.Border.Label = "Total Swap Memory in Mega Bytes"
	g0.BarColor = termui.ColorRed
	g0.Border.FgColor = termui.ColorWhite
	g0.Border.LabelFgColor = termui.ColorCyan

	g2 := termui.NewGauge()
	g2.Percent = 60
	g2.Width = 50
	g2.Height = 3
	g2.PercentColor = termui.ColorBlue
	g2.Y = 3
	g2.Border.Label = "Free Swap Memory in Mega Bytes"
	g2.BarColor = termui.ColorYellow
	g2.Border.FgColor = termui.ColorWhite

	g1 := termui.NewGauge()
	g1.Percent = 30
	g1.Width = 50
	g1.Height = 3
	g1.Y = 6
	g1.Border.Label = "Used Swap Memory in Mega Bytes"
	g1.PercentColor = termui.ColorYellow
	g1.BarColor = termui.ColorGreen
	g1.Border.FgColor = termui.ColorWhite
	g1.Border.LabelFgColor = termui.ColorMagenta

	termui.Render(g0, g1, g2)

	termbox.PollEvent()
}

func cpustat() {
	fmt.Println("*** At CPUstat ***")
	cpu_avg := "/proc/loadavg"
	bs, err := ioutil.ReadFile(cpu_avg)
	if err != nil {
		fmt.Println("failed to open ", cpu_avg, " file")
	}
	content := string(bs)
	fmt.Println(content) 

	err1 := termui.Init()
	if err1 != nil {
    	panic(err1)
	}
	defer termui.Close()

	termui.UseTheme("helloworld")

	g0 := termui.NewGauge()
	g0.Percent = 40
	g0.Width = 50
	g0.Height = 3
	g0.Border.Label = "CPU lOAD"
	g0.BarColor = termui.ColorRed
	g0.Border.FgColor = termui.ColorWhite
	g0.Border.LabelFgColor = termui.ColorCyan

	termui.Render(g0)

	termbox.PollEvent()
	
}

func main() {
	var choice int

	fmt.Println("1 - Memory Stat")	
	fmt.Println("2 - CPU Stat")
	fmt.Println("Enter the Option ? ")
	fmt.Scanf("%d", &choice)

	switch choice {
		case 1: memstat()
		case 2: cpustat()
		default: fmt.Println("Unknown choice.")
	}

}
