package main

import (
	"fmt"
	ui "github.com/gizak/termui"
	tm "github.com/nsf/termbox-go"
)

func memstat() {
	fmt.Println("This is memstat")

	err := ui.Init()
	if err!= nil {
		panic(err)
	}
	defer ui.Close() 
	
	ui.UseTheme("helloworld")
	
	ram_gs := make([]*ui.Gauge, 3)
	for i := range ram_gs {
		ram_gs[i] = ui.NewGauge()
		ram_gs[i].Height = 2
		ram_gs[i].HasBorder = false
		ram_gs[i].Percent = (i+1) * 10
		ram_gs[i].PaddingBottom = 1
		ram_gs[i].BarColor = ui.ColorRed
	}

	ram_ls := ui.NewList()
	ram_ls.HasBorder = false
	ram_ls.Items = []string{
		"TOTAL RAM MEMORY",
		"",
		"FREE RAM MEMORY",
		"",
		"USED RAM MEMORY",
	}
	ram_ls.Height = 5

	swap_gs := make([]*ui.Gauge, 3)
	for i := range swap_gs {
		swap_gs[i] = ui.NewGauge()
		swap_gs[i].Height = 2
		swap_gs[i].HasBorder = false
		swap_gs[i].Percent = (i+1) * 10
		swap_gs[i].PaddingBottom = 1
		swap_gs[i].BarColor = ui.ColorRed
	}

	swap_ls := ui.NewList()
	swap_ls.HasBorder = false
	swap_ls.Items = []string{
	    "TOTAL SWAP MEMMORY",
	    "",
		"FREE SWAP MEMORY",
	   	"",
	 	"USED SWAP MEMORY",
	}		
	swap_ls.Height = 5


	// build layout
	ui.Body.AddRows(
		ui.NewRow(
			ui.NewCol(4, 0, ram_ls),
			ui.NewCol(6, 0, ram_gs[0], ram_gs[1], ram_gs[2])),
		ui.NewRow(
			ui.NewCol(4, 0, swap_ls),
			ui.NewCol(6, 0, swap_gs[0], swap_gs[1], swap_gs[2])))

	// calculate layout
	ui.Body.Align()

	draw := func() {
		ui.Render(ui.Body)
	}
	

	for {
		for _, g := range ram_gs {
			g.Percent = (g.Percent + 3) % 100
		}
		tm.PollEvent()
		draw()
	}
}
