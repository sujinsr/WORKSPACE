package main

import (
	"fmt"
	"net/http"
	"html/template"
	"syscall"
)

type Disk struct {
    Total   uint64
    Free    uint64
    Used    uint64
}


func readDisk(path string) (*Disk, error) {
    fstat := syscall.Statfs_t{}
    err := syscall.Statfs(path, &fstat)
    if err != nil {
        return nil, err
    }
    
    disk := Disk{}
    disk.Total = (fstat.Blocks * uint64(fstat.Bsize)) / (1024 * 1024) 
    disk.Free = (fstat.Bfree * uint64(fstat.Bsize)) / (1024 * 1024)
    disk.Used = disk.Total - disk.Free
    return &disk, nil
}

/*func renderTemplate(w http.ResponseWriter, tmplHtml string, disk Disk) {
	t,_ := template.ParseFiles(tmplHtml);
	str := "fdafdas"
	t.Execute(w, str);
}*/

func mainHandler(w http.ResponseWriter, r *http.Request) {
	t,_ := template.ParseFiles("main.html");
	str := "executeMessage"
	t.Execute(w, str);
	fmt.Println("main handler");
}

func memoryHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("memory handler")

	disk, err := readDisk("/")
    if err != nil {
        fmt.Println("failed to read memory info")
    } else {
        fmt.Println(disk.Total)
        fmt.Println(disk.Free)
        fmt.Println(disk.Used)
    }
    t, _ := template.ParseFiles("memory.html")
    
    t.Execute(w, *disk)

}

func cpuinfoHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("CPUinfo handler");
	//srenderTemplate(w, "memory.html");
	fmt.Fprintf(w, "cpu hanler dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd");
}

func main() {
	fmt.Println("Listening.....");
	http.HandleFunc("/", mainHandler);
	http.HandleFunc("/mem", memoryHandler);
	http.HandleFunc("/cpu", cpuinfoHandler);
	http.ListenAndServe(":9999", nil);
}


