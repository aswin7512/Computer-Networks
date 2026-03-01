## Algorithm: FTP Server Implementation

**Step 1: Start**
Begin the program execution.

**Step 2: Declare Variables**
Initialize necessary variables:

* `server_fd`, `new_socket` (integer descriptors).
* `address` (sockaddr_in structure).
* `buffer` (character array for reading requests and file data).
* `file` (FILE pointer for reading the requested file).

**Step 3: Setup Server Socket**

* **Create:** Call `socket()` to get a file descriptor.
* **Configure:** Set family to `AF_INET`, address to `INADDR_ANY`, and port to `8080`.
* **Bind:** Call `bind()` to attach the socket to the port and address.
* **Listen:** Call `listen()` to put the server in passive mode to wait for clients.

**Step 4: Accept Connection**

* Call `accept()`. This blocks execution until a client connects.
* On success, a `new_socket` is created for communication.

**Step 5: Process Request**

* Call `recv()` to read the filename sent by the client into the `buffer`.
* Print the requested filename for logging.

**Step 6: Send File Content**

1. **Open File:** Attempt to `fopen()` the requested file in "rb" (read-binary) mode.
2. **Handle "File Not Found":**
* **If** file is NULL: Send an "ERROR: File not found" message to the client using `send()`.


3. **Handle "Success":**
* **If** file exists: Read the file in chunks using `fread()`.
* Inside a loop, `send()` each chunk through `new_socket` until the end of the file is reached.


4. **Cleanup:** Close the file pointer.

**Step 7: Close Sockets and Stop**

* Close `new_socket` (client connection) and `server_fd` (listener).
* End the program.
