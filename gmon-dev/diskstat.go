package main

import (
	"fmt"
	"io/ioutil"
	"strconv"
	"strings"
	"time"
)

type statIO struct {
	Name        string
	ReadSector  uint64
	WriteSector uint64
	ReadBytes   uint64
	WriteBytes  uint64
}

const (
	procPath string = "/proc/diskstats"
)

func getDiskstat() (stat []statIO) {
	stat = []statIO{}

	fData, err := ioutil.ReadFile(procPath)

	if err != nil {
		fmt.Println("failed to open", procPath)
		return nil
	}

	strData := string(fData)

	lines := strings.Split(strData, "\n")

	for _, line := range lines {
		if line == "" {
			continue
		}

		fields := strings.Fields(line)
		if fields[3] == "0" {
			continue
		}

		temp_stat := statIO{}
		temp_stat.Name = fields[2]
		temp_stat.ReadSector, _ = strconv.ParseUint(fields[5], 10, 64)
		temp_stat.WriteSector, _ = strconv.ParseUint(fields[9], 10, 64)
		temp_stat.ReadBytes = temp_stat.ReadSector * 512   //Sector to bytes
		temp_stat.WriteBytes = temp_stat.WriteSector * 512 //Sector to bytes

		stat = append(stat, temp_stat)
	}

	return stat
}

func diskstat() {
	fmt.Println("I am from disk stat")
	var r1, r2, w1, w2 uint64

	stat1 := getDiskstat()
	for _, v := range stat1 {
		fmt.Println("read", v.ReadBytes, "write", v.WriteBytes)

		r1 += v.ReadBytes
		w1 += v.WriteBytes
	}
	fmt.Println("read", r1, "write", w1)
	fmt.Printf("\n\n")

	time.Sleep(3 * time.Second)

	stat2 := getDiskstat()
	for _, v1 := range stat2 {
		fmt.Println("read", v1.ReadBytes, "write", v1.WriteBytes)

		r2 += v1.ReadBytes
		w2 += v1.WriteBytes
	}
	fmt.Println("read", r2, "write", w2)

	fmt.Println((r2-r1)/1024, "kb/3s Read")
	fmt.Println((w2-w1)/1024, "kb/3s Write")
}
