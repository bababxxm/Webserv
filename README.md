# 1. **src/config**

## `Config.cpp`

**Purpose:**
Implements the configuration parser + runtime config model.

**Responsibilities:**

- Parse `config/default.conf` (or user-provided `.conf`)
- Build internal representation of:

  - server blocks
  - listen ports
  - locations
  - root paths
  - index files
  - allowed methods
  - client_max_body_size
  - error_page mapping
  - CGI configurations

- Validate configuration values.
- Provide getters for `Server` and `Webserv`.

**You should implement:**

- Tokenizer + simple parser (like Nginx config-style)
- Error handling for malformed config
- Default fallback values

---

# 2. **src/core**

## `Server.cpp`

**Purpose:**
Represents a virtual server instance.

**Responsibilities:**

- Load its own config context from `Config`
- Prepare listening sockets (via `Socket`)
- Maintain mapping:

  - routes → filesystem
  - routes → CGI
  - error pages

- Provide:

  - request routing
  - static file resolution
  - CGI invocation triggers

- Handle a request at a high level:

  ```
  parse request → find location → apply method → return Response
  ```

## `Webserv.cpp`

**Purpose:**
This is your main application orchestrator.

**Responsibilities:**

- Own the full list of `Server` instances
- Initialize:

  - Config
  - Poller
  - Sockets

- Enter main loop:

  - Poll events
  - Accept new clients
  - Dispatch events to correct Server

- Shutdown cleanup

This is essentially your “engine”.

---

# 3. **src/http**

## `Request.cpp`

**Purpose:**
Full HTTP request parsing.

**Responsibilities:**

- Read raw data from socket
- Parse:

  - request line
  - method
  - URL
  - headers
  - query string
  - cookies
  - body (with Content-Length / chunked)

- Validate request
- Detect incomplete header/body
- Provide getter functions for Response

## `Response.cpp`

**Purpose:**
Builds the HTTP response.

**Responsibilities:**

- Build:

  - status line
  - headers
  - body

- Integrate:

  - static file reading via `utils::File`
  - CGI output
  - error pages

- Handle redirects, 405, 404, etc.
- Serialize full HTTP response to string/vector for sending.

## `Header.cpp`

**Purpose:**
Centralized header handling.

**Responsibilities:**

- Parse header fields and normalize them
- Provide helper:

  - `get("Content-Type")`
  - `has("Host")`

- Implement canonicalization (lowercase keys)
- Implement header validation

## `StatusCode.cpp`

**Purpose:**
Const table of HTTP status codes.

**Responsibilities:**

- Map:

  - int → reason phrase
  - int → default message

- Provide helper to look up status phrase

## `ErrorPages.cpp`

**Purpose:**
Handle built-in and custom error pages.

**Responsibilities:**

- Load error page templates from `www/errors`
- Allow override from config
- Provide:

  ```
  std::string getErrorPage(int status_code)
  ```

---

# 4. **src/net**

## `Socket.cpp`

**Purpose:**
Low-level socket wrapper.

**Responsibilities:**

- Create server socket
- Bind / listen
- Accept new connections
- Configure non-blocking mode
- Wrap system calls safely

## `Poller.cpp`

**Purpose:**
Abstraction over `poll()` or `kqueue`/`epoll`.

**Responsibilities:**

- Register file descriptors
- Track events (read/write/error)
- Provide event loop integration for Webserv

## `Connection.cpp`

**Purpose:**
Handles per-client connection state.

**Responsibilities:**

- Owned by Poller or Server
- Track:

  - input buffer
  - output buffer
  - request parsing progress
  - keep-alive / close

- Detect timeout
- Pass complete requests to `Server`

---

# 5. **src/utils**

## `File.cpp`

**Purpose:**
File I/O helper.

**Responsibilities:**

- `readFile(path)`
- `exists(path)`
- `getExtension(path)`
- MIME type resolution

## `Log.cpp`

**Purpose:**
Logging to `logs/access.log` and `logs/error.log`.

**Responsibilities:**

- Log request/response
- Error logging
- Timestamp formatting

## `String.cpp`

**Purpose:**
Utility string helpers.

**Responsibilities:**

- Trim
- Split
- Lower/upper
- Replace
- URL decode
- Safe numeric conversions

---

# Summary Table

| Directory | File           | Description                                      |
| --------- | -------------- | ------------------------------------------------ |
| config    | Config.cpp     | Parses `.conf`, validates, produces config model |
| core      | Server.cpp     | Virtual server, routing, static/CGI integration  |
| core      | Webserv.cpp    | Main engine, polling loop                        |
| http      | Request.cpp    | HTTP request parser                              |
| http      | Response.cpp   | HTTP response builder                            |
| http      | Header.cpp     | Header storage + parsing                         |
| http      | StatusCode.cpp | Status phrases table                             |
| http      | ErrorPages.cpp | Custom + built-in error page manager             |
| net       | Socket.cpp     | Non-blocking sockets, accept, listen             |
| net       | Poller.cpp     | Event loop abstraction                           |
| net       | Connection.cpp | Per-client state machine                         |
| utils     | File.cpp       | File I/O, MIME                                   |
| utils     | Log.cpp        | Logging                                          |
| utils     | String.cpp     | String utilities                                 |

---
