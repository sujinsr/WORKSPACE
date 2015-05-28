package main

import (
	"bufio"
	"fmt"
	"net"
	"os"
	//"runtime"
)

func errorCheck(err error, errStr string) {
	if err != nil {
		fmt.Println(errStr)
		os.Exit(-1)
	}
}

func clientSender(conn net.Conn) {
	reader := bufio.NewReader(os.Stdin)
	for {
		message, _ := reader.ReadBytes('\n')
		fmt.Println("From Server >>", message)
		conn.Write(message[0 : len(message)-1])
	}
}

func clientReceiver(conn net.Conn) {
	message := make([]byte, 1024)
	for {
		_, err := conn.Read(message)
		errorCheck(err, "Read error")
		fmt.Println(">>", string(message))
	}
}

func main() {

	netlisten, err := net.Listen("tcp", "127.0.0.1:20099")
	errorCheck(err, "Failed to listen.")
	defer netlisten.Close()
	for {
		fmt.Println("Wait for client.")
		conn, err := netlisten.Accept()
		errorCheck(err, "Accept Failed")

		fmt.Println("Client connected.")
		go clientReceiver(conn)
		go clientSender(conn)
	}

}
