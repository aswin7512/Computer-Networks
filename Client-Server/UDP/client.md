### Algorithm: UDP Client Implementation

**Step 1: Start**
Begin the program execution.

**Step 2: Declare Variables**
Initialize necessary variables:

* `sockfd` (integer file descriptor).
* `buffer` (character array for messages).
* `server_addr` (structure to hold the server's destination info).
* `addr_len` (size of the address structure).

**Step 3: Create Socket**

* Call `socket()` with `AF_INET` (IPv4) and `SOCK_DGRAM` (UDP).
* **Check:** If the result is < 0, print "Socket creation failed" and **Exit**.

**Step 4: Configure Server Address**

* Clear the `server_addr` memory.
* Set family to `AF_INET`.
* Set Port to `12345` (convert to network byte order using `htons`).
* Set IP address to `127.0.0.1` (localhost) using `inet_addr`.

**Step 5: Communication Loop (Repeat indefinitely)**

1. **Input:** Prompt the user ("Enter message") and read input using `fgets`.
2. **Format:** Remove the trailing newline character from the input.
3. **Send Data:** Call `sendto()` to transmit the `buffer` to the address specified in `server_addr`.
4. **Check Exit Condition:**
* **If** buffer contains "exit": Print "Exiting client" and **Break** the loop.


5. **Receive Data:** Call `recvfrom()` to wait for a response from the server.
* *Note:* In this code, the source address arguments are `NULL`, meaning the client accepts the packet without storing the sender's details separately (it assumes the response is from the server it just messaged).


6. **Display:** Null-terminate the received data and print "Server response".

**Step 6: Close Socket**

* Call `close(sockfd)` to release system resources.

**Step 7: Stop**
End the program.
