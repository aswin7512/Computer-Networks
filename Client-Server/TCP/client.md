### Algorithm: TCP Client Implementation

**Step 1: Start**
Begin the program execution.

**Step 2: Declare Variables**
Initialize necessary variables:

* `sock` (integer file descriptor, initialized to 0).
* `serv_addr` (structure to hold the server's IP and Port info).
* `buffer`, `message` (character arrays for sending/receiving data).

**Step 3: Create Socket**

* Call `socket()` with `AF_INET` (IPv4) and `SOCK_STREAM` (TCP).
* **Check:** If the return value is < 0, print "Socket creation error" and **Exit**.

**Step 4: Configure Server Address**

* Set the address family to `AF_INET`.
* Set the port to `8080` (converted to network byte order using `htons`).
* **Convert IP:** Use `inet_pton()` to convert the string "127.0.0.1" (localhost) to binary format.
* **Check:** If conversion fails (returns ), print "Invalid address" and **Exit**.

**Step 5: Connect to Server**

* Call `connect()` using the `sock` and the configured `serv_addr`.
* **Check:** If `connect` returns < 0, print "Connection Failed" and **Exit**.
* Print "Connected to server...".

**Step 6: Communication Loop (Repeat indefinitely)**

1. **Input:** Prompt the user ("You: ") and read the input string using `fgets`.
2. **Format:** Remove the trailing newline character from the input string.
3. **Send:** Call `send()` to transmit the `message` to the server.
4. **Check Exit Condition:**
* **If** the message is "exit": Print "Exiting..." and **Break** the loop.


5. **Receive:** Clear the `buffer` and call `read()` to get the server's response.
6. **Display:** Print the message received from the server.

**Step 7: Close Socket**

* Call `close(sock)` to release the system resources.

**Step 8: Stop**
End the program.