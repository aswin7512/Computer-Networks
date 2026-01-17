### Algorithm: UDP Server Implementation

**Step 1: Start**
Begin the program execution.

**Step 2: Declare Variables**
Initialize necessary variables:

* `sockfd` (integer file descriptor).
* `buffer` (array to store incoming messages).
* `server_addr`, `client_addr` (structures for IP/Port info).
* `client_addr_len` (size of the client address structure).

**Step 3: Create Socket**

* Call `socket()` with `AF_INET` (IPv4) and `SOCK_DGRAM` (UDP).
* **Check:** If the result is < 0, print "Socket creation failed" and **Exit**.

**Step 4: Configure Server Address**

* Clear the `server_addr` structure memory using `memset`.
* Set family to `AF_INET`.
* Set IP address to `INADDR_ANY` (accept data from any interface).
* Set Port to `12345` (convert to network byte order using `htons`).

**Step 5: Bind Socket**

* Call `bind()` to associate `sockfd` with the configured IP and Port.
* **Check:** If `bind` returns < 0, print "Bind failed", close socket, and **Exit**.
* Print "UDP Server listening...".

**Step 6: Communication Loop (Repeat indefinitely)**

1. **Receive Data:** Call `recvfrom()` to read data.
* *Note:* This function waits for a packet and stores the sender's details in `client_addr`.
* **Check:** If bytes received < 0, print error and **Continue** to next iteration.


2. **Process Data:** Null-terminate the received `buffer` string.
3. **Check Exit Condition:**
* **If** buffer contains "exit": Print "Shutting down" and **Break** the loop.


4. **Display Data:** Print the message received from the client.
5. **Get Input:** Prompt server user for a response and read using `fgets`.
6. **Send Data:** Call `sendto()` to transmit the response back to the specific `client_addr` captured in step 6.1.

**Step 7: Close Socket**

* Call `close(sockfd)` to release resources.

**Step 8: Stop**
End the program.
