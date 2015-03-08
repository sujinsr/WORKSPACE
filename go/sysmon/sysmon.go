package main

import (
	"fmt"
	"net/http"
	"html/template"
)

func renderTemplate(w http.ResponseWriter, tmplHtml string) {
	t,_ := template.ParseFiles(tmplHtml);
	str := "fdafdas"
	t.Execute(w, str);
}

func mainHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("main handler");
	renderTemplate(w, "main.html");
}

func memoryHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("memory handler");
	fmt.Fprintf(w, "memory dataddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd");
}

func cpuinfoHandler(w http.ResponseWriter, r *http.Request) {
	fmt.Println("CPUinfo handler");
	fmt.Fprintf(w, "cpu hanler dddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddd");
}

func main() {
	fmt.Println("Listening.....");
	http.HandleFunc("/", mainHandler);
	http.HandleFunc("/mem", memoryHandler);
	http.HandleFunc("/cpu", cpuinfoHandler);
	http.ListenAndServe(":9999", nil);
}

