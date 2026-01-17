### Algorithm: Stop-and-Wait Client

**Step 1: Start**
Begin the program execution.

**Step 2: Declare Variables**
Initialize necessary variables:

* `sockfd`: Integer for the socket file descriptor.
* `server_addr`: Structure to define the destination (Receiver) IP and Port.
* `buffer`: Character array to store incoming ACKs.
* `tv`: Time value structure for timeout settings (2 seconds).
* `frame_to_send`: Integer counter initialized to 0.

**Step 3: Create Socket & Configure Timeout**

* Call `socket()` with `AF_INET` (IPv4) and `SOCK_DGRAM` (UDP).
* Set `tv.tv_sec = 2` (2-second duration).
* Call `setsockopt()` with `SO_RCVTIMEO` to apply this timeout to the socket. This ensures the program doesn't hang forever if an ACK is lost.

**Step 4: Configure Server Address**

* Set family to `AF_INET`.
* Set port to `8080`.
* Set IP address to `127.0.0.1`.

**Step 5: Transmission Loop**
Repeat the following steps while `frame_to_send < 5`:

1. **Prepare Frame:** Format a string (e.g., "Frame 0") using `sprintf`.
2. **Send Frame:**
* Print "Sending: Frame X".
* Call `sendto()` to transmit the message to `server_addr`.

3. **Wait for Acknowledgement:**
* Call `recvfrom()` to listen for a response.
* **Check Condition:**
* **If `recvfrom` returns < 0 (Timeout):**
* Print "Timeout! Resending...".
* *Note:* The loop variable `frame_to_send` is **not** incremented, so the loop repeats the same frame in the next iteration.


* **If `recvfrom` returns success (ACK received):**
* Print "Received: ACK".
* Increment `frame_to_send` (proceed to next frame).

4. **Delay:** Wait for 1 second (`sleep(1)`) before the next iteration.

**Step 6: Close Socket**

* Call `close(sockfd)` to release resources.

**Step 7: Stop**
End the program.
