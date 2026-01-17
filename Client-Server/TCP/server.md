### Algorithm: TCP Server Implementation

**Step 1: Start**
Begin the program execution.

**Step 2: Declare Variables**
Initialize necessary variables:

* `server_fd`, `new_socket` (integers for file descriptors).
* `address` (structure to hold IP and Port info).
* `buffer` (array to store incoming messages).
* `response` (string containing the server's reply).

**Step 3: Create Socket**

* Call the `socket()` function with `AF_INET` (IPv4) and `SOCK_STREAM` (TCP).
* **Check:** If the result is 0 (failure), print "Socket creation failed" and **Exit**.

**Step 4: Configure Address Settings**
Set the `address` structure parameters:

* Set family to `AF_INET`.
* Set IP address to `INADDR_ANY` (accept connections from any IP).
* Set Port to `8080` (convert to network byte order using `htons`).

**Step 5: Bind Socket**

* Call `bind()` to attach the `server_fd` to the specified IP and Port.
* **Check:** If `bind` returns < 0, print "Bind failed", close the socket, and **Exit**.

**Step 6: Listen for Connections**

* Call `listen()` to put the server in a passive mode to wait for requests.
* **Check:** If `listen` returns < 0, print error, close socket, and **Exit**.
* Print "Server listening on port 8080...".

**Step 7: Accept Connection**

* Call `accept()` to extract the first connection request from the queue.
* **Check:** If `accept` returns < 0, print "Accept failed" and **Exit**.
* Assign the return value to `new_socket`.

**Step 8: Communication Loop (Repeat indefinitely)**

1. **Clear Memory:** Reset the `buffer` to ensure no stale data remains.
2. **Read Data:** Call `read()` to get data from `new_socket` into `buffer`.
3. **Check Connection:**
* **If** bytes read : Print "Client disconnected" and **Break** the loop.


4. **Display Data:** Print the message received from the client.
5. **Send Response:** Call `send()` to transmit the `response` string back to the client.
6. **Check Exit Condition:**
* **If** the message contains "exit": Print "Shutting down" and **Break** the loop.



**Step 9: Close Connections**

* Close the client socket (`new_socket`).
* Close the server socket (`server_fd`).

**Step 10: Stop**
End the program.
