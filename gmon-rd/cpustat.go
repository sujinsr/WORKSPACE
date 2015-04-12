package main

import (
	"fmt"
	//ui "github.com/gizak/termui"
	//tm "github.com/nsf/termbox-go"
	"io/ioutil"
	"strconv"
	"strings"
	"time"
)

type Stat struct {
	AllStat  CpuStat
	SepStats []CpuStat
}

type CpuStat struct {
	CpuNo  string
	Total  uint64
	User   uint64
	System uint64
	Wait   uint64
	Idle   uint64
}

var numCpu int

func (x *Stat) printSepStst() {
	for _, cpu := range x.SepStats {
		fmt.Printf("%s %d %d %d %d -> %d\n", cpu.CpuNo, cpu.User, cpu.System, cpu.Wait, cpu.Idle, cpu.Total)
	}
}

func (s *Stat) changePercentage() {
	for in, _ := range s.SepStats {
		s.SepStats[in].User = s.SepStats[in].User * 100 / s.SepStats[in].Total
		s.SepStats[in].System = s.SepStats[in].System * 100 / s.SepStats[in].Total
		s.SepStats[in].Wait = s.SepStats[in].Wait * 100 / s.SepStats[in].Total
		s.SepStats[in].Idle = s.SepStats[in].Idle * 100 / s.SepStats[in].Total
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
		numFields := len(fields)
		if len(fields) == 0 {
			continue
		}

		if fields[0][:3] == "cpu" {
			var cpustat CpuStat
			cpustat.CpuNo = fields[0]
			for j := 1; j < numFields; j++ {
				val, _ := strconv.ParseUint(fields[j], 10, 64)
				cpustat.Total += val
				switch j {
				case 1:
					cpustat.User = val
				case 3:
					cpustat.System = val
				case 4:
					cpustat.Idle = val
				case 5:
					cpustat.Wait = val
				}
			}
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
	stats1, _ := getstat("/proc/stat")
	time.Sleep(3 * time.Second)
	stats2, _ := getstat("/proc/stat")

	idleTicks := float64(stats2.AllStat.Idle - stats1.AllStat.Idle)
	totalTicks := float64(stats2.AllStat.Total - stats1.AllStat.Total)
	cpuUsage := 100 * (totalTicks - idleTicks) / totalTicks

	fmt.Printf("Idle - %f\n", cpuUsage)
	fmt.Printf("Number of cput : %d\n", numCpu)
}
