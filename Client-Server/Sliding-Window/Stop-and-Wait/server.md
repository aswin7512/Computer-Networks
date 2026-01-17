### Algorithm: Stop-and-Wait Server

**Step 1: Start**
Begin the program execution.

**Step 2: Declare Variables**
Initialize necessary variables:

* `sockfd`: Integer for the socket file descriptor.
* `server_addr`: Structure to define the server's IP and Port.
* `client_addr`: Structure to hold the sender's address details.
* `buffer`: Character array to store incoming frame data.
* `expected_frame`: Integer counter initialized to 0.

**Step 3: Create Socket**

* Call `socket()` with `AF_INET` (IPv4) and `SOCK_DGRAM` (UDP).

**Step 4: Configure Address & Bind**

* Set the address family to `AF_INET`.
* Set the port to `8080`.
* Set the IP address to `127.0.0.1`.
* **Bind:** Call `bind()` to assign this address to the `sockfd`.
* Print "Receiver is ready...".

**Step 5: Receive Loop**
Repeat the following steps while `expected_frame < 5`:

1. **Receive Frame:** Call `recvfrom()` to wait for data from the sender. This blocks until a packet arrives.
2. **Display Data:** Print the content of the received `buffer`.
3. **Send Acknowledgement:**
* Print "Sending ACK for frame [expected_frame]".
* Call `sendto()` to send the string "ACK" back to the sender (`client_addr`).


4. **Increment:** Increase the `expected_frame` counter by 1.

**Step 6: Close Socket**

* Call `close(sockfd)` to release resources.

**Step 7: Stop**
End the program.
