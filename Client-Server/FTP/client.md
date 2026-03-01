## Algorithm: FTP Client Implementation

**Step 1: Start**
Begin the program execution.

**Step 2: Declare Variables**
Initialize necessary variables:

* `sock` (integer file descriptor).
* `serv_addr` (sockaddr_in structure).
* `buffer` (character array for data transfer).
* `filename` (character array to store requested file name).
* `file` (FILE pointer for saving the downloaded data).

**Step 3: Create Socket**

* Call `socket(AF_INET, SOCK_STREAM, 0)`.
* **Check:** If return value < 0, print "Socket creation error" and **Exit**.

**Step 4: Configure Server Address**

* Set address family to `AF_INET` and port to `8080` (using `htons`).
* **Convert IP:** Use `inet_pton` to convert "127.0.0.1" to binary.
* **Check:** If conversion fails, print "Invalid address" and **Exit**.

**Step 5: Connect to Server**

* Call `connect()` using `sock` and `serv_addr`.
* **Check:** If return value < 0, print "Connection Failed" and **Exit**.

**Step 6: Request File**

* Prompt user for a filename and read it using `scanf`.
* Send the `filename` string to the server using `send()`.

**Step 7: Receive and Save File**

1. **Initial Read:** Call `recv()` to get the first chunk of data.
2. **Check for Error:** If the buffer starts with "ERROR:", display the server's error message and skip to Step 8.
3. **Open Local File:** Create a new filename (e.g., "downloaded_filename") and open it in "wb" (write-binary) mode.
4. **Write Loop:** * Write the current buffer to the file using `fwrite()`.
* Repeat `recv()` in a loop to get remaining chunks until the server closes the connection.


5. **Finalize:** Close the file pointer and print "File downloaded successfully".

**Step 8: Close Socket and Stop**

* Call `close(sock)` and terminate the program.