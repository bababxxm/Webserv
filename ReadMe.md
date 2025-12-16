Understood — here is a **clear, structured explanation** of **your exact folder layout**, why each directory exists, what belongs there, and how the whole architecture works together.

This is the kind of structure a **real production HTTP server** would use, and it is excellent for large-scale modularity.

---

# **Overall Architecture**

Your layout is organized into **layers**:

1. **config** — server configuration + MIME database
2. **core** — top-level application and server blocks
3. **http** — request/response parsing and protocol logic
4. **net** — sockets, pollers, connections
5. **utils** — logging, file utilities, string helpers
6. **www** — actual served website + CGI
7. **logs** — output logs
8. **tests** — integration/unit test data
9. **src/include separation** — strict modular design

---

# **1. `config/` — Runtime Input Files**

```
config/
│   default.conf        → main server config (like nginx.conf)
│   mime.types          → maps file extensions to MIME types
│   sites/
│       example_site.conf  → optional per-virtual-host configs
```

This directory handles everything related to **runtime configuration**, not code.

* `default.conf` is the entrypoint config passed to webserv.
* `sites/` allows multiple server blocks.
* `mime.types` is used by Response to set correct `Content-Type`.

---

# **2. `include/` — Public Headers Organized by Domain**

Your headers are separated into clear subsystems:

---

## **2.1 `include/core/` — Top-level orchestration**

```
include/core/
│   Webserv.hpp    → the top-level engine that runs everything
│   Server.hpp     → represents each `server {}` config block
```

Roles:

* **Webserv**

  * parses config
  * builds Server objects
  * initializes sockets
  * owns event loop
* **Server**

  * binds ports
  * sets root/index/error configs
  * manages connections belonging to that server block

---

## **2.2 `include/http/` — HTTP protocol layer**

```
include/http/
│   Request.hpp
│   Response.hpp
│   Header.hpp
│   StatusCode.hpp
```

Handles HTTP grammar / parsing / formatting.

* **Request** — parse raw HTTP bytes
* **Header** — manage header key/values
* **StatusCode** — enum or dictionary for codes
* **Response** — build HTTP responses

This layer is intentionally **network-agnostic** (no sockets here).

---

## **2.3 `include/utils/` — Internal helper layer**

```
include/utils/
│   Log.hpp
│   File.hpp
│   String.hpp
```

Examples:

* `Log` — write to `logs/access.log` and `logs/error.log`
* `File` — load files from `www/`
* `String` — trim, split, case-insensitive compare, etc.

This avoids duplicating helper code across modules.

---

## **2.4 `include/net/` — Networking subsystem**

```
include/net/
│   Poller.hpp
│   Socket.hpp
│   Connection.hpp
```

Handles OS-level networking:

* **Socket**

  * wrapper for `socket()`, `bind()`, `listen()`, `accept()`

* **Connection**

  * represents a client connection
  * stores a buffer
  * tracks read/write state
  * holds Request and Response objects

* **Poller**

  * wraps `poll()`, `epoll`, or `kqueue`
  * monitors file descriptors
  * notifies Webserv when something is readable or writable

This is the low-level layer → only this layer touches syscalls.

---

## **2.5 `include/config/` — Config parser**

```
include/config/
│   Config.hpp
```

Handles:

* tokenize `.conf` files
* parse server/location blocks
* validate types
* expose structured config to Server/Webserv

---

# **3. `src/` — Implementation for all headers**

Mirrors the include structure:

```
src/core/
src/http/
src/utils/
src/net/
src/config/
```

This ensures:

* clean separation
* faster compile times
* correct modularity
* predictable linking

Each `.cpp` implements the corresponding `.hpp`.

---

# **4. `www/` — Public Website Data**

```
www/
│   index.html
│   assets/
│       css/
│       js/
│       img/
│   cgi-bin/
│       test.py
```

Your webserv should:

* serve static files from this directory
* run CGI programs from `cgi-bin`
* map URLs → file paths based on config

This folder is your **document root**, like Apache’s `/var/www/html`.

---

# **5. `logs/` — Runtime Log Files**

```
logs/
│   access.log
│   error.log
```

Produced by `utils/Log`.

Your server should:

* write all successful HTTP requests → access.log
* write errors → error.log
* never print raw logs to STDOUT (except debug mode)

---

# **6. `tests/` — Testing Assets**

```
tests/
│   request_examples/
│       simple_get.txt
│       malformed_request.txt
│   unit/
│   integration/
```

Purpose:

* Provide raw HTTP request examples
* Used for unit testing parser
* Integration testing of the whole system

You can curl your server like:

```
curl -v http://localhost:8080/
```

OR feed these raw request files directly.

---

# **7. `Makefile` — Build Automation**

Your structure implies:

* recursive or pattern-based build
* include paths: `-Iinclude`
* output binary → project root or `/out`

Makefile responsibilities:

* compile using C++98
* link all `.cpp` recursively
* generate `webserv` binary

---

# **8. `main.cpp` — Entry Point**

Should:

* read config path
* create Webserv object
* call config → init → run
* catch exceptions

No logic other than orchestration.

---

# **How the Modules Interact**

### **CONFIG → CORE → NET → HTTP → UTILS**

#### A request flow example:

1. **Poller** says FD is readable
2. **Connection** reads bytes
3. Bytes go into **Request parser**
4. Once parsed, **Server** determines route
5. **Response** is built
6. Written back by **Connection**
7. Logged by **Log**
8. Served file loaded using **File utils**

