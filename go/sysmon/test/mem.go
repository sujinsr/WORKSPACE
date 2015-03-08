package main

import "fmt"
import "syscall"

type Disk struct {
    total   uint64
    free    uint64
    used    uint64
}

func readDisk(path string) (*Disk, error) {
    fstat := syscall.Statfs_t{}
    err := syscall.Statfs(path, &fstat)
    if err != nil {
        return nil, err
    }
    
    disk := Disk{}
    disk.total = fstat.Blocks * uint64(fstat.Bsize)
    disk.free = fstat.Bfree * uint64(fstat.Bsize)
    disk.used = disk.total - disk.free
    return &disk, nil
}

func main() {
    fmt.Println("hjello")
    disk, err := readDisk("/")
    if err != nil {
        fmt.Println("failed to read memory info")
    } else {
        fmt.Println(disk.total)
        fmt.Println(disk.free)
        fmt.Println(disk.used)
    }
    
    
}   