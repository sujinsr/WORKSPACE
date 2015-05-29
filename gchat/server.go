package main

import (
	"container/list"
	"fmt"
	"net"
	"os"
)

type ClientProp struct {
	Name string
	Conn net.Conn
}

func errorCheck(err error, errStr string) {
	if err != nil {
		fmt.Println(errStr)
		os.Exit(-1)
	}
}

func clientReceiver(conn net.Conn, ch_msg chan string) {
	message := make([]byte, 1024)
	for {
		_, err := conn.Read(message)
		errorCheck(err, "Read error")
		ch_msg <- string(message)
		//fmt.Println(">>", string(message))
	}
}

func clientHandler(conn net.Conn, ch_msg chan string, l *list.List) {
	/* get name */
	newclient := &ClientProp{"TestName", conn}

	go clientReceiver(conn, ch_msg)
	l.PushBack(*newclient)
}

func allClientSend(ch_msg chan string, l *list.List) {
	for {
		msg := <-ch_msg
		for val := l.Front(); val != nil; val = val.Next() {
			client := val.Value.(ClientProp)
			//fmt.Println(client.Name)
			client.Conn.Write([]byte(msg))
		}
	}
}

func main() {
	client_list := list.New()
	ch_msg := make(chan string)

	netlisten, err := net.Listen("tcp", "127.0.0.1:20099")
	errorCheck(err, "Failed to listen.")
	defer netlisten.Close()

	go allClientSend(ch_msg, client_list)

	for {
		fmt.Println("Wait for client.")
		conn, err := netlisten.Accept()
		errorCheck(err, "Accept Failed")

		fmt.Println("Client connected.")
		go clientHandler(conn, ch_msg, client_list)
	}

}
