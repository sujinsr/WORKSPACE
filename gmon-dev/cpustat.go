package main

import (
	"fmt"
	"io/ioutil"
	"strings"
	"strconv"
	"time"
	ui "github.com/gizak/termui"
	tm "github.com/nsf/termbox-go"
)

type Stat struct {
	AllStat CpuStat
	SepStats []CpuStat
}

type CpuStat struct {
	CpuNo	string
	User	uint64
	System	uint64
	Wait	uint64
	Idle	uint64
}

var numCpu int

func (x *Stat) printSepStst(){
     for _,cpu := range x.SepStats {
         fmt.Printf("%s %d %d %d %d\n", cpu.CpuNo, cpu.User, cpu.System, cpu.Wait, cpu.Idle)
     }
}

func (s *Stat) changePercentage() {
	for in,_ := range s.SepStats {
		s.SepStats[in].User = s.SepStats[in].User * 100 / s.AllStat.User
		s.SepStats[in].System = s.SepStats[in].System * 100 / s.AllStat.System
		s.SepStats[in].Wait = s.SepStats[in].Wait * 100 / s.AllStat.Wait
		s.SepStats[in].Idle = s.SepStats[in].Idle * 100 / s.AllStat.Idle
	}
}
	

func getstat(path string) (*Stat, error) {
	var stat Stat = Stat{}
	filedata, err := ioutil.ReadFile(path)
	if err != nil {
		return nil, err
	}

	str_data := string(filedata)
	lines := strings.Split(str_data, "\n")

	for i, line := range lines {
		fields := strings.Fields(line)
		if len(fields) == 0 {
			continue
		}

		if fields[0][:3] == "cpu" {
			var cpustat CpuStat
			cpustat.CpuNo 		= fields[0]
			cpustat.User, _ 	= strconv.ParseUint(fields[1], 10, 64)
			cpustat.System, _ 	= strconv.ParseUint(fields[3], 10, 64)
			cpustat.Wait, _ 	= strconv.ParseUint(fields[5], 10, 64)
			cpustat.Idle, _ 	= strconv.ParseUint(fields[4], 10, 64)
			if i == 0 {
				stat.AllStat = cpustat
				numCpu = 0
			} else {
				stat.SepStats = append(stat.SepStats, cpustat)
				numCpu += 1
			}
		}
	}	
	return &stat, nil
}

func cpustat() {
	fmt.Println("it is a cpustat")
	stats,_ := getstat("/proc/stat")
	fmt.Printf("user - %d sys - %d wailt - %d idle - %d\n", stats.AllStat.User, stats.AllStat.System, stats.AllStat.Wait, stats.AllStat.Idle)
	stats.printSepStst()
	stats.changePercentage()
	stats.printSepStst()
	
	fmt.Printf("Number of cput : %d", numCpu)

	err := ui.Init()
	if err != nil {
        panic(err)
	}
	defer ui.Close()
	ui.UseTheme("helloworld")
	
	data := []int{0, 0, 0, 0}
	bc := make([]*ui.BarChart, 4)
	for i := range bc {
		bc[i] = ui.NewBarChart()
		bclabels := []string{"Usr", "Sys", "Wait", "Idle"}
		bc[i].Border.Label = "CPU"
		bc[i].Data = data
		bc[i].Width = 50
		bc[i].Height = 25
		bc[i].DataLabels = bclabels
		bc[i].TextColor = ui.ColorGreen
		bc[i].BarColor = ui.ColorRed
		bc[i].NumColor = ui.ColorYellow
		bc[i].BarGap = 5
		bc[i].BarWidth = 5
	}

	evt := ui.EventCh()
	var moncpu int = 0
	for {
		select {
			case e := <-evt:
				if e.Type == ui.EventKey && e.Ch == 'q' {
				return
			}
			default:
				stats,_ := getstat("/proc/stat")
				stats.changePercentage()
				data[0] = (int)(stats.SepStats[moncpu].User)
				data[1] = (int)(stats.SepStats[moncpu].System)
				data[2] = (int)(stats.SepStats[moncpu].Wait)
				data[3] = (int)(stats.SepStats[moncpu].Idle)
				bc[0].Data = data
				ui.Render(bc[moncpu])
				time.Sleep(time.Second)
		}
	}
	ui.Render(bc[1])
	tm.PollEvent()
}

